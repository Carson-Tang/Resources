#pragma once
#include <bits/stdc++.h>
using namespace std;

// Manber Myers Suffix Array to sort suffixes of a string in lexicographical order
// Time Complexity: O(S log S)
// Memory Complexity: O(S + ALPHABET_SIZE)
template <const int MAXS, const int ALPHABET_SIZE, const int OFFSET> struct ManberMyersSuffixArray {
    int N, ind[MAXS], rnk[MAXS], temp[MAXS], freq[ALPHABET_SIZE], preFreq[ALPHABET_SIZE]; string S;
    void run() {
        N = S.length(); ind[N] = N; rnk[N] = -1; fill(freq, freq + ALPHABET_SIZE, 0); preFreq[0] = 0;
        for (int i = 0; i < N; i++) freq[S[i] - OFFSET]++;
        for (int i = 1; i < ALPHABET_SIZE; i++) preFreq[i] = preFreq[i - 1] + freq[i - 1];
        for (int i = 0; i < N; i++) rnk[i] = preFreq[S[i] - OFFSET];
        for (int i = 0; i < N; i++) ind[preFreq[S[i] - OFFSET]++] = i;
        for (int offset = 1; offset < N; offset += offset) for (int i = 1, cnt = 0; i <= N; i++) {
            if (rnk[ind[i]] == rnk[ind[i - 1]]) cnt++;
            else if (cnt > 0) {
                int l = i - cnt - 1, r = i;
                sort(ind + l, ind + r, [&] (const int &a, const int &b) { return rnk[offset + a] < rnk[offset + b]; });
                int cur = rnk[ind[l]];
                for (int j = l + 1; j < r; j++) {
                    if (rnk[offset + ind[j - 1]] < rnk[offset + ind[j]]) cur = rnk[ind[l]] + j - l;
                    temp[ind[j]] = cur;
                }
                for (int j = l + 1; j < r; j++) rnk[ind[j]] = temp[ind[j]];
                cnt = 0;
            }
        }
    }
    int getind(int i) { return ind[i]; } // ind in original string of the ith smallest suffix
    string select(int i) { return S.substr(ind[i]); } // returns the ith smallest suffix
};
