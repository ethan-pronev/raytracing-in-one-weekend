#pragma once

#include "vec3.h"

class ray {
  private:
    point3 orig;
    vec3 dir;

  public:
    constexpr ray() {}
    constexpr ray(const point3 &origin, const vec3 &direction): orig{origin}, dir{direction} {}

    inline point3 origin() const { return orig; }
    inline point3 direction() const { return dir; }

    inline point3 at(double t) const { return orig + t*dir; }
};
