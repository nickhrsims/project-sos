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

  vector2();
  vector2(int x, int y);

  bool is_origin() const;
  bool operator_bool() const;
  vector2 operator+(const vector2 &rhs) const;
  vector2 operator-(const vector2 &rhs) const;
  vector2 operator*(const vector2 &rhs) const;
  vector2 operator/(const vector2 &rhs) const;
};

} // namespace sos::demo
