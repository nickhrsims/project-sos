#include "vector2.h"

namespace sos::demo {

vector2::vector2() : x{0}, y{0} {}

vector2::vector2(int p_x, int p_y) : x{p_x}, y{p_y} {}

bool vector2::is_origin() const { return !(x || y); }

bool vector2::operator_bool() const { return x || y; }

vector2 vector2::operator+(const vector2 &rhs) const {
  return vector2{x + rhs.x, y + rhs.y};
}

vector2 vector2::operator-(const vector2 &rhs) const {
  return vector2{x - rhs.x, y - rhs.y};
}

vector2 vector2::operator*(const vector2 &rhs) const {
  return vector2{x * rhs.x, y * rhs.y};
}

vector2 vector2::operator/(const vector2 &rhs) const {
  return vector2{x / rhs.x, y / rhs.y};
}

} // namespace sos::demo
