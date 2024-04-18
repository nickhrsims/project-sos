#include <string>

#include <spdlog/spdlog.h>

#include "texture.h"

namespace sos::video {

// -----------------------------------------------------------------------------
// Destructor, Constructors, and Operators
// -----------------------------------------------------------------------------

texture::~texture() { SDL_DestroyTexture(data); }

texture::texture(SDL_Texture *rawSdlTexture) : data{rawSdlTexture} {
  if (!data) {
    spdlog::error("Cannot create Texture object: {}", SDL_GetError());
    abort();
  }

  SDL_QueryTexture(rawSdlTexture, NULL, NULL, &w, &h);
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

void texture::setAlpha(unsigned char alpha) {
  SDL_SetTextureAlphaMod(data, alpha);
}
void texture::resetAlpha() { setAlpha(255); }

} // namespace sos::video
