/**
 * Author: Enzo de Almeida 
 * Date: 2025-06-19
 * License: 
 * Source: 
 * Description: 
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

#include "../data-structures/SegmentTreeLazy.h"

const int maxn = 2e5 + 50;
int a[maxn];
vector<int> adj[maxn];
Seg seg; // built in main

struct hld {
    int tin[maxn], tout[maxn], par[maxn], head[maxn], eul[maxn], sz[maxn], T;

    hld() {}
    void dfs(int u, int p = -1) {
        sz[u] = 1;
        par[u] = p;
        if (par[u] > -1) adj[u].erase(find(adj[u].begin(), adj[u].end(), par[u]));
        for (int& v : adj[u]) {
            dfs(v, u);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
        }
    }
    void dfs_hld(int u) {
        tin[u] = T++;
        eul[tin[u]] = u;
        for (int v : adj[u]) {
            head[v] = v == adj[u][0] ? head[u] : v;
            dfs_hld(v);
        }
        tout[u] = T;
    }

    void build() {
        dfs(0);
        dfs_hld(0);
        seg.build(T, a, eul);
    }

    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (tin[u] < tin[v]) swap(u, v);
            u = par[head[u]];
        }
        if (tin[u] < tin[v]) swap(u, v);
        return u;
    }

    ll query(int u, int v) {
        ll uans = 0, vans = 0;
        while (head[u] != head[v]) {
            if (tin[u] > tin[v]) {
                uans += seg.query(tin[head[u]], tin[u]);
                u = par[head[u]];
            }
            else {
                vans += seg.query(tin[head[v]], tin[v]);
                v = par[head[v]];
            }
        }
        if (tin[u] < tin[v]) vans += seg.query(tin[u], tin[v]);
        else uans += seg.query(tin[v], tin[u]);

        return uans + vans;
    }

    void update(int u, int val) {
        seg.update(tin[u], val);
    }
} hld;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);


    int n, q; cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n-1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    seg.build(n);
    hld.build();

    while (q--) {
        int id; cin >> id;
        if (id == 1) {
            int u, x; cin >> u >> x; u--;
            hld.update(u, x);
        }
        else {
            int u; cin >> u; u--;
            cout << hld.query(u, 0) << endl;
        }
    }
}
// https://cses.fi/problemset/task/1138

