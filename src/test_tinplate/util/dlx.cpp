#define PROBLEM "https://www.luogu.com.cn/problem/P4929"

#include "../../code/util/dlx.hpp"

void solve() {
  u32 n, m;
  std::cin >> n >> m;
  vvec<bool> maps(n, vec<bool>(m));
  for (usz i = 0, x; i < n; ++i)
    for (usz j = 0; j < m; ++j) {
      std::cin >> x;
      maps[i][j] = x;
    }
  auto res = tifa_libs::util::DLX(maps).dance([](auto const&) {});
  if (res.has_value())
    for (auto i : res.value()) std::cout << i << ' ';
  else
    std::cout << "No Solution!";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve();
  return 0;
}

/*
给定一个 $N$ 行 $M$ 列的矩阵, 矩阵中每个元素要么是 $1$, 要么是 $0$

你需要在矩阵中挑选出若干行, 使得对于矩阵的每一列 $j$, 在你挑选的这些行中, 有且仅有一行的第 $j$ 个元素为 $1$

## 输入格式

第一行两个数 $N,M$

接下来 $N$ 行, 每行 $M$ 个数字 $0$ 或 $1$, 表示这个矩阵

## 输出格式

一行输出若干个数表示答案, 两个数之间用空格隔开, 输出任一可行方案均可, 顺序随意

若无解, 输出 `No Solution!`

## 提示

对于 $100\%$ 的数据, $N,M\leq 500$, 保证矩阵中 $1$ 的数量不超过 $5000$ 个
*/

/*
3 3
0 0 1
1 0 0
0 1 0
==========
2 1 3
*/

/*
3 3
1 0 1
1 1 0
0 1 1
================
No Solution!
*/