#pragma once

#include "SDL_rect.h"

#include "vector2.h"

namespace sos::demo {

/**
 * A.k.a "Axis-Aligned Bounding Box", and all that implies.
 *
 * A simple wrapper around SDL_Rect.
 * Rect specialization for position, size, and collision geometry.
 *
 * The "origin" from the perspective of the API is the center of the Rect.
 *
 * TODO: Tests
 */
struct rect : public SDL_Rect {
  inline rect();
  inline rect(int x, int y, int w, int h);

  inline rect(const rect &rhs);
  inline rect(const rect &&rhs);

  inline rect &operator=(const rect &rhs);
  inline rect &operator=(const rect &&rhs);

  /**
   * Returns the Minkowski Sum between Rects.
   */
  inline const rect operator+(const rect &rhs) const;

  /**
   * Returns the Minkowski Difference between Rects.
   */
  inline const rect operator-(const rect &rhs) const;

  /**
   * Get center position.
   */
  inline vector2 center() const;

  /**
   * The geometric spatial-difference between two convex polygons.
   * Carries some interesting properties that allow it to be used for
   * collision detection.
   */
  inline const rect minkowski_difference(const rect &other) const;

  /**
   * Does the given point line within the boundaries of this Rect?
   */
  inline bool has_point(int x, int y) const;

  /**
   * Describes the results of an intersection checks.
   */
  enum class intersection_result {
    none = 0,
    from_left,
    from_above,
    from_right,
    from_below,
  };

  /**
   * Return the edge of `this` most overlapped by the `other` rectangle.
   * Will return `none` of no overlap occurs, and can be cast safely to false.
   *
   * The results returned provide the most likely direction of "incoming"
   * intersections in terms of spatial motion. This is ultimately a heuristic
   * that does not account for motion-in-time, meaning only _current_
   * intersections can be identified using this.
   */
  inline intersection_result is_intersecting(const rect &other) const;
};

} // namespace sos::demo

#include "rect.ipp"
