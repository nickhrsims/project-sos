#pragma once

// --- stdlib
#include <functional>

// --- SDL2
#include <SDL2/SDL.h>

// --- Project
#include "atoms/milliseconds.h"
#include "group.h"

// --- Local
#include "event.h"
#include "keycode.generated.h"
#include "keystate.h"
#include "scancode.generated.h"

namespace sos::input::keyboard {

// -----------------------------------------------------------------------------
// SDL_KeyboardEvent Dispatch Handler
// -----------------------------------------------------------------------------

void handle_event(const event &p_event);

// -----------------------------------------------------------------------------
// SOS Keyboard-Event Structure
// -----------------------------------------------------------------------------

/**
 * Keyboard Event
 */
struct event : sos::input::event {

  event(const SDL_KeyboardEvent &p_sdl_event);

  // Metadata
  milliseconds timestamp;
  bool repeat;

  // Key Data
  keyboard::scancode scancode;
  keyboard::keycode keycode;
  keyboard::keystate state;

  // Modifier Flags
  bool left_shift : 1;
  bool right_shift : 1;
  bool left_ctrl : 1;
  bool right_ctrl : 1;
  bool left_alt : 1;
  bool right_alt : 1;
  bool left_meta : 1;
  bool right_meta : 1;
  bool num_lock : 1;
  bool caps_lock : 1;
  bool scroll_lock : 1;
  bool mode : 1;
  bool shift : 1;
  bool ctrl : 1;
  bool alt : 1;
  bool meta : 1;
};

// -----------------------------------------------------------------------------
// Keyboard-Observer Group
// -----------------------------------------------------------------------------

struct observer_group : public group<std::function<void(event p_event)>> {
  static observer_group &get();
  void notify(event p_event);
};

// -----------------------------------------------------------------------------
// Keyboard-Event Observer
// -----------------------------------------------------------------------------

/**
 * Subscribe to changes in the global keyboard state.
 *
 * Returns a subscription membership. Destuct the membership to unsubscribe.
 */
observer_group::membership watch(observer_group::value_type callback);

// -----------------------------------------------------------------------------
// Query API
// -----------------------------------------------------------------------------

bool is_key_pressed(scancode p_scancode);
bool is_key_pressed(keycode p_keycode);

bool is_key_released(scancode p_scancode);
bool is_key_released(keycode p_keycode);

} // namespace sos::input::keyboard

#include "keyboard.ipp"
