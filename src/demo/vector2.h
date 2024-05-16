#pragma once

namespace sos::demo {

/**
 * 2-Dimensional Vector.
 * Can be used as a point, velocity, size, etc.
 *
 * TODO: Tests
 */
struct vector2 {
  int x;
  int y;

  inline vector2();
  inline vector2(int x, int y);

  inline bool is_origin() const;
  inline bool operator_bool() const;
  inline vector2 operator+(const vector2 &rhs) const;
  inline vector2 operator-(const vector2 &rhs) const;
  inline vector2 operator*(const vector2 &rhs) const;
  inline vector2 operator/(const vector2 &rhs) const;
};

} // namespace sos::demo

#include "vector2.ipp"
