#ifndef TIFA_LIBS_STR_SUFFIX_ARRAY
#define TIFA_LIBS_STR_SUFFIX_ARRAY

#include "../util/util.hpp"

namespace tifa_libs::str {
template <typename T = std::string>
class suffixarray {
  T s;

 public:
  vec<u32> sa, rk, height;
  // s must start from 1
  suffixarray(T s_) : s(s_), sa(s.size()), rk(s.size()) {
    u32 n = u32(s.size() - 1), m = 0, p;
    for (auto x : s_) m = std::max(m, u32(x));
    vec<u32> oldrk(n + n + 1), id(n + 1), cnt(m + 1, 0);
    for (u32 i = 1; i <= n; ++i) ++cnt[rk[i] = u32(s[i])];
    for (u32 i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (u32 i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

    for (u32 w = 1;; w *= 2, m = p) {
      p = 0;
      for (u32 i = n; i > n - w; --i) id[++p] = i;
      for (u32 i = 1; i <= n; ++i)
        if (sa[i] > w) id[++p] = sa[i] - w;

      cnt = vec<u32>(m + 1, 0);
      for (u32 i = 1; i <= n; ++i) ++cnt[rk[id[i]]];
      for (u32 i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
      for (u32 i = n; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];
      std::copy(rk.begin(), rk.end(), oldrk.begin());
      p = 0;
      for (u32 i = 1; i <= n; ++i) {
        u32 x = sa[i], y = sa[i - 1];
        rk[x] = oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w] ? p : ++p;
      }
      if (p == n) break;
    }
  }
  void get_height() {
    u32 n = s.size() - 1;
    vec<u32> height(n + 1);
    for (u32 i = 1, k = 0; i <= n; ++i) {
      if (rk[i] == 1) continue;
      if (k) --k;
      while (i + k <= n && s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
      height[rk[i]] = k;
    }
  }
  /*
    s.substr(begs) := s[begs..s.size() - 1]
    -1:  t > s.substr
    0 :  t == s.substr
    1 :  t < s.substr, t is a prefix of s.substr
    2 :  t < s.substr, t isn't prefix of s.substr
  */
  i32 compare_substr(T t, u32 begs = 1, u32 begt = 1) {
    while (begs < s.size() && begt < t.size()) {
      if (t[begt] > s[begs]) return -1;
      if (t[begt] < s[begs]) return 2;
      ++begs, ++begt;
    }
    return begs == s.size() && begt == t.size() ? 0 : (begt >= t.size() ? 1 : -1);
  }
  u32 lower_bound(T t) {  // the smallest rank of suffix that is greater than or equal t
    u32 l = 1, r = u32(s.size() - 1), ret = u32(s.size());
    while (r >= l) {
      u32 mid = l + (r - l) / 2;
      if (compare_substr(t, sa[mid]) < 0) l = mid + 1;
      else r = mid - 1, ret = mid;
    }
    return ret;
  }
  u32 upper_bound(T t) {  // the smallest rank of suffix that is greater than t and t isn't prefix of that
    u32 l = 1, r = u32(s.size() - 1), ret = u32(s.size());
    while (r >= l) {
      u32 mid = l + (r - l) / 2;
      if (compare_substr(t, sa[mid]) <= 1) l = mid + 1;
      else r = mid - 1, ret = mid;
    }
    return ret;
  }
  u32 frequency(T t) {
    return upper_bound(t) - lower_bound(t);
  }
};

}  // namespace tifa_libs::str

#endif