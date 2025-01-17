#ifndef TIFA_LIBS_MATH_BALL_BOX_DDL
#define TIFA_LIBS_MATH_BALL_BOX_DDL

#include "binom.hpp"
#include "gen_pows.hpp"

namespace tifa_libs::math {

template <class mint>
inline mint ball_box_ddl(u32, u32 box, vec<u64> const& pows, Binom<mint> const& binom) {
  mint ans = 0;
  bool f = box & 1;
  for (u32 i = 1; i <= box; ++i) {
    f ? (ans += binom.mCn(box, i) * pows[i]) : (ans -= binom.mCn(box, i) * pows[i]);
    f ^= 1;
  }
  return ans;
}
template <class mint>
inline mint ball_box_ddl(u32 ball, u32 box, Binom<mint> const& binom) { return ball_box_ddl<mint>(ball, box, gen_pows(box + 1, ball, mint::mod()), binom); }

}  // namespace tifa_libs::math

#endif