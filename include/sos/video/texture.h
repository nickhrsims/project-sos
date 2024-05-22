#pragma once

#include <SDL.h>

namespace sos::video {

// TODO: Tests
struct texture {
    // --- Constructors, Destructor, Operators
    inline ~texture();
    inline texture(SDL_Texture* sdl_texture);
    inline texture(texture&& other);
    inline texture& operator=(texture&& rhs);
    // --- Disable copy
    inline texture(const texture&)            = delete;
    inline texture& operator=(const texture&) = delete;

    // --- Member Functions
    inline void set_alpha(unsigned char alpha);
    inline void reset_alpha();

    // --- Data Members
    SDL_Texture* data;
    int w;
    int h;
};
} // namespace sos::video

#include <sos/video/texture.ipp>
