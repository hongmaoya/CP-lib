#ifndef TIFA_LIBS_MATH_MAT_RK
#define TIFA_LIBS_MATH_MAT_RK

#include "../util/util.hpp"

namespace tifa_libs::math {

template <class Mat, class Ge>
inline u64 rank(Mat const &mat, Ge ge) { return (u64)abs(ge(Mat(mat), false)); }

}  // namespace tifa_libs::math

#endif