#ifndef TIFALIBS_POLY_MPE
#define TIFALIBS_POLY_MPE

#include "poly_inv.hpp"
#include "poly_shr.hpp"

namespace tifa_libs::math {

// Multi-point evaluation based on Tellegen's Principle
// @return {f(a[0]), f(a[1]), ..., f(a.back())}
template <class T>
inline poly<T> poly_mpe(poly<T> f, poly<T> a) {
  class SegTree {
    vec<poly<T>> t;

    constexpr void init_(poly<T> const &a, usz k, usz l, usz r) {
      if (l == r) {
        t[k] = poly<T>{1, -a[l]};
        return;
      }
      usz m = l + (r - l) / 2;
      init_(a, k * 2, l, m);
      init_(a, k * 2 + 1, m + 1, r);
      t[k] = t[k * 2] * t[k * 2 + 1];
    }
    constexpr static poly<T> mult(poly<T> const &f, poly<T> g) {
      usz m = g.size();
      g.reverse();
      g.conv(f);
      g = poly_shr(g, m - 1);
      g.resize(f.size());
      return g;
    }
    constexpr void calc_(poly<T> f, poly<T> &res, usz k, usz l, usz r) const {
      f.resize(r - l + 1);
      if (l == r) {
        res[l] = f[0];
        return;
      }
      usz m = l + (r - l) / 2;
      calc_(mult(f, t[k * 2 + 1]), res, k * 2, l, m);
      calc_(mult(f, t[k * 2]), res, k * 2 + 1, m + 1, r);
    }

   public:
    explicit constexpr SegTree(poly<T> const &a) : t(a.size() * 4) { init_(a, 1, 0, a.size() - 1); }

    constexpr poly<T> operator()(poly<T> const &f) const {
      poly<T> res(f.size());
      calc_(mult(f, poly_inv(t[1])), res, 1, 0, t.size() / 4 - 1);
      return res;
    }
  };

  usz n = f.size(), m = a.size();
  f.resize(std::max(n, m));
  a.resize(std::max(n, m));
  auto _ = SegTree(a)(f);
  _.resize(m);
  return _;
}

}  // namespace tifa_libs::math

#endif