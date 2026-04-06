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

static struct FastInput {
  static constexpr int BUF_SIZE = 1 << 20;
  char buf[BUF_SIZE];
  size_t chars_read = 0;
  size_t buf_pos = 0;
  FILE *in = stdin;
  char cur = 0;

  inline char get_char() {
    if (buf_pos >= chars_read) {
      chars_read = fread(buf, 1, BUF_SIZE, in);
      buf_pos = 0;
      buf[0] = (chars_read == 0 ? -1 : buf[0]);
    }
    return cur = buf[buf_pos++];
  }

  inline void tie(int) {}

  inline explicit operator bool() {
    return cur != -1;
  }

  inline static bool is_blank(char c) {
    return c <= ' ';
  }

  inline bool skip_blanks() {
    while (is_blank(cur) && cur != -1) {
      get_char();
    }
    return cur != -1;
  }

  inline FastInput& operator>>(char& c) {
    skip_blanks();
    c = cur;
    return *this;
  }

  inline FastInput& operator>>(string& s) {
    if (skip_blanks()) {
      s.clear();
      do {
        s += cur;
      } while (!is_blank(get_char()));
    }
    return *this;
  }

  template <typename T>
  inline FastInput& read_integer(T& n) {
    // unsafe, doesn't check that characters are actually digits
    n = 0;
    if (skip_blanks()) {
      int sign = +1;
      if (cur == '-') {
        sign = -1;
        get_char();
      }
      do {
        n += n + (n << 3) + cur - '0';
      } while (!is_blank(get_char()));
      n *= sign;
    }
    return *this;
  }

  template <typename T>
  inline typename enable_if<is_integral<T>::value, FastInput&>::type operator>>(T& n) {
    return read_integer(n);
  }

  #if !defined(_WIN32) || defined(_WIN64)
  inline FastInput& operator>>(__int128& n) {
    return read_integer(n);
  }
  #endif

  template <typename T>
  inline typename enable_if<is_floating_point<T>::value, FastInput&>::type operator>>(T& n) {
    // not sure if really fast, for compatibility only
    n = 0;
    if (skip_blanks()) {
      string s;
      (*this) >> s;
      sscanf(s.c_str(), "%lf", &n);
    }
    return *this;
  }
} fast_input;

#define cin fast_input

static struct FastOutput {
  static constexpr int BUF_SIZE = 1 << 20;
  char buf[BUF_SIZE];
  size_t buf_pos = 0;
  static constexpr int TMP_SIZE = 1 << 20;
  char tmp[TMP_SIZE];
  FILE *out = stdout;

  inline void put_char(char c) {
    buf[buf_pos++] = c;
    if (buf_pos == BUF_SIZE) {
      fwrite(buf, 1, buf_pos, out);
      buf_pos = 0;
    }
  }

  ~FastOutput() {
    fwrite(buf, 1, buf_pos, out);
  }

  inline FastOutput& operator<<(char c) {
    put_char(c);
    return *this;
  }

  inline FastOutput& operator<<(const char* s) {
    while (*s) {
      put_char(*s++);
    }
    return *this;
  }

  inline FastOutput& operator<<(const string& s) {
    for (int i = 0; i < (int) s.size(); i++) {
      put_char(s[i]);
    }
    return *this;
  }

  template <typename T>
  inline char* integer_to_string(T n) {
    // beware of TMP_SIZE
    char* p = tmp + TMP_SIZE - 1;
    if (n == 0) {
      *--p = '0';
    } else {
      bool is_negative = false;
      if (n < 0) {
        is_negative = true;
        n = -n;
      }
      while (n > 0) {
        *--p = (char) ('0' + n % 10);
        n /= 10;
      }
      if (is_negative) {
        *--p = '-';
      }
    }
    return p;
  }

  template <typename T>
  inline typename enable_if<is_integral<T>::value, char*>::type stringify(T n) {
    return integer_to_string(n);
  }

  #if !defined(_WIN32) || defined(_WIN64)
  inline char* stringify(__int128 n) {
    return integer_to_string(n);
  }
  #endif

  template <typename T>
  inline typename enable_if<is_floating_point<T>::value, char*>::type stringify(T n) {
    sprintf(tmp, "%.17f", n);
    return tmp;
  }

  template <typename T>
  inline FastOutput& operator<<(const T& n) {
    auto p = stringify(n);
    for (; *p != 0; p++) {
      put_char(*p);
    }
    return *this;
  }
} fast_output;

#define cout fast_output

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


void solve() {
    int n, q; cin >> n >> q; 
    vector<int> a(n); for (int i = 0; i < n; i++) cin >> a[i]; 

    fenwick_tree<ll> bit; 
    bit.build(a); 

    while (q--) {
        int id; cin >> id; 
        if (id) {
            int l, r; cin >> l >> r; 
            cout << bit.sum(r) - bit.sum(l) << endl;
        } 
        else {
            int p, x; cin >> p >> x; 
            bit.add(p + 1, x); 
        } 
    } 
} 

int main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 

    solve(); 
} 



