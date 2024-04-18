#include <string>

#include <spdlog/spdlog.h>

#include "SDL.h"

#include "display.h"

static const std::string TAG{"Display Sub-system"};

namespace sos::video {

// -----------------------------------------------------------------------------
// No-op Constructor / Destructor
// -----------------------------------------------------------------------------

display::display() {}
display::~display() {}

// -----------------------------------------------------------------------------
// Initialization / Termination
// -----------------------------------------------------------------------------

void display::initialize(const config &config) {
  spdlog::info("Initializing {}.", TAG);
  // TODO: support flags (fullscreen etc.)
  sdl_window = SDL_CreateWindow(config.window_title.c_str(), config.window_x,
                                config.window_y, config.window_width,
                                config.window_height, 0);
  if (!sdl_window) {
    spdlog::error("{} Error: Failed to create window!");
  }
}

void display::terminate() {
  spdlog::info("Terminating {}.", TAG);
  SDL_DestroyWindow(sdl_window);
}

// -----------------------------------------------------------------------------
// Singleton
// -----------------------------------------------------------------------------

// Return singleton.
display &display::get() {
  static display object{};
  return object;
}

// -----------------------------------------------------------------------------
// Event Handling
// -----------------------------------------------------------------------------

void display::handle_event(const SDL_Event &event) { (void)event; }

} // namespace sos::video
