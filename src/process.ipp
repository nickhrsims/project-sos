#pragma once

#include <cstdint>

#include <SDL.h>
#include <spdlog/spdlog.h>

#include "input/keyboard.h"
#include "process.h"

// ---------------------------------
// sos :: process :: bool active
// ---------------------------------
namespace sos::process {
inline static bool active{false};
}

// ---------------------------------
// <unit> :: void handle_event()
// ---------------------------------
inline static void handle_event(const SDL_Event &p_event) {
  switch (p_event.type) {
  case SDL_KEYDOWN:
    sos::input::keyboard::handle_event(p_event.key);
    break;
  case SDL_QUIT:
    sos::process::stop();
    break;
  default:
    break;
  }
}

// ---------------------------------
// sos :: process :: void stop()
// ---------------------------------
inline void sos::process::stop() { active = false; }

// ---------------------------------
// sos :: process :: void start()
// ---------------------------------
// TODO: Template overload to support custom event handler
template <typename Fn>
  requires std::invocable<Fn &, const float>
void sos::process::start(Fn p_processing_function) {
  typedef uint64_t ticks;
  typedef uint64_t milliseconds;
  typedef float interval;

  spdlog::info("Application started");

  // --- Execute Simulation Loop

  // Set active flag.
  active = true;

  /** CPU ticks at the start of the last frame. */
  ticks previous = SDL_GetTicks64();

  /** CPU ticks at the start of this frame. */
  ticks current = 0;

  /** Time at the beginning of the frame. */
  milliseconds frame_beginning = 0;

  /** Time at the end of the frame. */
  milliseconds frame_ending = 0;

  /** Milliseconds this frame has taken. */
  interval frame_duration = 0;

  /** Time between frames. Measured in seconds. */
  float frame_delta = 0;

  // --- Application Loop
  while (active) {

    // --- Start Frame Timing

    frame_beginning = SDL_GetPerformanceCounter();
    current = SDL_GetTicks64();
    frame_delta = (current - previous) / 1000.0f;

    // --- Poll input events
    /** Input Event Processing */
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      handle_event(event);
    }

    // --- Process Frame
    p_processing_function(frame_delta);

    // --- End Frame Timing
    //
    previous = current;
    frame_ending = SDL_GetPerformanceCounter();
    frame_duration = (frame_ending - frame_beginning) /
                     (float)SDL_GetPerformanceFrequency() * 1000.0f;

    // 60 FPS in Milliseconds
    // == 1 (frame) / 60 (seconds) * 1000 (convert to ms)
    static float const FPS60 = 16.666f;

    milliseconds frame_delay = std::abs(std::floor(FPS60 - frame_duration));

    // Delay each frame to get as close to 60FPS as possible.
    SDL_Delay(frame_delay);
  }

  spdlog::info("Application stopped");
}

#ifdef NEVER
// -----------------------------------------------------------------------------
// Never compiled
// -----------------------------------------------------------------------------
// A way to trick clangd to stop complaining about dead code based on templates.
namespace sos::process::never {
void __force_template__instantiation__() {
  sos::process::start([](float) { sos::process::stop(); });
}
} // namespace sos::process::never
#endif
