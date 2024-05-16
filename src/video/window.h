#pragma once

#include <string>

#include <SDL_events.h>

namespace sos::video::window {

struct config {
  std::string title;
  unsigned int x;
  unsigned int y;
  unsigned int w;
  unsigned int h;
};

template <uint8_t index = 0> void create(const config &p_config);
template <uint8_t index = 0> void destroy();

} // namespace sos::video::window

#include "window.ipp"
