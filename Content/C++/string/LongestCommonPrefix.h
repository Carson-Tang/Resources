#pragma once
#include <bits/stdc++.h>
#include "../datastructures/FischerHeunStructure.h"
using namespace std;

// Computes the longest common prefix of two suffixes of a string
//   be using the Fischer Heun Structure over the LCP array generated by the
//   Suffix Array
// Indices are 0-indexed and ranges are inclusive with the exception of
//   functions that accept two iterators as a parameter, such as
//   the constructor, which are exclusive
// Template Arguments:
//   SuffixArray: a generic suffix array to be used (should be either
//       SuffixArray in SuffixArray.h or SAISSuffixArray in SAISSuffixArray.h)
//     Required Fields:
//       S: a vector of type T representing the string/array
//       rnk: a vector of the ranks of the suffixes (rnk[i] is the rank of the
//         suffix starting from index i)
//       ind: a vector of the indices in the original string of the suffixes
//         sorted in lexicographical order (ind[i] is the index in original
//         string of the ith lexicographically smallest suffix)
//       LCP: a vector of the longest common prefixes between the suffixes when
//         sorted in lexicographical order (LCP[i] is the longest common prefix
//         of the ith and (i + 1)th lexicographically smallest suffix, with
//         LCP[N - 1] being 0)
//     Required Functions:
//       constructor(N, f): construts a suffix array with a string/array of
//         length N with the generating function that returns the ith element
//          on the ith call
// Constructor Arguments:
//   N: the number of elements in the string/array
//   f: a generating function that returns the ith element on the ith call
//   st: an iterator pointing to the first element in the string/array
//   en: an iterator pointing to after the last element in the string/array
// Fields:
//   SA: the associated suffix array constructed from the string/array
// Functions:
//   lcpRnk(i, j): computes the longest common prefix of the ith and jth
//     lexicographically least suffixes
//   lcp(i, j): computes the longest common prefix of the suffixes starting
//     from index i and j
// In practice, the constructor has a very small constant, lcp has a
//   moderate constant, still faster than using segment trees
// Time Complexity:
//   constructor: time complexity of SuffixArray constructor
//   lcpRnk, lcp: O(1)
// Memory Complexity: memory complexity of SuffixArray
// Tested:
//   Fuzz and Stress Tested
//   https://dmoj.ca/problem/ccc20s3
template <class SuffixArray> struct LongestCommonPrefix {
  SuffixArray SA; FischerHeunStructure<int, greater<int>> FHS;
  template <class F> LongestCommonPrefix(int N, F f)
    : SA(N, f), FHS(SA.LCP.begin(), SA.LCP.end()) {}
  template <class It> LongestCommonPrefix(It st, It en)
      : LongestCommonPrefix(en - st, [&] { return *st++; }) {}
  int lcpRnk(int i, int j) {
    if (i > j) swap(i, j);
    return i == j ? int(SA.S.size()) - SA.ind[j] : FHS.query(i, j - 1);
  }
  int lcp(int i, int j) { return lcpRnk(SA.rnk[i], SA.rnk[j]); }
};
