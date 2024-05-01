#pragma once

#include <functional>

#include "group.h"
#include "input/device.h"
#include "input/keyboard.h"
#include "input/mousebutton.h"

namespace sos::input::indirection {

/**
 * Grouping of input events to value types.
 *
 * Supports registration and queries of input mappings with arbitrary values.
 *
 * Follows group semantics for callbacks observing input events.
 */
template <typename value_type>
class indirection_map : public sos::group<std::function<void(value_type)>> {
public:
  using callback_type = std::function<void(value_type)>;
  using membership = sos::group<callback_type>::membership;

  /**
   * Get singleton based on specific `value_type`.
   *
   * A new singleton will be returned for each unique `value_type`!
   */
  static indirection_map &get();

  /**
   * Reset the value-input mappings for this group.
   */
  void reset();

  /**
   * Query a given value's state at this moment in time.
   */
  bool is_value_pressed(value_type value);

  /**
   * Relate an value with a specific keyboard key.
   */
  void relate_value(value_type value, keyboard::scancode scancode);

  /**
   * Relate an value with a specific mouse button.
   */
  void relate_value(value_type value, mouse button);

  /**
   * Register a callback to be notified whenever an input related to this
   * group's value type is received.
   *
   * Returns a membership (observer subscription) that will invalidate
   * the callback should the membership go out of scope.
   * (See: group semantics in the documentation)
   */
  membership on_value(callback_type callback);

  /**
   * Notify all observers of value mapped to given keyboard key.
   */
  void notify(keyboard::scancode);

  /**
   * Notify all observers of value mapped to given mouse button.
   */
  void notify(mouse button);

private:
  // --- Utility value Queires

  bool is_keyboard_value_pressed(value_type value);
  bool is_mouse_button_value_pressed(value_type value);

  // --- value Maps
  // NOTE: One day, these should be templated bidirectional-maps

  /**
   * Relate values to their input type.
   */
  std::unordered_map<value_type, device> value_to_device_map;

  /**
   * Relates values to scancodes.
   *
   * Used for key-state queries.
   */
  std::unordered_map<value_type, keyboard::scancode> value_to_scancode_map;

  /**
   * Relates values to mouse buttons.
   * (mouse buttons are referenced as unsigned bytes)
   *
   * Used for button-state queries.
   */
  std::unordered_map<value_type, mouse> value_to_mousebutton_map;

  /**
   * Relates scancodes to values.
   *
   * Used for notify participants of specific value.
   */
  std::unordered_map<keyboard::scancode, value_type> scancode_to_value_map;

  /**
   *Relates mouse buttons to values.
   *
   * Used to notify participants of specific value.
   */
  std::unordered_map<mouse, value_type> mousebutton_to_value_map;
};

} // namespace sos::input::indirection

#include "indirection_map.ipp"
