#pragma once

#include <SDL.h>

namespace sos::video {

// TODO: Tests
struct texture {
  // --- Constructors, Destructor, Operators
  ~texture();
  texture(SDL_Texture *sdl_texture);
  texture(texture &&other);
  texture &operator=(texture &&rhs);
  // --- Disable copy
  texture(const texture &) = delete;
  texture &operator=(const texture &) = delete;

  // --- Member Functions
  void set_alpha(unsigned char alpha);
  void reset_alpha();

  // --- Data Members
  SDL_Texture *data;
  int w;
  int h;
};
} // namespace sos::video

#include "texture.ipp"
