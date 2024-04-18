#pragma once

#include <SDL.h>

#include "font.h"

namespace sos::video {

// TODO: Tests
struct texture {
  // --- Constructors, Destructor, Operators
  ~texture();
  texture(SDL_Texture *rawSdlTexture);
  texture(texture &&other);
  texture &operator=(texture &&rhs);
  // --- Disable copy
  texture(const texture &) = delete;
  texture &operator=(const texture &) = delete;

  // --- Member Functions
  void setAlpha(unsigned char alpha);
  void resetAlpha();

  // --- Data Members
  SDL_Texture *data;
  int w;
  int h;
};
} // namespace sos::video
