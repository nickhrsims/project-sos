#pragma once

#include <spdlog/spdlog.h>

#include <sos/video/font.h>
#include <sos/video/renderer.h>
#include <sos/video/texture.h>
#include <sos/video/window.h>

namespace sos::video::renderer::__data__ {
template <uint8_t index> SDL_Renderer* sdl_renderer{nullptr};
}

namespace sos::video::renderer {

// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------

// TODO: Support texture asset caching (including strings from fonts)

template <uint8_t index> void create() {
    SDL_Renderer* sdl_renderer{nullptr};
    spdlog::info("Creating renderer({}).", index);
    if (!window::__data__::sdl_window<index>) {
        spdlog::error("Could not create renderer({}), window({}) is required by "
                      "renderer({}) does not appear to exist.",
                      index, index, index);
    }
    sdl_renderer = SDL_CreateRenderer(window::__data__::sdl_window<index>, index, 0);
    if (!sdl_renderer) {
        spdlog::error("Failed to create renderer({}): {}.", index, SDL_GetError());
        abort();
    }
    __data__::sdl_renderer<index> = sdl_renderer;
}

template <uint8_t index> void destroy() {
    spdlog::info("Destroying renderer({}).", index);
    SDL_DestroyRenderer(__data__::sdl_renderer<index>);
}

template <uint8_t index> void clear() {
    SDL_RenderClear(__data__::sdl_renderer<index>);
}

template <uint8_t index> void show() {
    SDL_RenderPresent(__data__::sdl_renderer<index>);
}

// -----------------------------------------------------------------------------
// Draw
// -----------------------------------------------------------------------------

template <uint8_t index, SdlCompatibleColor Color>
void set_color(const Color& p_color) {
    SDL_SetRenderDrawColor(__data__::sdl_renderer<index>, p_color.r, p_color.g,
                           p_color.b, p_color.a);
}

template <uint8_t index, SdlCompatibleRect Rect> void draw(const Rect& p_rect) {
    SDL_RenderFillRect(__data__::sdl_renderer<index>, &p_rect);
}

template <uint8_t index, SdlCompatiblePoint Position>
void draw(const texture& p_texture, const Position& p_position) {
    int x{p_position.x - (p_texture.w / 2)};
    int y{p_position.y - (p_texture.h / 2)};
    SDL_Rect rect{x, y, p_texture.w, p_texture.h};
    SDL_RenderCopy(__data__::sdl_renderer<index>, p_texture.data, NULL, &rect);
}

// -----------------------------------------------------------------------------
// Resource Management
// -----------------------------------------------------------------------------

template <uint8_t index, SdlCompatibleColor Color>
texture load_texture(const font& font, const Color& color, const std::string& text) {
    SDL_Surface* surface =
        TTF_RenderText_Solid(font.data, text.c_str(), static_cast<SDL_Color>(color));
    texture texture{
        SDL_CreateTextureFromSurface(__data__::sdl_renderer<index>, surface)};
    SDL_FreeSurface(surface);
    return texture;
}
} // namespace sos::video::renderer
