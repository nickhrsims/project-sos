#pragma once

#include <spdlog/spdlog.h>

#include <sos/video/font.h>

namespace sos::video {

inline font::font(const std::string path, const int size)
    : data{TTF_OpenFont(path.c_str(), size)} {
    if (!data) {
        spdlog::error("Cannot load font data: {}.", TTF_GetError());
        abort();
    }
}
inline font::~font() { TTF_CloseFont(data); }

inline font::font(font&& other) {
    data       = other.data;
    other.data = nullptr;
}

inline font& font::operator=(font&& rhs) {
    if (data) {
        TTF_CloseFont(data);
    }
    data     = rhs.data;
    rhs.data = nullptr;
    return *this;
}

} // namespace sos::video
