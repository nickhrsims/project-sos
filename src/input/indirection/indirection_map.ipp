#pragma once

#include "data/reset_map.ipp"
#include "indirection_map.h"

namespace sos::input::indirection {

template <typename value_type>
indirection_map<value_type> &indirection_map<value_type>::get() {
  static indirection_map object;
  return object;
}
template <typename value_type> void indirection_map<value_type>::reset() {
  // --- Keyboard Keys

  for (const auto &[_, scancode] : value_to_scancode_map) {
    __data__::reset_map<keyboard::scancode>[scancode](scancode);
  }

  value_to_scancode_map.clear();
  scancode_to_value_map.clear();

  // --- Mouse Buttons

  for (const auto &[value, button] : value_to_mousebutton_map) {
    __data__::reset_map<mouse>[button](button);
  }

  value_to_mousebutton_map.clear();
  mousebutton_to_value_map.clear();

  // --- Device Mappings

  value_to_device_map.clear();
}

template <typename value_type>
bool indirection_map<value_type>::is_value_pressed(value_type p_value) {
  switch (value_to_device_map[p_value]) {
  case device::keyboard:
    return keyboard::is_key_pressed(value_to_scancode_map[p_value]);

    // TODO: Come back when mouse has an abstraction layer
  case device::mouse:
    return SDL_GetMouseState(nullptr, nullptr) &
           SDL_BUTTON(static_cast<uint8_t>(value_to_mousebutton_map[p_value]));

  default:
    return false;
  }
}

template <typename value_type>
void indirection_map<value_type>::relate_value(value_type p_value,
                                               keyboard::scancode p_scancode) {
  value_to_device_map[p_value] = device::keyboard;
  value_to_scancode_map[p_value] = p_scancode;
  scancode_to_value_map[p_scancode] = p_value;
}

template <typename value_type>
void indirection_map<value_type>::relate_value(value_type value, mouse button) {
  value_to_device_map[value] = device::mouse;
  value_to_mousebutton_map[value] = button;
  mousebutton_to_value_map[button] = value;
}

template <typename value_type>
indirection_map<value_type>::membership indirection_map<value_type>::on_value(
    typename indirection_map<value_type>::callback_type callback) {
  return this->issue(callback);
}

template <typename value_type>
void indirection_map<value_type>::notify(keyboard::scancode p_scancode) {
  value_type value{scancode_to_value_map[p_scancode]};

  for (std::function<void(value_type)> callback : this->participants_) {
    callback(value);
  }
}

template <typename value_type>
void indirection_map<value_type>::notify(mouse button) {
  value_type value{mousebutton_to_value_map[button]};

  for (std::function<void(value_type)> callback : this->participants_) {
    callback(value);
  }
}
} // namespace sos::input::indirection
