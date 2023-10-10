#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

struct Segtree {
    using D = ll;
    using L = ll;
    static constexpr D DI = 0;
    static constexpr L LI = 0;
    inline L lazyadd(L a, L b) {
        return a + b;
    }
    inline D apply(D d, L lazy, int len) {
        return d + lazy * len;
    }
    inline D combine(D a, D b) {
        return a + b;
    }

    struct Node {
        D d = DI;
        L lazy = LI;
    };
    int n;
    vector<Node> data;
    int log(int n) {
        return 32-__builtin_clz(n);
    }
    Segtree(int _n) : n(1<<log(_n-1)), data(n*2) {}
    Segtree(vector<D> &a) : n(1<<log(a.size()-1)), data(n*2) {
        assign(1, a.size(), a, 1, 1, n);
    }
    void assign(int l, int r, vector<D> &a, int node, int nodeL, int nodeR) {
        if (l > nodeR || r < nodeL) return;
        if (nodeL == nodeR) {
            data[node].d = a[nodeL-1];
            return;
        }
        assign(l,r,a,node*2,nodeL,(nodeL+nodeR)/2);
        assign(l,r,a,node*2+1,(nodeL+nodeR)/2+1,nodeR);
        data[node].d = combine(data[node*2].d, data[node*2+1].d);
    }
    void propagate(int node, int nodeL, int nodeR){
        if (data[node].lazy == LI) return;
        int len = nodeR - nodeL + 1;
        if (len > 1) {
            data[node*2].lazy = lazyadd(data[node*2].lazy, data[node].lazy);
            data[node*2+1].lazy = lazyadd(data[node*2+1].lazy, data[node].lazy);
        }
        data[node].d = apply(data[node].d, data[node].lazy, len);
        data[node].lazy = LI;
    }

    void update(int l, int r, L val, int node, int nodeL, int nodeR){
        propagate(node, nodeL, nodeR);
        if (l > nodeR || r < nodeL) return;
        if (l <= nodeL && nodeR <= r){
            data[node].lazy = lazyadd(data[node].lazy, val);
            propagate(node,nodeL,nodeR);
            return;
        }
        update(l,r,val,node*2,nodeL,(nodeL+nodeR)/2);
        update(l,r,val,node*2+1,(nodeL+nodeR)/2+1,nodeR);
        data[node].d = combine(data[node*2].d, data[node*2+1].d);
    }
    void update(int l, int r, L val) { update(l, r, val, 1, 1, n); }

    D query(int l, int r, int node, int nodeL, int nodeR){
        propagate(node, nodeL, nodeR);
        if (l > nodeR || r < nodeL) return DI;
        if (l <= nodeL && nodeR <= r) {
            return data[node].d;
        }
        return combine(query(l,r,node*2,nodeL,(nodeL+nodeR)/2), query(l,r,node*2+1,(nodeL+nodeR)/2+1,nodeR));
    }
    D query(int l, int r) { return query(l, r, 1, 1, n); }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;
    vector<ll> a(N);
    for(auto &x : a) cin >> x;
    Segtree tree(a);
    for(int i=0;i<M+K;i++) {
        int a; cin >> a;
        if( a == 1 ){
            int b,c; ll d;
            cin >> b >> c >> d;
            tree.update(b,c,d);
        } else {
            int b,c; cin >> b >> c;
            cout << tree.query(b, c) << '\n';
        }
    }
}
