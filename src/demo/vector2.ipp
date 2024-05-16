#pragma once
#include "vector2.h"

namespace sos::demo {

inline vector2::vector2() : x{0}, y{0} {}

inline vector2::vector2(int p_x, int p_y) : x{p_x}, y{p_y} {}

inline bool vector2::is_origin() const { return !(x || y); }

inline bool vector2::operator_bool() const { return x || y; }

inline vector2 vector2::operator+(const vector2 &rhs) const {
  return vector2{x + rhs.x, y + rhs.y};
}

inline vector2 vector2::operator-(const vector2 &rhs) const {
  return vector2{x - rhs.x, y - rhs.y};
}

inline vector2 vector2::operator*(const vector2 &rhs) const {
  return vector2{x * rhs.x, y * rhs.y};
}

inline vector2 vector2::operator/(const vector2 &rhs) const {
  return vector2{x / rhs.x, y / rhs.y};
}

} // namespace sos::demo
