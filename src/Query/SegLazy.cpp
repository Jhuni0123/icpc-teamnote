#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int log(int x) {
    return 31-__builtin_clz(x);
}

struct Segtree {
    using D = ll;
    using L = ll;
    static constexpr D DI = 0;
    static constexpr L LI = 0;
    inline L lazyadd(L a, L b) {
        return a + b;
    }
    inline D applylazy(D d, L lazy, int len) {
        return d + lazy * len;
    }
    inline D combine(D a, D b) {
        return a + b;
    }

    int n, h;
    vector<D> t;
    vector<L> d;
    Segtree(int n) : n(n), h(log(n)+1), t(n*2), d(n*2) {}
    Segtree(vector<D> &a) : n(a.size()), h(log(n)+1), d(n*2) {
        t.reserve(2*n);
        t.resize(n);
        t.insert(t.end(), a.begin(), a.end());
        for (int i = n - 1; i > 0; --i) {
            t[i] = combine(t[i<<1], t[i<<1|1]);
        }
    }

    void calc(int x, int len) {
        if (d[x] == LI) t[x] = combine(t[x<<1], t[x<<1|1]);
        else t[x] = applylazy(combine(t[x<<1], t[x<<1|1]), d[x], len);
    }

    void apply(int x, L v, int len) {
        t[x] = applylazy(t[x], v, len);
        if (x < n) d[x] = lazyadd(d[x], v);
    }

    void push(int l, int r) {
        int s = h, len = 1 << (h-1);
        for (l += n, r += n-1; s > 0; s--, len >>= 1) {
            for (int i = l >> s; i <= r >> s; i++) if (d[i] != LI) {
                apply(i<<1, d[i], len);
                apply(i<<1|1, d[i], len);
                d[i] = LI;
            }
        }
    }

    void update(int l, int r, L v) {
        if (v == LI) return;
        push(l, l+1);
        push(r-1, r);
        bool cl = false, cr = false;
        int len = 1;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1, len <<= 1) {
            if (cl) calc(l-1, len);
            if (cr) calc(r, len);
            if (l&1) apply(l++, v, len), cl = true;
            if (r&1) apply(--r, v, len), cr = true;
        }
        for (--l; r > 0; l >>= 1, r >>= 1, len <<= 1) {
            if (cl) calc(l, len);
            if (cr && (!cl || l != r)) calc(r, len);
        }
    }

    D query(int l, int r) {
        push(l, l+1);
        push(r-1, r);
        D resl = DI, resr = DI;
        for(l += n, r += n; l<r; l>>=1, r>>=1) {
            if (l&1) resl = combine(resl, t[l++]);
            if (r&1) resr = combine(t[--r], resr);
        }
        return combine(resl, resr);
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, k;
    cin >> n >> m >> k;
    vector<ll> a(n);
    for(auto &x : a) cin >> x;
    Segtree seg(a);

    for(int i=0;i<m+k;i++) {
        ll t, a, b, c;
        cin >> t;
        if (t == 1){
            cin >> a >> b >> c;
            seg.update(a-1, b, c);
        } else {
            cin >> a >> b;
            cout << seg.query(a-1, b) << '\n';
        }
    }
}
