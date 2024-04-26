#pragma once

#include <SDL2/SDL.h>

#include "SDL_timer.h"
#include "input/keyboard.h"

namespace toolkit {

inline void setup() {
  // --- Input system requires `Events` sub-system.
  // If other SDL sub-systems are required,
  // it should be considered a design flaw.
  SDL_Init(SDL_INIT_EVENTS);
}

inline void teardown() { SDL_Quit(); }

inline void send_keydown_event(sos::input::keyboard::scancode p_scancode,
                               sos::input::keyboard::keycode p_keycode,
                               bool p_repeat = false) {
  SDL_Scancode sdl_scancode{static_cast<SDL_Scancode>(p_scancode)};
  SDL_Keycode sdl_keycode{static_cast<SDL_Keycode>(p_keycode)};
  uint8_t sdl_repeat{static_cast<uint8_t>(p_repeat)};

  SDL_Event event;
  event.key.timestamp = SDL_GetTicks64();
  event.key.repeat = sdl_repeat;
  event.key.keysym.scancode = sdl_scancode;
  event.key.keysym.sym = sdl_keycode;
  event.key.keysym.mod = KMOD_NONE;

  event.key.type = SDL_KEYDOWN;
  event.key.state = SDL_PRESSED;

  SDL_PushEvent(&event);
}

} // namespace toolkit
