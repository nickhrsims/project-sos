#include <cstdint>

#include <SDL2/SDL.h>

#include <catch2/catch_test_macros.hpp>

#include "input/input_map.h"

namespace sos::input::test {

inline void setup() {
  // --- Input system requires `Events` sub-system.
  // If other SDL sub-systems are required,
  // it should be considered a design flaw.
  SDL_Init(SDL_INIT_EVENTS);
}

inline void teardown() { SDL_Quit(); }

/**
 * Send a virtual keyboard-input key press through the SDL event queue.
 */
inline void simulate_keyboard_key_press(sos::input::keyboard key) {
  SDL_Scancode scancode{static_cast<SDL_Scancode>(key)};

  SDL_Event event;
  event.key.keysym.scancode = scancode;
  event.key.keysym.sym = SDL_GetKeyFromScancode(scancode);
  event.key.keysym.mod = KMOD_NONE;

  event.key.type = SDL_KEYDOWN;
  event.key.state = SDL_PRESSED;

  SDL_PushEvent(&event);
}

/**
 * Send a virtual keyboard-input key release through the SDL event queue.
 */
inline void simulate_keyboard_key_release(sos::input::keyboard key) {
  SDL_Scancode scancode{static_cast<SDL_Scancode>(key)};

  SDL_Event event;
  event.key.keysym.scancode = scancode;
  event.key.keysym.sym = SDL_GetKeyFromScancode(scancode);
  event.key.keysym.mod = KMOD_NONE;

  event.key.type = SDL_KEYUP;
  event.key.state = SDL_RELEASED;

  SDL_PushEvent(&event);
}

inline void run_event_loop(uint8_t iterations) {
  for (uint8_t n = 0; n < iterations; ++n) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        sos::input::handle_keydown_event(event);
      }
    }
  }
}

} // namespace sos::input::test
