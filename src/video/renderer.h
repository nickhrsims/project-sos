#pragma once

#include "SDL2/SDL.h"

#include "font.h"
#include "texture.h"
#include "window.h"

namespace sos::video::renderer {

template <uint8_t index = 0> void create();

template <uint8_t index = 0> void destroy();

template <uint8_t index = 0> void clear();

template <uint8_t index = 0> void show();

template <uint8_t index = 0, typename Color> void set_color(const Color &color);

template <uint8_t index = 0, typename Rect> void draw(const Rect &rect);

template <uint8_t index = 0, typename Position>
void draw(const texture &texture, const Position &position);

template <uint8_t index = 0, typename Color>
texture load_texture(const font &font, const Color &color,
                     const std::string &text);

} // namespace sos::video::renderer

#include "renderer.ipp"
