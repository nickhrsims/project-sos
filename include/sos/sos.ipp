#pragma once

#include <SDL2/SDL.h>

#include <spdlog/spdlog.h>

#include <sos/sos.h>

/** Enforce single-initialization. */
static inline bool is_initialized{false};

inline void sos::root::init(const sos::root::config &config) {

  // --- Enforce single-initialization
  if (is_initialized) {
    spdlog::warn("Ignoring attempted re-initialization before quitting.");
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

  // --- Create Window + Renderer
  sos::video::window::create(config.window);
  sos::video::renderer::create();
}

inline void sos::root::init() {
  // Just pass in some sane defaults
  sos::root::init({.headless = false,
                   .window = {
                       .title = "SDL2-on-Stilts Application",
                       .x = 0,
                       .y = 0,
                       .w = 640,
                       .h = 480,
                   }});
}

inline void sos::root::quit() {
  // --- Terminate Sub-systems
  sos::video::renderer::destroy();
  sos::video::window::destroy();

  TTF_Quit();
  SDL_Quit();

  is_initialized = false;
}
