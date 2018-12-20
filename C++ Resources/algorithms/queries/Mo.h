#pragma once
#include <bits/stdc++.h>
using namespace std;

// Mo's algorithm, used to count the number of distinct integers in a subarray
// Time Complexity: O(N + Q log Q + Q * max(B, Q / B) * (update complexity))
// Memory Complexity: O(N + Q)
template <const int MAXN, const int MAXQ, const int BLOCKSZ> struct Mo {
    struct Query {
        int l, r, ind, block;
        bool operator < (const Query &q) const { return block == q.block ? r < q.r : block < q.block; }
    };
    int Q = 0, cnt[MAXN], ans[MAXQ], val[MAXN], temp[MAXN], curAns; Query q[MAXQ];
    void query(int l, int r) { q[Q] = {l, r, Q, l / BLOCKSZ}; Q++; }
    void add(int x) { if (cnt[x]++ == 0) curAns++; }
    void rem(int x) { if (--cnt[x] == 0) curAns--; }
    void run(int N) {
        fill(cnt, cnt + N, 0); copy(val, val + N, temp); sort(temp, temp + N); int k = unique(temp, temp + N) - temp;
        for (int i = 0; i < N; i++) val[i] = lower_bound(temp, temp + k, val[i]) - temp;
        sort(q, q + Q); int l = q[0].l, r = l - 1; curAns = 0;
        for (int i = 0; i < Q; i++) {
            while (l < q[i].l) rem(val[l++]);
            while (l > q[i].l) add(val[--l]);
            while (r < q[i].r) add(val[++r]);
            while (r > q[i].r) rem(val[r--]);
            ans[q[i].ind] = curAns;
        }
    }
    void clear() { Q = 0; }
};
