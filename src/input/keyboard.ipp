#pragma once

#include <SDL2/SDL.h>

#include "keyboard.h"

namespace sos::input::keyboard {

// -----------------------------------------------------------------------------
// SOS Keyboard-Event Structure
// -----------------------------------------------------------------------------

event::event(const SDL_KeyboardEvent &p_event)
    : timestamp{p_event.timestamp}, repeat{static_cast<bool>(p_event.repeat)},

      scancode{static_cast<enum scancode>(p_event.keysym.scancode)},
      keycode{static_cast<enum keycode>(p_event.keysym.sym)},
      state{static_cast<keystate>(p_event.state)},

      left_shift{static_cast<bool>(p_event.keysym.mod & KMOD_LSHIFT)},
      right_shift{static_cast<bool>(p_event.keysym.mod & KMOD_RSHIFT)},
      left_ctrl{static_cast<bool>(p_event.keysym.mod & KMOD_LCTRL)},
      right_ctrl{static_cast<bool>(p_event.keysym.mod & KMOD_RCTRL)},
      left_alt{static_cast<bool>(p_event.keysym.mod & KMOD_LALT)},
      right_alt{static_cast<bool>(p_event.keysym.mod & KMOD_RALT)},
      left_meta{static_cast<bool>(p_event.keysym.mod & KMOD_LGUI)},
      right_meta{static_cast<bool>(p_event.keysym.mod & KMOD_RGUI)},

      num_lock{static_cast<bool>(p_event.keysym.mod & KMOD_NUM)},
      caps_lock{static_cast<bool>(p_event.keysym.mod & KMOD_CAPS)},
      scroll_lock{static_cast<bool>(p_event.keysym.mod & KMOD_SCROLL)},

      mode{static_cast<bool>(p_event.keysym.mod & KMOD_MODE)},

      shift{static_cast<bool>(p_event.keysym.mod & KMOD_SHIFT)},
      ctrl{static_cast<bool>(p_event.keysym.mod & KMOD_CTRL)},
      alt{static_cast<bool>(p_event.keysym.mod & KMOD_ALT)},
      meta{static_cast<bool>(p_event.keysym.mod & KMOD_GUI)} {}

// -----------------------------------------------------------------------------
// Keyboard-Observer Group
// -----------------------------------------------------------------------------

observer_group &observer_group::get() {
  static observer_group object;
  return object;
}

void observer_group::notify(event p_event) {
  for (auto const &callback : participants_) {
    callback(p_event);
  }
}

// -----------------------------------------------------------------------------
// SDL_KeyboardEvent Dispatch Handler
// -----------------------------------------------------------------------------

void handle_event(const event &p_event) {
  observer_group::get().notify(p_event);
}

// -----------------------------------------------------------------------------
// Keyboard-Event Subscriptions
// -----------------------------------------------------------------------------

observer_group::membership on_event(observer_group::value_type callback) {
  return observer_group::get().issue(callback);
}

// -----------------------------------------------------------------------------
// Keyboard State Queries
// -----------------------------------------------------------------------------

bool is_key_pressed(scancode p_scancode) {
  return SDL_GetKeyboardState(0)[static_cast<SDL_Scancode>(p_scancode)];
}

bool is_key_pressed(keycode p_keycode) {
  return SDL_GetKeyboardState(
      0)[SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(p_keycode))];
}

bool is_key_released(scancode p_scancode) {
  return !is_key_pressed(p_scancode);
}

bool is_key_released(keycode p_keycode) { return !is_key_pressed(p_keycode); }

} // namespace sos::input::keyboard
