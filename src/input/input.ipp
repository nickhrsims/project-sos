#pragma once

#include <SDL_events.h>
#include <SDL_scancode.h>

#include <spdlog/spdlog.h>

#include "input.h"

namespace sos::input {

// -----------------------------------------------------------------------------
// Function API
// -----------------------------------------------------------------------------

// --- Action State Query (Read)
template <typename action_type> bool action(action_type action) {
  return group<action_type>::get().is_action_pressed(action);
}

// --- Key-Action-Mapping Command (Write)
template <typename action_type> void action(action_type action, keyboard key) {
  group<action_type>::get().configure_keyboard_action(action, key);
}

// --- MouseButton-Action-Mapping Command (Write)
template <typename action_type> void action(action_type action, mouse button) {
  group<action_type>::get().configure_mousebutton_action(action, button);
}

// --- Reset Command (Write)
template <typename action_type> void reset(action_type null_action) {
  group<action_type>::get().reset(null_action);
}

// -----------------------------------------------------------------------------
// Group
// -----------------------------------------------------------------------------

// We get a different group for different action types! :D
// (this is what we want)
template <typename action_type> group<action_type> &group<action_type>::get() {
  static group object;
  return object;
}

template <typename action_type>
bool group<action_type>::is_action_pressed(action_type action) {
  switch (action_to_device_map[action]) {
  case device::keyboard:
    return SDL_GetKeyboardState(
        nullptr)[static_cast<SDL_Scancode>(action_to_scancode_map[action])];

  case device::mouse:
    return SDL_GetMouseState(nullptr, nullptr) &
           SDL_BUTTON(static_cast<uint8_t>(action_to_mousebutton_map[action]));

  default:
    return false;
  }
}

template <typename action_type>
void group<action_type>::reset(action_type p_null_action) {
  null_action = p_null_action;
  action_to_device_map.clear();
  action_to_scancode_map.clear();
  action_to_mousebutton_map.clear();
  std::fill_n(scancode_to_action_map, SDL_NUM_SCANCODES, p_null_action);
  std::fill_n(mousebutton_to_action_map, mousebutton_count, p_null_action);
}

template <typename action_type>
void group<action_type>::configure_keyboard_action(action_type action,
                                                   keyboard key) {
  action_to_device_map[action] = device::keyboard;
  action_to_scancode_map[action] = static_cast<SDL_Scancode>(key);
  scancode_to_action_map[static_cast<SDL_Scancode>(key)] = action;
}

template <typename action_type>
void group<action_type>::configure_mousebutton_action(action_type action,
                                                      mouse button) {
  action_to_device_map[action] = device::mouse;
  action_to_mousebutton_map[action] = static_cast<uint8_t>(button);
  mousebutton_to_action_map[static_cast<uint8_t>(button)] = action;
}

template <typename action_type>
void group<action_type>::handle_keyboard_event(const SDL_KeyboardEvent &event) {
  SDL_Scancode scancode{event.keysym.scancode};
  action_type action{scancode_to_action_map[scancode]};

  // If no action assigned to scancode, ignore the event.
  if (action == null_action) {
    return;
  }

  for (auto const &callback : this->participants) {
    callback(action);
  }
}

template <typename action_type>
void group<action_type>::handle_mousebutton_event(
    const SDL_MouseButtonEvent &event) {
  uint8_t button{event.button};
  action_type{mousebutton_to_action_map[button]};

  if (action == null_action) {
    return;
  }

  for (auto const &callback : this->participants) {
    callback(action);
  }
}

template <typename action_type>
group<action_type>::membership group<action_type>::on_action_pressed(
    typename group<action_type>::callback_type callback) {
  return this->issue(callback);
}

template <typename action_type>
void group<action_type>::off_action_pressed(
    typename group<action_type>::membership membership) {
  this->revoke(membership);
}

} // namespace sos::input
