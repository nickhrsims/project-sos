#pragma once

#include <string>

#include <spdlog/spdlog.h>

#include "texture.h"

namespace sos::video {

// -----------------------------------------------------------------------------
// Destructor, Constructors, and Operators
// -----------------------------------------------------------------------------

texture::~texture() { SDL_DestroyTexture(data); }

texture::texture(SDL_Texture *p_sdl_texture) : data{p_sdl_texture} {
  if (!data) {
    spdlog::error("Cannot load texture data: {}.", SDL_GetError());
    abort();
  }

  SDL_QueryTexture(p_sdl_texture, NULL, NULL, &w, &h);
}

texture::texture(texture &&other) : data{other.data}, w{other.w}, h{other.h} {
  other.data = nullptr;
}

texture &texture::operator=(texture &&other) {
  if (data) {
    SDL_DestroyTexture(data);
  }
  data = other.data;
  w = other.w;
  h = other.h;
  other.data = nullptr;
  return *this;
}

// -----------------------------------------------------------------------------
// Public API
// -----------------------------------------------------------------------------

void texture::set_alpha(unsigned char alpha) {
  SDL_SetTextureAlphaMod(data, alpha);
}
void texture::reset_alpha() { set_alpha(255); }

} // namespace sos::video
