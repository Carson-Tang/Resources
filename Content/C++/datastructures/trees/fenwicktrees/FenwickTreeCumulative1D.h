#pragma once
#include <bits/stdc++.h>
using namespace std;

// Fenwick Tree or Binary Indexed Tree supporting point updates
//   and prefix range queries over a cumulative function, such as max and min,
//   in 1 dimension
// Indices are 0-indexed and ranges are inclusive with the exception of
//   functions that accept two iterators as a parameter, such as
//   the constructor, which are exclusive
// In practice, this version performs as well as the multidimensional version
// Small constant, like most fenwick trees, and faster than segment trees
// Time Complexity:
//   constructor: O(N)
//   update, query: O(log N)
// Memory Complexity: O(N)
// Tested:
//   https://atcoder.jp/contests/dp/tasks/dp_q
//   https://dmoj.ca/problem/ds1
template <class T, class Op> struct FenwickTreeCumulative1D {
  int N; vector<T> BIT; Op op;
  FenwickTreeCumulative1D(int N, T vdef, Op op)
      : N(N), BIT(N + 1, vdef), op(op) {}
  template <class F> FenwickTreeCumulative1D(int N, F f, T vdef, Op op)
      : FenwickTreeCumulative1D(N, vdef, op) {
    for (int i = 1; i <= N; i++) {
      BIT[i] = op(BIT[i], f());
      int j = i + (i & -i); if (j <= N) BIT[j] = op(BIT[j], BIT[i]);
    }
  }
  template <class It> FenwickTreeCumulative1D(It st, It en, T vdef, Op op)
      : FenwickTreeCumulative1D(en - st, [&] { return *st++; }, vdef, op) {}
  void update(int i, T v) {
    for (i++; i <= N; i += i & -i) BIT[i] = op(BIT[i], v);
  }
  T query(int r) {
    T ret = BIT[++r]; while ((r -= r & -r) > 0) ret = op(ret, BIT[r]);
    return ret;
  }
};
