#pragma once

#include "SDL2/SDL.h"

#include <sos/video/color.h>
#include <sos/video/font.h>
#include <sos/video/texture.h>
#include <sos/video/window.h>

namespace sos::video::renderer {

// -----------------------------------------------------------------------------
// Concepts
// -----------------------------------------------------------------------------

template <typename T>
concept SdlCompatibleRect = std::is_base_of<SDL_Rect, T>::value;

template <typename T>
concept SdlCompatibleColor = std::is_base_of<SDL_Color, T>::value;

template <typename T>
concept SdlCompatiblePoint = std::is_base_of<SDL_Point, T>::value;

// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------

template <uint8_t index = 0> void create();

template <uint8_t index = 0> void destroy();

template <uint8_t index = 0> void clear();

template <uint8_t index = 0> void show();

template <uint8_t index = 0, SdlCompatibleColor Color>
void set_color(const Color& color);

template <uint8_t index = 0, SdlCompatibleRect Rect> void draw(const Rect& rect);

template <uint8_t index = 0, SdlCompatiblePoint Position>
void draw(const texture& texture, const Position& position);

template <uint8_t index = 0, SdlCompatibleColor Color>
texture load_texture(const font& font, const Color& color, const std::string& text);

} // namespace sos::video::renderer

#include <sos/video/renderer.ipp>
