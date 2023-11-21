#include <vector>
using namespace std;

// https://codeforces.com/blog/entry/18051
struct Segtree {
    int n;
    vector<int> t;
    Segtree(int n) : n(n), t(n*2) {}  // [0, n)
    Segtree(vector<int> &d) {
        n = d.size();
        t.resize(n);
        t.insert(t.end(), d.begin(), d.end());
        for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
    }
    // Point update, range query
    void modify(int p, int value) {  // set value at position p
      for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
    }

    int query(int l, int r) {  // sum on interval [l, r)
      int res = 0;
      for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) res += t[l++];
        if (r&1) res += t[--r];
      }
      return res;
    }

    ////////////////////////////////////
    // Range update, Point query
    void modify(int l, int r, int value) {
      for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) t[l++] += value;
        if (r&1) t[--r] += value;
      }
    }

    int query(int p) {
      int res = 0;
      for (p += n; p > 0; p >>= 1) res += t[p];
      return res;
    }

    ////////////////////////////////////////
    // Non-commutative combiner function
    void modify(int p, const S& value) {
      for (t[p += n] = value; p >>= 1; ) t[p] = combine(t[p<<1], t[p<<1|1]);
    }

    S query(int l, int r) {
      S resl, resr;
      for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) resl = combine(resl, t[l++]);
        if (r&1) resr = combine(t[--r], resr);
      }
      return combine(resl, resr);
    }
};
