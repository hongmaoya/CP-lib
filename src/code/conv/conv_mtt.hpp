#ifndef TIFALIBS_CONV_CONV_MTT
#define TIFALIBS_CONV_CONV_MTT

#include "../util/util.hpp"
#include "fft.hpp"

namespace tifa_libs::math {

template <class mint, class FP = f64>
inline vec<mint> conv_mtt(vec<mint> const &l, vec<mint> const &r, usz ans_size) {
  using C = typename FFT<FP>::C;
  static FFT<FP> fft;
  if (l.size() == 1) {
    vec<mint> ans = r;
    ans.resize(ans_size);
    for (auto &i : ans) i *= l[0];
    return ans;
  }
  if (r.size() == 1) {
    vec<mint> ans = l;
    ans.resize(ans_size);
    for (auto &i : ans) i *= r[0];
    return ans;
  }
  fft.bzr(std::max({l.size(), r.size(), std::min(l.size() + r.size() - 1, ans_size)}));
  usz n = fft.size();
  const int OFS = ((int)sizeof(decltype(mint::mod())) * 8 - bit::cntl0(mint::mod() - 1) + 1) / 2;
  const u32 MSK = ((1u << OFS) - 1);
  vec<mint> ans(ans_size);
  vec<C> a(n), b(n);
  for (usz i = 0; i < l.size(); ++i) a[i] = {(FP)(l[i].val() & MSK), (FP)(l[i].val() >> OFS)};
  for (usz i = 0; i < r.size(); ++i) b[i] = {(FP)(r[i].val() & MSK), (FP)(r[i].val() >> OFS)};
  fft.dif(a);
  fft.dif(b);
  {
    vec<C> p(n), q(n);
    for (usz i = 0, j; i < n; ++i) {
      j = (n - i) & (n - 1);
      C da = (a[i] + std::conj(a[j])) * C(.5, 0), db = (a[i] - std::conj(a[j])) * C(0, -.5), dc = (b[i] + std::conj(b[j])) * C(.5, 0), dd = (b[i] - std::conj(b[j])) * C(.5, 0);
      p[j] = da * dc + da * dd;
      q[j] = db * dc + db * dd;
    }
    a = p;
    b = q;
  }
  fft.dif(a);
  fft.dif(b);
  for (usz i = 0; i < ans_size; ++i) {
    i64 da = (i64)(a[i].real() / (FP)n + .5) % mint::mod(), db = (i64)(a[i].imag() / (FP)n + .5) % mint::mod(), dc = (i64)(b[i].real() / (FP)n + .5) % mint::mod(), dd = (i64)(b[i].imag() / (FP)n + .5) % mint::mod();
    ans[i] = da + ((db + dc) << OFS) % mint::mod() + (dd << (OFS * 2)) % mint::mod();
  }
  return ans;
}
template <class mint, class FP = f64>
inline vec<mint> conv_mtt(vec<mint> const &l, vec<mint> const &r) { return conv_mtt<mint, FP>(l, r, l.size() + r.size() - 1); }

}  // namespace tifa_libs::math

#endif