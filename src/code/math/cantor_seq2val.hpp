#ifndef TIFA_LIBS_MATH_CANTOR_SEQ2VAL
#define TIFA_LIBS_MATH_CANTOR_SEQ2VAL

#include "../comb/fact_mod_gen.hpp"

namespace tifa_libs::math {

inline u64 cantor_seq2val(vec<u32> const &s, vec<u64> const &fact, u64 mod = (u64)-1) {
  usz n = s.size();
  u64 ret = 1;
  for (u64 i = 0; i < n; ++i) (ret += mul_mod_u(s[i], fact[n - i - 1], mod)) %= mod;
  return ret;
}
inline u64 cantor_seq2val(vec<u32> const &s, u64 mod = (u64)-1) { return cantor_seq2val(s, fact_mod_gen(s.size(), mod), mod); }

}  // namespace tifa_libs::math

#endif