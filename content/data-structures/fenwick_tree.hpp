/*
 * Author: 
 * Date: 
 * License: 
 * Source: 
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: 
 */
#pragma once

template <typename T>
struct fenwick_tree {
    vector<T> bit;
    int n;
    const int neutral = 0;

    void build(int _n) {
        n = _n;
        bit.assign(n + 1, neutral);
    }

    template <typename U>
    void build(vector<U> &a) {
        n = a.size();
        bit.assign(n + 1, neutral);
        for (int i = 0; i < n; i++) bit[i+1] = a[i];
        for (int i = 1; i <= n; i++) {
            if (i + (i & -i) <= n) bit[i + (i&-i)] += bit[i];
        }
    }

    T sum(int r) {
        T ret = 0;
        for (; r > 0; r -= r&-r) ret += bit[r];
        return ret;
    }
    void add(int i, T val) {
        for (; i <= n; i += i&-i) bit[i] += val;
    }
};

