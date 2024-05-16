#pragma once

#include <algorithm>
#include <stdexcept>

#include "rect.h"

namespace sos::demo {

// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

inline rect::rect() : SDL_Rect{0, 0, 0, 0} {}
inline rect::rect(int p_x, int p_y, int p_w, int p_h)
    : SDL_Rect{p_x, p_y, p_w, p_h} {}
inline rect::rect(const rect &rhs) : SDL_Rect{rhs.x, rhs.y, rhs.w, rhs.h} {}
inline rect::rect(const rect &&rhs) : SDL_Rect{rhs.x, rhs.y, rhs.w, rhs.h} {}

// -----------------------------------------------------------------------------
// Operators
// -----------------------------------------------------------------------------

// Copy Assignment
inline rect &rect::operator=(const rect &rhs) {
  this->x = rhs.x;
  this->y = rhs.y;
  this->w = rhs.w;
  this->h = rhs.h;
  return *this;
}

// Move Assignment
inline rect &rect::operator=(const rect &&rhs) {
  this->x = rhs.x;
  this->y = rhs.y;
  this->w = rhs.w;
  this->h = rhs.h;
  return *this;
}

// Sum (Minkowski Sum)
inline const rect rect::operator+(const rect &rhs) const {
  return rect{
      x + (rhs.x + rhs.w),
      y + (rhs.y + rhs.h),
      w + rhs.w,
      h + rhs.h,
  };
}

// Difference (Minkowski Difference)
inline const rect rect::operator-(const rect &rhs) const {
  return rect{
      x - (rhs.x + rhs.w),
      y - (rhs.y + rhs.h),
      w + rhs.w,
      h + rhs.h,
  };
}

// -----------------------------------------------------------------------------
// Public API Implementation
// -----------------------------------------------------------------------------

inline const rect rect::minkowski_difference(const rect &p_other) const {
  return *this - p_other;
}

inline vector2 rect::center() const { return vector2{x + w / 2, y + h / 2}; }

inline bool rect::has_point(int p_x, int p_y) const {
  int left = x;
  int top = y;
  int right = x + w;
  int bottom = y + h;

  return (left < p_x && p_x < right && top < p_y && p_y < bottom);
}

inline rect::intersection_result
rect::is_intersecting(const rect &p_other) const {
  rect minkowski{minkowski_difference(p_other)};

  // If the minkowski box doesn't surround the origin, then the composing rects
  // are not intersecting.
  if (!minkowski.has_point(0, 0)) {
    return intersection_result::none;
  }

  int left = std::abs(minkowski.x);
  int top = std::abs(minkowski.y);
  int right = std::abs(minkowski.x + minkowski.w);
  int bottom = std::abs(minkowski.y + minkowski.h);

  // TODO: Remove branch via. culling
  int closest_edge{std::min({left, right, top, bottom})};

  // TODO: Refactor to provide collision vector for simplified resolution.
  if (closest_edge == left) {
    return intersection_result::from_left;
  }
  if (closest_edge == right) {
    return intersection_result::from_right;
  }
  if (closest_edge == top) {
    return intersection_result::from_above;
  }
  if (closest_edge == bottom) {
    return intersection_result::from_below;
  }

  return intersection_result::none;
}

} // namespace sos::demo
