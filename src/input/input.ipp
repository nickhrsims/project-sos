#pragma once

#include <SDL2/SDL.h>

#include <spdlog/spdlog.h>

#include "input.h"

namespace sos::input {

// TODO: One input should be able to be assigned to multiple actions,
//       but should an action only be able to be triggered by a single input?
//       (think Minecraft).
//
// NOTE: Not all games do this. Dragon's Dogma 2 maps two inputs to
//       the same action, for example (sprint / interact).
//       Furthermore, some games directly support multiple custom inputs to
//       an action (Starwars: Battlefront II classic). Hell, I've used
//       this to configure gamepads and mouse + keyboard controls
//       simultaneously since the game does not disciminate between
//       "gamepad on/off mode" conceptually, you either have gamepad(s)
//       plugged in or you don't. It has it's uses.
//
// NOTE: How would this be implemented? In the current implementation,
//       actions are mapped to an input device, making multi-device
//       input-to-action mappings unsupported mechanically.
//       The reason actions are mapped to a device to begin with is
//       because action-state query lookup requires a device-specific polling
//       function under the hood to check inputs against.
//
// NOTE: One solution might be an action-to-device-mask map rather than a
//       straight-forward action-to-device map. In this way, an action is
//       explicitly mapped to multiple devices without requiring a
//       collection-like datatype to convey what queries are required.
//
// NOTE: Stuff like this is exactly why the templates here don't accept
//       device_type parameters, instead manually overloading them and
//       keeping duplicate maps around.
//
// NOTE: The suggested task will, no matter how the mapping is done,
//       require an overhaul of device-agnostic action registration support.

// TODO: Support device-change notification subscriptions.
// (Hello, this is IT. Is your gamepad plugged in?)

// -----------------------------------------------------------------------------
// Global State Data
// -----------------------------------------------------------------------------

namespace __data__ {

template <typename input_type>
static inline std::unordered_map<input_type, std::function<void(input_type)>>
    dispatch_map;

template <typename input_type>
static inline std::unordered_map<input_type, std::function<void(input_type)>>
    reset_map;

} // namespace __data__

// -----------------------------------------------------------------------------
// Global Input Event Handlers
// -----------------------------------------------------------------------------

static inline void handle_keydown_event(const SDL_Event &event) {

  keyboard key{static_cast<keyboard>(event.key.keysym.scancode)};
  if (__data__::dispatch_map<keyboard>.contains(key)) {
    __data__::dispatch_map<keyboard>[key](key);
  }
}

// TODO: Account for multiple mice
inline void handle_mousebuttondown_event(const SDL_Event &event) {
  mouse button{static_cast<mouse>(event.button.button)};
  if (__data__::dispatch_map<mouse>.contains(button)) {
    __data__::dispatch_map<mouse>[button](button);
  }
}

// -----------------------------------------------------------------------------
// Function API
// -----------------------------------------------------------------------------

// --- sos :: input :: on(callback) [set]
template <typename action_type>
group<action_type>::membership on(std::function<void(action_type)> callback) {
  return group<action_type>::get().on_action_pressed(callback);
}

// --- sos :: input :: reset() [clear]
// TODO: Remove relevent global state values
template <typename action_type> void reset() {
  group<action_type>::get().reset();
}

// --- sos :: input :: action(type) [get]
template <typename action_type> bool action(action_type action) {
  return group<action_type>::get().is_action_pressed(action);
}

// --- sos :: input :: action(type, key) [set]
// TODO: action_type must be hashable, copyable
template <typename action_type> void action(action_type action, keyboard key) {
  __data__::dispatch_map<keyboard>[key] = [](keyboard key) {
    group<action_type>::get().handle_keyboard(key);
  };
  __data__::reset_map<keyboard>[key] = [](keyboard key) {
    __data__::dispatch_map<keyboard>.erase(key);
    __data__::reset_map<keyboard>.erase(key);
  };
  group<action_type>::get().configure_keyboard_action(action, key);
}

// --- sos :: input :: action(type, button) [set]
template <typename action_type> void action(action_type action, mouse button) {
  __data__::dispatch_map<mouse>[button] = [](mouse button) {
    group<action_type>::get().handle_mouse(button);
  };
  __data__::reset_map<mouse>[button] = [](mouse button) {
    __data__::dispatch_map<mouse>.erase(button);
    __data__::reset_map<mouse>.erase(button);
  };
  group<action_type>::get().configure_mousebutton_action(action, button);
}

// -----------------------------------------------------------------------------
// Input Group Implementation
// -----------------------------------------------------------------------------

// --- group :: get() [get]
template <typename action_type> group<action_type> &group<action_type>::get() {
  static group object;
  return object;
}
// --- group :: reset() [clear]
template <typename action_type> void group<action_type>::reset() {
  // --- Keyboard Keys

  for (const auto &[action, key] : action_to_keyboard_map) {
    __data__::reset_map<keyboard>[key](key);
  }

  action_to_keyboard_map.clear();
  keyboard_to_action_map.clear();

  // --- Mouse Buttons

  for (const auto &[action, button] : action_to_mousebutton_map) {
    __data__::reset_map<mouse>[button](button);
  }

  action_to_mousebutton_map.clear();
  mousebutton_to_action_map.clear();

  // --- Device Mappings

  action_to_device_map.clear();
}

// --- group :: is_action_pressed() [get]
template <typename action_type>
bool group<action_type>::is_action_pressed(action_type action) {
  switch (action_to_device_map[action]) {
  case device::keyboard:
    return SDL_GetKeyboardState(
        nullptr)[static_cast<SDL_Scancode>(action_to_keyboard_map[action])];

  case device::mouse:
    return SDL_GetMouseState(nullptr, nullptr) &
           SDL_BUTTON(static_cast<uint8_t>(action_to_mousebutton_map[action]));

  default:
    return false;
  }
}

// --- group :: configure_keyboard_action(type, key) [set]
template <typename action_type>
void group<action_type>::assign_action(action_type action, keyboard key) {
  action_to_device_map[action] = device::keyboard;
  action_to_keyboard_map[action] = key;
  keyboard_to_action_map[key] = action;
}

// --- group :: configure_mousebutton_action(type, button) [set]
template <typename action_type>
void group<action_type>::assign_action(action_type action, mouse button) {
  action_to_device_map[action] = device::mouse;
  action_to_mousebutton_map[action] = button;
  mousebutton_to_action_map[button] = action;
}

// --- group :: on_action_pressed [observe]
template <typename action_type>
group<action_type>::membership group<action_type>::on_action_pressed(
    typename group<action_type>::callback_type callback) {
  return this->issue(callback);
}

// --- group :: off_action_pressed [unobserve]
template <typename action_type>
void group<action_type>::off_action_pressed(
    typename group<action_type>::membership membership) {
  this->revoke(membership);
}

// --- group :: handle_keyboard(key) [effect]
template <typename action_type>
void group<action_type>::handle_keyboard(keyboard key) {
  action_type action{keyboard_to_action_map[key]};

  for (std::function<void(action_type)> callback : this->participants_) {
    callback(action);
  }
}

// --- group :: handle_mouse(button) [effect]
template <typename action_type>
void group<action_type>::handle_mouse(mouse button) {
  action_type action{mousebutton_to_action_map[button]};

  for (std::function<void(action_type)> callback : this->participants_) {
    callback(action);
  }
}

} // namespace sos::input
