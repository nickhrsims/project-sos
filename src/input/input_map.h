#pragma once

#include <functional>
#include <list>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>

#include "keyboard.h"
#include "mousebutton.h"

#include "group.h"

// TODO: How to implement multi-player inputs without specifying specific player
// actions?
//       Possibly with a different action_type to instantiate a different
//       group!!

namespace sos::input {

/**
 * Supported input devices.
 */
enum class device {
  none,
  keyboard,
  mouse,
};

// -----------------------------------------------------------------------------
// Input Event
// -----------------------------------------------------------------------------

struct event {};

struct keyboard_event : event {};

struct mouse_button_event : event {};

struct mouse_motion_event : event {};

// -----------------------------------------------------------------------------
// Input Group
// -----------------------------------------------------------------------------

/**
 * Grouping of input events to action types.
 *
 * Supports registration and queries of input mappings with actions.
 *
 * Follows group semantics for callbacks observing input events.
 */
template <typename action_type>
class group : public sos::group<std::function<void(action_type)>> {
public:
  using callback_type = std::function<void(action_type)>;
  using membership = sos::group<callback_type>::membership;

  /**
   * Get singleton based on specific `action_type`.
   *
   * A new singleton will be returned for each unique `action_type`!
   */
  static group &get();

  /**
   * Reset the action-input mappings for this group.
   */
  void reset();

  /**
   * Query a given action's state at this moment in time.
   */
  bool is_action_pressed(action_type action);

  /**
   * Relate an action with a specific keyboard key.
   */
  void assign_action(action_type action, keyboard key);

  /**
   * Relate an action with a specific mouse button.
   */
  void assign_action(action_type action, mouse button);

  /**
   * Register a callback to be notified whenever an input related to this
   * group's action type is received.
   *
   * Returns a membership (observer subscription) that will invalidate
   * the callback should the membership go out of scope.
   * (See: group semantics in the documentation)
   */
  membership on_action_pressed(callback_type callback);

  /**
   * Manually remove input event observer.
   */
  void off_action_pressed(membership);

  /**
   * Notify all observers of action mapped to given keyboard key.
   */
  void handle_keyboard(keyboard key);

  /**
   * Notify all observers of action mapped to given mouse button.
   */
  void handle_mouse(mouse button);

private:
  // --- Utility Action Queires

  bool is_keyboard_action_pressed(action_type action);
  bool is_mouse_button_action_pressed(action_type action);

  // --- Action Maps
  // NOTE: One day, these should be templated bidirectional-maps

  /**
   * Relate actions to their input type.
   */
  std::unordered_map<action_type, device> action_to_device_map;

  /**
   * Relates actions to scancodes.
   *
   * Used for key-state queries.
   */
  std::unordered_map<action_type, keyboard> action_to_keyboard_map;

  /**
   * Relates actions to mouse buttons.
   * (mouse buttons are referenced as unsigned bytes)
   *
   * Used for button-state queries.
   */
  std::unordered_map<action_type, mouse> action_to_mousebutton_map;

  /**
   * Relates scancodes to actions.
   *
   * Used for notify participants of specific action.
   */
  std::unordered_map<keyboard, action_type> keyboard_to_action_map;

  /**
   *Relates mouse buttons to actions.
   *
   * Used to notify participants of specific action.
   */
  std::unordered_map<mouse, action_type> mousebutton_to_action_map;
};

// -----------------------------------------------------------------------------
// Function API
// -----------------------------------------------------------------------------

/**
 * Subscribe to actions of a given type.
 */
template <typename action_type>
group<action_type>::membership on(std::function<void(action_type)> callback);

/**
 * Reset the global input-action mappings.
 */
template <typename action_type> void reset();

/**
 * Query the state of an action.
 */
template <typename action_type> bool action(action_type action);

/**
 * Relate an action with a keyboard key.
 */
template <typename action_type> void action(action_type action, keyboard key);

/**
 * Relate an action with a mouse button.
 */
template <typename action_type> void action(action_type action, mouse button);

} // namespace sos::input

#include "input_map.ipp"
