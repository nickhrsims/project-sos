#pragma once

#include <spdlog/spdlog.h>

#include "font.h"

namespace sos::video {

font::font(const std::string path, const int size)
    : data{TTF_OpenFont(path.c_str(), size)} {
  if (!data) {
    spdlog::error("Cannot load font data: {}.", TTF_GetError());
    abort();
  }
}
font::~font() { TTF_CloseFont(data); }

font::font(font &&other) {
  data = other.data;
  other.data = nullptr;
}

font &font::operator=(font &&rhs) {
  if (data) {
    TTF_CloseFont(data);
  }
  data = rhs.data;
  rhs.data = nullptr;
  return *this;
}

} // namespace sos::video
