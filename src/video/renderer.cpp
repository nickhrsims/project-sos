#include <spdlog/spdlog.h>

#include "display.h"
#include "font.h"
#include "renderer.h"
#include "texture.h"

static const std::string TAG{"Renderer"};

namespace sos::video {

// TODO: Support texture asset caching (including strings from fonts)

// -----------------------------------------------------------------------------
// No-op Constructor / Destructor
// -----------------------------------------------------------------------------

renderer::renderer() {}
renderer::~renderer() {}

// -----------------------------------------------------------------------------
// Initialization / Termination
// -----------------------------------------------------------------------------

void renderer::initialize(const config &config) {
  (void)config;
  spdlog::info("Initializing {}.", TAG);
  if (!display::get().sdl_window) {
    spdlog::error("{} Error: Window required by renderer is null!", TAG);
  }
  sdl_renderer = SDL_CreateRenderer(display::get().sdl_window, 0, 0);
  if (!sdl_renderer) {
    spdlog::error("{} Error: Renderer create failed!", TAG);
    abort();
  }
  spdlog::debug("Initialized {} OK!", TAG);
}

void renderer::terminate() {
  spdlog::info("Terminating {}.", TAG);
  SDL_DestroyRenderer(sdl_renderer);
}

// -----------------------------------------------------------------------------
// Singleton
// -----------------------------------------------------------------------------

// Return singleton.
renderer &renderer::get() {
  static renderer object;
  return object;
}

// -----------------------------------------------------------------------------
// Clear + Show
// -----------------------------------------------------------------------------

void renderer::clear() const {
  SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 0);
  SDL_RenderClear(sdl_renderer);
}
void renderer::show() const { SDL_RenderPresent(sdl_renderer); }

// -----------------------------------------------------------------------------
// Draw
// -----------------------------------------------------------------------------

void renderer::draw_rect(const SDL_Rect &rect, const SDL_Color &color) const {
  SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(sdl_renderer, &rect);
}

void renderer::draw_texture(const texture &texture, int x, int y) const {
  int cx{x - (texture.w / 2)};
  int cy{y - (texture.h / 2)};
  SDL_Rect rect{cx, cy, texture.w, texture.h};
  SDL_RenderCopy(sdl_renderer, texture.data, NULL, &rect);
}

// -----------------------------------------------------------------------------
// Resource Management
// -----------------------------------------------------------------------------

texture renderer::load_texture(const font &font, const std::string &text,
                               const SDL_Color &color) const {
  SDL_Surface *surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
  texture texture{
      SDL_CreateTextureFromSurface(renderer::get().sdl_renderer, surface)};
  SDL_FreeSurface(surface);
  return texture;
}
} // namespace sos::video
