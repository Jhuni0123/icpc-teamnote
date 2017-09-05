// 1-index
#define L(x) ((x)<<1)
#define R(x) (((x)<<1)+1)

const int MAXN = 100050;
const int LOGN = 17;

vector<int> adj[MAXN];
int st[6 * MAXN], sub[MAXN], pa[MAXN];
int idx[MAXN], head[MAXN], pos[MAXN], rev[MAXN];
int sz, cnt;

void init(int n) {
    fill(st, st + 6*n, INF);
    fill(head, head + n, -1);
}

void dfs(int x, int p) {
    sub[x] = 1;
    for(auto c : adj[x]) {
        if(c != p) {
            pa[c] = x;
            dfs(c, x);
            sub[x] += sub[c];
        }
    }
}

void update(int x, int id = 1, int l = 0, int r = sz) {
    if(x < l || x >= r) return;
    if(r - l <= 1) {
        if(st[id] == INF)
            st[id] = l;
        else
            st[id] = INF;
        return;
    }
    int mid = (l + r) >> 1;
    update(x, L(id), l, mid);
    update(x, R(id), mid, r);
    st[id] = min(st[L(id)], st[R(id)]);
}

int query(int x, int y, int id = 1, int l = 0, int r = sz) {
    if(y <= l || r <= x) return INF;
    if(x <= l && r <= y) return st[id];
    int mid = (l + r) >> 1;
    return min(query(x, y, L(id), l, mid), query(x, y, R(id), mid, r));
}


void HLD(int x, int p) {
    if(head[cnt] == -1)
        head[cnt] = x;
    idx[x] = cnt;
    pos[x] = sz;
    rev[sz] = x;
    sz++;

    int cindex = -1;
    for(int i = 0; i < adj[x].size(); i++) {
        if(adj[x][i] != p)
            if(cindex == -1 || sub[adj[x][cindex]] < sub[adj[x][i]])
                cindex = i;
    }
    if(cindex != -1)
        HLD(adj[x][cindex], x);
    for(int i = 0; i < adj[x].size(); i++) {
        if(adj[x][i] != p && i != cindex) {
            cnt++;
            HLD(adj[x][i], x);
        }
    }
}

int queryTree(int v) {
    if(v == 0) {
        int ans = query(pos[0], pos[0] + 1);
        if(ans == INF)
            return -1;
        else
            return 1;
    }
    int vchain, ans = INF;
    while(1) {
        vchain = idx[v];
        if(idx[v] == 0) {
            ans = min(ans, query(pos[0], pos[v]+1));
            break;
        }
        ans = min(ans, query(pos[head[vchain]], pos[v]+1));
        v = pa[head[vchain]];
    }
    if(ans == INF)
        return -1;
    else
        return rev[ans] + 1;
}

void updateTree(int v) {
    update(pos[v]);
}

int main() {
    int n, q;
    geti(n, q);
    for(int i = 1; i < n; i++) {
        int u, v;
        geti(u, v);
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    init(n);
    dfs(0, -1);
    HLD(0, -1);

    while(q--) {
        int type, x;
        geti(type, x);
        x--;
        if(type == 0) {
            updateTree(x);
        } else {
            printf("%d\n", queryTree(x));
        }
    }
}