#ifndef TIFA_LIBS_GEO2D_TAN_CP
#define TIFA_LIBS_GEO2D_TAN_CP

#include "circle.hpp"

namespace tifa_libs::geo {

// tagante points of point to circle
// maybe duplicate
template <class FP>
std::optional<ptt<point<FP>>> tan_CP(circle<FP> const &c, point<FP> const &p) {
  point v = p - c.o;
  FP x = v.norm2(), d = x - c.r * c.r;
  if (is_neg(d)) return {};
  point q1 = c.o + v * (c.r * c.r / x);
  point q2 = v.do_rot90() * (c.r * std::sqrt(d) / x);
  // counter clock-wise
  return ptt<point<FP>>{q1 - q2, q1 + q2};
}

}  // namespace tifa_libs::geo

#endif