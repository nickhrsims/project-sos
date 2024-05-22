#pragma once

#include <string>

#include <SDL_ttf.h>

namespace sos::video {

// TODO: Tests
class font {
  public:
    inline font(const std::string path, const int points);
    inline ~font();

    inline font(font&& other);
    inline font& operator=(font&& rhs);

    TTF_Font* data;

  private:
    inline font(const font& other);
    inline font& operator=(const font& rhs);
};
} // namespace sos::video

#include <sos/video/font.ipp>
