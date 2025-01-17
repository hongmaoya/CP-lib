#ifndef TIFA_LIBS_GEO3D_LINE3D
#define TIFA_LIBS_GEO3D_LINE3D

#include "point3d.hpp"

namespace tifa_libs::geo {

template <class FP>
struct line3d {
  point3d<FP> l, r;
  explicit constexpr line3d(point3d<FP> const &s, point3d<FP> const &t) : l(s), r(t) {}

  friend std::istream &operator>>(std::istream &is, line3d &l) { return is >> l.l >> l.r; }
  friend std::ostream &operator<<(std::ostream &os, line3d const &l) { return os << l.l << ' ' << l.r; }
};

}  // namespace tifa_libs::geo

#endif