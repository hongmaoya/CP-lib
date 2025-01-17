#ifndef TIFA_LIBS_UTIL_HUFFMAN_TREE
#define TIFA_LIBS_UTIL_HUFFMAN_TREE

#include "util.hpp"

namespace tifa_libs::util {

template <class T = u64>
class huffman {
  struct node {
    T weight;
    vec<usz> ch;
    node(T weight = T{}, usz child_cnt = 0) : weight(weight), ch(child_cnt) {}
  };
  usz cnt_w, cnt_l, ch_sz;
  vec<node> data;

  template <class Res, class Op>
  vec<Res> run(Op operate) const {
    vec<Res> ret(cnt_w);
    std::queue<std::pair<usz, Res>> q;
    q.emplace(data.size() - 1, Res{});
    while (!q.empty()) {
      auto [now_idx, now_code] = q.front();
      auto &ch = data[now_idx].ch;
      q.pop();
      for (usz i = 0; i < ch_sz; ++i) {
        auto &&next_child = ch[i];
        if (next_child < cnt_l) {
          if (next_child < cnt_w) ret[next_child] = operate(now_code, i);
          continue;
        } else q.emplace(next_child, operate(now_code, i));
      }
    }
    return ret;
  }

 public:
  explicit huffman(vec<T> const &weights, usz child_sz = 2) : cnt_w(weights.size()), cnt_l(), ch_sz(child_sz), data() {
    assert(1 < child_sz && child_sz < weights.size());
    for (T now : weights) data.emplace_back(now);
    for (usz i = 0, iend = ((ch_sz - 1) - ((cnt_w - 1) % (ch_sz - 1))) % (ch_sz - 1); i < iend; ++i) data.emplace_back();
    cnt_l = data.size();
    pqg<std::pair<T, usz>> q;
    for (usz i = 0; i < data.size(); ++i) q.emplace(data[i].weight, i);
    while (q.size() > 1) {
      data.emplace_back(T{}, ch_sz);
      for (usz i = 0; i < ch_sz; ++i) {
        auto [now_weight, now_idx] = q.top();
        data.back().weight += now_weight;
        data.back().ch[i] = now_idx;
        q.pop();
      }
      q.emplace(data.back().weight, data.size() - 1);
    }
  }

  vec<std::string> encode(std::string_view char_set = "01") const {
    assert(char_set.size() == ch_sz);
    return run<std::string>([&](const std::string &pre_code, usz idx) { return pre_code + char_set[idx]; });
  }
  vec<usz> depths() const {
    return run<usz>([](const usz &pre_depth, usz) { return pre_depth + 1; });
  }
};

}  // namespace tifa_libs::util

#endif