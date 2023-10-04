#ifndef TIFA_LIBS_GEO2D_MAKE_P_POLAR
#define TIFA_LIBS_GEO2D_MAKE_P_POLAR

#include "point.hpp"

namespace tifa_libs::geo2d {

template <class FP>
constexpr point<FP> make_P_polar(FP r, FP theta) { return point{r * std::cos(theta), r * std::sin(theta)}; }

}  // namespace tifa_libs::geo2d

#endif