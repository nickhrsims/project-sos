#pragma once

#include <SDL_pixels.h>

// TODO: Tests

namespace sos::demo {
struct color : SDL_Color {
  static const color generate(float r, float b, float g, float a);

  static const color white(float alpha);
  static const color white();

  static const color black(float alpha);
  static const color black();
};
} // namespace sos::demo

#include "color.ipp"
