#pragma once

#include "data/dispatch_map.ipp"
#include "data/reset_map.ipp"
#include "functions.h"

namespace sos::input::indirection {
template <typename value_type>
indirection_map<value_type>::membership
on_value(std::function<void(value_type)> p_callback) {
  return indirection_map<value_type>::get().on_value(p_callback);
}

// TODO: Remove relevent global state values
template <typename value_type> void reset() {
  indirection_map<value_type>::get().reset();
}

template <typename value_type> bool is_value_pressed(value_type p_value) {
  return indirection_map<value_type>::get().is_value_pressed(p_value);
}

// TODO: value_type must be hashable, copyable
template <typename value_type>
void relate_value(value_type p_value, input::keyboard::scancode p_scancode) {
  using scancode = input::keyboard::scancode;
  __data__::dispatch_map<scancode>[p_scancode] = [](scancode lp_scancode) {
    indirection_map<value_type>::get().notify(lp_scancode);
  };
  __data__::reset_map<scancode>[p_scancode] = [](scancode lp_scancode) {
    __data__::dispatch_map<scancode>.erase(lp_scancode);
    __data__::reset_map<scancode>.erase(lp_scancode);
  };
  indirection_map<value_type>::get().relate_value(p_value, p_scancode);
}

template <typename value_type>
void relate_value(value_type p_value, mouse p_button) {
  __data__::dispatch_map<mouse>[p_button] = [](mouse button) {
    indirection_map<value_type>::get().notify(button);
  };
  __data__::reset_map<mouse>[p_button] = [](mouse button) {
    __data__::dispatch_map<mouse>.erase(button);
    __data__::reset_map<mouse>.erase(button);
  };
  indirection_map<value_type>::get().relate_value(p_value, p_button);
}

} // namespace sos::input::indirection
