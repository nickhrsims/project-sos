#pragma once

#include <string>

#include "SDL_ttf.h"

namespace sos::video {

// TODO: Tests
class font {
public:
  font(const std::string path, const int points);
  ~font();

  font(font &&other);
  font &operator=(font &&rhs);

  TTF_Font *get() const;

private:
  TTF_Font *data;
  font(const font &other);
  font &operator=(const font &rhs);
};
} // namespace sos::video
