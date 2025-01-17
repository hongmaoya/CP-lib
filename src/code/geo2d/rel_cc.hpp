#ifndef TIFA_LIBS_GEO2D_REL_CC
#define TIFA_LIBS_GEO2D_REL_CC

#include "circle.hpp"
#include "dist_pp.hpp"

namespace tifa_libs::geo {

// relation between circle and circle
enum RELCC {
  lyingin_cc,
  touchin_cc,
  intersect_cc,
  touchex_cc,
  lyingout_cc
};

template <class FP>
constexpr RELCC relation_CC(circle<FP> const &c1, circle<FP> const &c2) {
  FP d = dist_PP(c1.o, c2.o);
  if (is_gt(d, c1.r + c2.r)) return lyingout_cc;
  if (is_eq(d, c1.r + c2.r)) return touchex_cc;
  if (is_gt(d, std::abs(c1.r - c2.r))) return intersect_cc;
  if (is_eq(d, std::abs(c1.r - c2.r))) return touchin_cc;
  return lyingin_cc;
}

}  // namespace tifa_libs::geo

#endif