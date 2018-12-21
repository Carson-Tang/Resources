#pragma once
#include <bits/stdc++.h>
using namespace std;

// Metrix data structure
template <class T> struct Matrix : vector<vector<T>> {
    int N, M; Matrix(int N, int M) : N(N), M(M) { for (int i = 0; i < N; i++) this->push_back(vector<T>(M, 0)); }
};

// Returns the identiy matrix of dimension N
// Time Complexity: O(N^2)
template <class T> Matrix<T> identity(int N) {
    Matrix<T> A(N, N);
    for (int i = 0; i < N; i++) A[i][i] = 1;
    return A;
}

// Returns A + B
// Time Complexity: O(N^2)
template <class T> Matrix<T> add(const Matrix<T> &A, const Matrix<T> &B) {
    assert(A.N == B.N && A.M == B.M); Matrix<T> C(A.N, A.M);
    for (int i = 0; i < C.N; i++) for (int j = 0; j < C.M; j++) C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Returns A - B
// Time Complexity: O(N^2)
template <class T> Matrix<T> sub(const Matrix<T> &A, const Matrix<T> &B) {
    assert(A.N == B.N && A.M == B.M); Matrix<T> C(A.N, A.M);
    for (int i = 0; i < C.N; i++) for (int j = 0; j < C.M; j++) C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Returns A * B
// Time Complexity: O(N^3)
template <class T> Matrix<T> times(const Matrix<T> &A, const Matrix<T> &B) {
    assert(A.M == B.N); Matrix<T> C(A.N, B.M);
    for (int i = 0; i < A.N; i++) for (int j = 0; j < B.M; j++) for (int k = 0; k < A.M; k++) C[i][j] += A[i][k] * B[k][j];
    return C;
}

// Returns A ^ pow
// Time Complexity: O(N^3 log pow)
template <class T> Matrix<T> pow(const Matrix<T> &A, long long pow) {
    assert(A.N == A.M);
    Matrix<T> x = identity(A.N), y = A;
    for (; pow > 0; pow /= 2, y = times(y, y)) if (pow % 2 == 1) x = times(x, y);
    return x;
}

// Determinant
// Time Complexity: O(N^3)
template <class T> T det(Matrix<T> &A) {
    T ret = 1;
    for (int i = 0; i < A.N; i++) {
        int mx = i;
        for (int j = i + 1; j < A.N; j++) if (A[j][i] > A[mx][i]) mx = j;
        if (i != mx) {
            ret = -ret;
            A[i].swap(A[mx]);
        }
        for (int j = i + 1; j < A.N; j++) {
            T alpha = A[j][i] / A[i][i];
            for (int k = i + 1; k < A.N; k++) A[j][k] -= alpha * A[i][k];
        }
    }
    for (int i = 0; i < A.N; i++) ret *= A[i][i];
    return ret;
}