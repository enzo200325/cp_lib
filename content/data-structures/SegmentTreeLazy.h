/**
 * Author: Enzo de Almeida 
 * Date: 2025-06-19
 * License: CC0
 * Source: me
 * Description:
 * Time: O(\log N).
 * Usage: 
 * Status: 
 */
#pragma once

struct Seg {
    Seg() {} 
    vector<int> seg; 
    int n; 

    void build_aux(int p, int l, int r, vector<int>& a) {
        if (l == r) {
            seg[p] = a[l]; 
            return; 
        } 
        int mid = l + r >> 1; 
        build_aux(p<<1, l, mid, a); 
        build_aux(p<<1|1, mid+1, r, a); 
    } 
    void build(vector<int>& a) {
        n = a.size(); 
        build_aux(1, 0, n-1, a); 
    } 
    void build(int _n) {
        n = _n; 
        seg.assign(4*n, 0);
    } 

    int query(int p, int l, int r, int L, int R) {
        if (l > R || r < L) return 0;
        if (l >= L && r <= R) return seg[p];
        int mid = l + r >> 1; 
        int q1 = query(p<<1, l, mid, L, R); 
        int q2 = query(p<<1|1, mid+1, r, L, R); 
        return q1 + q2; 
    } 
    int query(int l, int r) {
        return query(1, 0, n-1, l, r);
    } 

    void update(int p, int l, int r, int i, int val) {
        if (l == r) {
            seg[p] += val; 
            return; 
        } 

        int mid = l + r >> 1; 
        if (i <= mid) update(p<<1, l, mid, i, val); 
        else update(p<<1|1, mid+1, r, i, val); 
        seg[p] = seg[p<<1] + seg[p<<1|1]; 
    } 
    void update(int i, int val) {
        update(1, 0, n-1, i, val);
    } 
};  

