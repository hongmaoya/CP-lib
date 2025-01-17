#ifndef TIFA_LIBS_STR_KMP
#define TIFA_LIBS_STR_KMP

#include "../util/util.hpp"

namespace tifa_libs::str {

// @return nxt of pattern
inline vec<i32> kmp_nxt(std::string_view pattern) {
  i32 n = (i32)pattern.size();
  vec<i32> nxt((u32)n);
  i32 i, j;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
  for (nxt[0] = j = -1, i = 1; i < n; nxt[i++] = j) {
    while (~j && pattern[j + 1] != pattern[i]) j = nxt[j];
    if (pattern[j + 1] == pattern[i]) ++j;
  }
#pragma GCC diagnostic pop
  return nxt;
}

// find pattern in text
// @return matched position in s
inline vec<u32> kmp(std::string_view pattern, std::string_view text) {
  vec<i32> nxt = kmp_nxt(pattern);
  vec<u32> ret;
  i32 n = (i32)pattern.size(), m = (i32)text.size();
  i32 i, j;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
  for (j = -1, i = 0; i < m; ++i) {
    while (~j && pattern[j + 1] != text[i]) j = nxt[j];
    if (pattern[j + 1] == text[i]) ++j;
    if (j == n - 1) {
      ret.push_back(i - n + 1);
      j = nxt[j];
    }
  }
#pragma GCC diagnostic pop
  return ret;
}

}  // namespace tifa_libs::str

#endif