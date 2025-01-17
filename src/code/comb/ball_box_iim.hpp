#ifndef TIFA_LIBS_MATH_BALL_BOX_IIM
#define TIFA_LIBS_MATH_BALL_BOX_IIM

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class mint>
constexpr mint ball_box_iim(u32 ball, u32 box) { return box >= ball; }

}  // namespace tifa_libs::math

#endif