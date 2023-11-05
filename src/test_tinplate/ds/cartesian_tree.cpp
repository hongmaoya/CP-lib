#define PROBLEM "https://judge.yosupo.jp/problem/cartesian_tree/"

#include "../../code/ds/cartesian_tree.hpp"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  u32 n;
  std::cin >> n;
  vec<i32> a(n);
  for(auto &x: a) std::cin >> x;
  tifa_libs::ds::cartesian_tree tr(a);
  i64 retl = 0, retr = 0;
  for(u32 i = 0; i < n; ++ i) {
    retl ^= 1ll * (i + 1) * (tr.t[i].son[0] != -1u ? tr.t[i].son[0] + 2 : 1);
    retr ^= 1ll * (i + 1) * (tr.t[i].son[1] != -1u ? tr.t[i].son[1] + 2 : 1);
  }
  std::cout << retl << ' ' << retr << '\n';
  return 0;
}

/*
# 【模板】笛卡尔树

## 题目描述

给定一个 1 ~ n 的排列 p，构建其笛卡尔树。


即构建一棵二叉树，满足：

1. 每个节点的编号满足二叉搜索树的性质。
2. 节点 i 的权值为 p_i，每个节点的权值满足小根堆的性质。

## 输入格式

第一行一个整数 n。

第二行一个排列 p_{1 \dots n}。

## 输出格式

设 l_i,r_i 分别表示节点 i 的左右儿子的编号（若不存在则为 0）。

一行两个整数，分别表示 \operatorname{xor}_{i = 1}^n i \times (l_i + 1) 和 \operatorname{xor}_{i = 1}^n i \times (r_i + 1)。

## 样例 #1

### 样例输入 #1

```
5
4 1 3 2 5
```

### 样例输出 #1

```
19 21
```

## 提示

【样例解释】

| i | l_i | r_i |
| :-: | :-: | :-: |
| 1 | 0 | 0 |
| 2 | 1 | 4 |
| 3 | 0 | 0 |
| 4 | 3 | 5 |
| 5 | 0 | 0 |

【数据范围】

对于 30% 的数据，n <= 10^3。

对于 60% 的数据，n <= 10^5。

对于 80% 的数据，n <= 10^6。

对于 90% 的数据，n <= 5 * 10^6。

对于 100% 的数据，1 <= n <= 10^7。
*/