#pragma once

#include <string>

#include <spdlog/spdlog.h>

#include "SDL.h"

#include "window.h"

namespace sos::video::window::__data__ {
template <uint8_t index> static SDL_Window *sdl_window{nullptr};
}

namespace sos::video::window {

template <uint8_t index> SDL_Window *get() {
  return __data__::sdl_window<index>;
}

template <uint8_t index> void create(const config &p_config) {
  spdlog::info("Creating window({}).", index);
  // TODO: support flags (fullscreen etc.)
  __data__::sdl_window<index> =
      SDL_CreateWindow(p_config.title.c_str(), p_config.x, p_config.y,
                       p_config.w, p_config.h, 0);
  if (!__data__::sdl_window<index>) {
    spdlog::error("Failed to create window({}): {}.", index, SDL_GetError());
  }
}

template <uint8_t index> void destroy() {
  spdlog::info("Destroying window({}).", index);
  SDL_DestroyWindow(__data__::sdl_window<index>);
}

} // namespace sos::video::window
