#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
#include <climits> 
using namespace std; 
#define endl '\n'
#define all(x) begin(x), end(x)
 
void dbg_print(int x) {cerr << x;}
void dbg_print(long x) {cerr << x;}
void dbg_print(long long x) {cerr << x;}
void dbg_print(unsigned x) {cerr << x;}
void dbg_print(unsigned long x) {cerr << x;}
void dbg_print(unsigned long long x) {cerr << x;}
void dbg_print(float x) {cerr << x;}
void dbg_print(double x) {cerr << x;}
void dbg_print(long double x) {cerr << x;}
void dbg_print(char x) {cerr << '\'' << x << '\'';}
void dbg_print(const char *x) {cerr << '\"' << x << '\"';}
void dbg_print(const string &x) {cerr << '\"' << x << '\"';}
void dbg_print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void dbg_print(const pair<T, V> &x) {cerr << '{'; dbg_print(x.first); cerr << ','; dbg_print(x.second); cerr << '}';}
template<typename T>
void dbg_print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), dbg_print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {dbg_print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
template<size_t T>
void dbg_print(bitset<T> b) {cerr << b;}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
 
// ============================================================================================== // 

typedef long long ll;

const int maxn = 5e5 + 500;
int ch[2*maxn*30][2], val[2*maxn*30], tot, rt[maxn];
ll sz[2*maxn*30];
const ll lim = 1e18 + 100;

int new_x() {
    int u = tot++;
    return u;
}
int new_l(int v) {
    int u = new_x();
    sz[u] = 1;
    val[u] = v;
    return u;
}

pair<int, int> cut(int u) {
    return make_pair(ch[u][0], ch[u][1]);
}

void pull(int u) {
    sz[u] = min(lim, sz[ch[u][0]] + sz[ch[u][1]]);
}
int join(int u, int v) {
    int x = new_x();
    ch[x][0] = u;
    ch[x][1] = v;
    pull(x);
    return x;
}
int merge(int u, int v) {
    if (sz[u] == lim) return u;
    if (sz[u] > 3 * sz[v]) {
        auto [x, y] = cut(u);
        if ((sz[y] + sz[v]) > 3 * sz[x]) {
            auto [k, h] = cut(y);
            return merge(merge(x, k), merge(h, v));
        }
        else return merge(x, merge(y, v));
    }
    else if (sz[v] > 3 * sz[u]) {
        auto [x, y] = cut(v);
        if ((sz[x] + sz[u]) > 3 * sz[v]) {
            auto [k, h] = cut(x);
            return merge(merge(u, k), merge(h, y));
        }
        else return merge(merge(u, x), y);
    }
    else return join(u, v);
}

int query(int u, ll cur) {
    if (sz[u] == 1) return val[u];
    if (sz[ch[u][0]] >= cur) return query(ch[u][0], cur);
    else return query(ch[u][1], cur - sz[ch[u][0]]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    rt[0] = new_l(0);
    rt[1] = new_l(1);
    int q; cin >> q;
    for (int i = 2; i < q + 2; i++) {
        int l, r; cin >> l >> r;
        ll x; cin >> x;
        rt[i] = merge(rt[l], rt[r]);
        cout << query(rt[i], x) << endl;
    }
}
