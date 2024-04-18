#pragma once

#include "SDL_rect.h"
#include "SDL_render.h"

#include "display.h"
#include "font.h"
#include "texture.h"

namespace sos::video {

// TODO: Tests
class renderer {

public:
  struct config {};

  ~renderer();

  static renderer &get();

  void initialize(const config &config);
  void terminate();

  void clear() const;
  void show() const;
  void draw_rect(const SDL_Rect &rect, const SDL_Color &color) const;
  // TODO: Support Vector2 positioning
  void draw_texture(const texture &texture, int x, int y) const;
  texture load_texture(const font &font, const std::string &text,
                       const SDL_Color &color) const;

private:
  SDL_Renderer *sdl_renderer;

  renderer();
  renderer(const renderer &) = delete;
  renderer(const renderer &&) = delete;
  renderer &operator=(const renderer &) = delete;
  renderer &operator=(const renderer &&) = delete;
};

} // namespace sos::video
