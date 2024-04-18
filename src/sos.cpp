
#include <SDL2/SDL.h>

#include <spdlog/spdlog.h>

#include "sos.h"

/** Enforce single-initialization. */
static bool is_initialized{false};

void sos::root::init(const sos::root::config &config) {

  // --- Enforce single-initialization
  if (is_initialized) {
    spdlog::warn("Ignoring attempted re-initialization before calling quit().");
    return;
  }

  // Set construction flag
  is_initialized = true;

  // --- Headless Mode
  if (config.headless) {
    spdlog::warn("Initializing in headless mode! "
                 "(No video, audio, or input systems will be available!)");
    // Headless application may still use timers and event bus!
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
      std::string error_message{SDL_GetError()};
      spdlog::error("{}:{} - {}", __FILE__, __LINE__, error_message);
      abort();
    }
    return;
  }

  // --- Initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::string error_message{SDL_GetError()};
    spdlog::error("{}:{} - {}", __FILE__, __LINE__, error_message);
    abort();
  }

  // --- Initialize SDL TTF
  if (TTF_Init() != 0) {
    std::string error_message{TTF_GetError()};
    spdlog::error("{}:{} - {}", __FILE__, __LINE__, error_message);
    abort();
  }

  // --- Initialize Sub-systems
  sos::video::display::get().initialize(config.display);
  sos::video::renderer::get().initialize(config.renderer);
}

void sos::root::init() {
  sos::root::init({
      .headless = false,
      .display =
          {
              .window_title = "SDL2-on-Stilts Application",
              .window_x = 0,
              .window_y = 0,
              .window_width = 640,
              .window_height = 480,
          },
      .renderer = {},
  });
}

void sos::root::quit() {
  // --- Terminate Sub-systems
  sos::video::renderer::get().terminate();
  sos::video::display::get().terminate();

  TTF_Quit();
  SDL_Quit();

  is_initialized = false;
}
