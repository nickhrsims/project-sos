#pragma once

#include <functional>
#include <list>
#include <string>
#include <unordered_map>

#include <SDL_events.h>
#include <SDL_scancode.h>

#include "keyboard.h"
#include "mousebutton.h"

#include "group.h"

// TODO: How to implement multi-player inputs without specifying specific player
// actions?
//       Possibly with a different action_type to instantiate a different
//       group!!

namespace sos::input {
/**
 * Input Types.
 */
enum class device {
  none,
  keyboard,
  mouse,
};

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

  // --- Queries
  bool is_action_pressed(action_type action);

  // --- Commands
  void reset(action_type null_action = 0);
  void configure_keyboard_action(action_type action, keyboard key);
  void configure_mousebutton_action(action_type action, mouse button);
  void handle_keyboard_event(const SDL_KeyboardEvent &event);
  void handle_mousebutton_event(const SDL_MouseButtonEvent &event);

  // --- Events
  membership on_action_pressed(callback_type callback);

  // NOTE: Possible to remove when membership is implemented correctly
  // NOTE: Consider membership custom revocation function
  void off_action_pressed(membership);

private:
  // --- Utility Action Queires

  bool is_keyboard_action_pressed(action_type action);
  bool is_mouse_button_action_pressed(action_type action);

  // --- Action Maps

  /**
   * Relate actions to their input type.
   */
  std::unordered_map<action_type, device> action_to_device_map;

  /**
   * Relates actions to scancodes.
   */
  std::unordered_map<action_type, SDL_Scancode> action_to_scancode_map;

  /**
   * Relates actions to mouse buttons.
   * (mouse buttons are referenced as unsigned bytes)
   */
  std::unordered_map<action_type, uint8_t> action_to_mousebutton_map;

  /**
   * Relates scancodes to actions.
   */
  action_type scancode_to_action_map[SDL_NUM_SCANCODES];
  /**
   *Relates mouse buttons to actions.
   *
   * SDL2 implementation-specific.
   * SDL_mouse.h provides 5 macro-definitions ranging 1..5 inclusive.
   * This means that the map must have a length of 6 to support all
   * mouse indices (without needing to subject the mouse button, which
   * would require an explanation everywhere it happens, and extra byte
   * isn't much when compared to making sense of code).
   */
  static const uint8_t mousebutton_count{6};
  action_type
      mousebutton_to_action_map[mousebutton_count]; // Read note above on magic
                                                    // number `6`

  /**
   * Null action value. Assumed `0` unless otherwise configured.
   */
  action_type null_action = static_cast<action_type>(0);
};

// ---------------------------------
// Configuration
// ---------------------------------

// TODO: Remove
// FIXME: This is an incomplete stub from legacy versions
template <typename Action> struct config {

  // It is undefined behavior to assign multiple inputs to the same action.
  // TODO: Consider supporting multiple inputs / input-types per action.

  /**
   * Relate a keyboard key scancode to an action.
   *
   * This will cause the action to be triggered when the key is pressed.
   */
  void setKeyboardKeyDownAction(SDL_Scancode scancode, Action action);

  /**
   * Relate a mouse button to an action.
   *
   * This will cause the action to be triggered when the button is pressed.
   */
  void setMouseButtonDownAction(uint8_t button, Action action);

private:
  struct KeyboardKeyActionDescription {
    KeyboardKeyActionDescription(){}; // by default do nothing interesting.
    KeyboardKeyActionDescription(SDL_Scancode scancode);
    device type;
    SDL_Scancode scancode;
  };

  struct MouseButtonActionDescription {
    MouseButtonActionDescription(){}; // by default do nothing interesting.
    MouseButtonActionDescription(uint8_t button);
    device type;
    uint8_t button;
  };

  union ActionDescription {
    ActionDescription(){};
    device type;
    KeyboardKeyActionDescription keyboard;
    MouseButtonActionDescription mouse;
  };

  std::unordered_map<Action, ActionDescription> actionMap;
};

} // namespace sos::input

#include "input.ipp"
