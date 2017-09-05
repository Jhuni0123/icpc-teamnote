int N;
int g[MAXN];
int f[MAXN];
int pa[LOGV][MAXV]; int level[MAXN];
int ST[MAXN], EN[MAXN], arr[MAXN*3];
int tt = 0;
vector<int> E[MAXN];

void dfs_build(int x, int p, int lev){
    pa[0][x] = p;
    level[x] = lev; 
    ST[x] = ++tt; arr[tt] = x;
    for(auto e : E[x])if(e!=p){
        dfs_build(e,x,lev+1);
    }
    EN[x] = ++tt; arr[tt] = x;
}

void lca_build(){
    for(int k=1;k<LOGV;k++){
        repp(i,N){
            if( pa[k-1][i] != -1 )pa[k][i] = pa[k-1][pa[k-1][i]];
            else pa[k][i] = -1;
        }
    }
}

int lca(int x, int y){
    if( level[x] < level[y] ) swap(x,y);
    int diff = level[x] - level[y];
    for(int k=0;k<LOGV;k++)    
        if( diff & (1<<k) )    x = pa[k][x];
            
    if( x == y ) return x;
    for(int k=LOGV-1;k>=0;k--)
        if( pa[k][x] != pa[k][y] ){
            x = pa[k][x]; y = pa[k][y];
        }
    return pa[0][x];
}

int Bsize;
struct query{
    int l,r,n;
};
bool cmp1(query& a, query& b){
    if( a.l/Bsize == b.l/Bsize ) return a.r < b.r;
    else return a.l/Bsize < b.l/Bsize;
};
bool cmp2(query&a, query& b ){ return a.n < b.n; }

ll ans[100500];
ll cnt[2][200500];
int vis[100500];
ll sum = 0;

void update(int x, int type){
    // add node to range
    if( type == 1 ){
        sum += cnt[g[x]^1][f[x]];
        cnt[g[x]][f[x]]++;
    }
    // remove node from range
    if( type == 0 ){
        sum -= cnt[g[x]^1][f[x]];
        cnt[g[x]][f[x]]--;
    }
}

int main(void){
    geti(N);
    repp(i,N) geti(g[i]);
    repp(i,N) geti(f[i]);

    set<int> flist;
    map<int,int> fmp;
    repp(i,N) flist.insert(f[i]);
    int tmp = 1;
    for(auto e: flist) fmp[e] = tmp++;
    repp(i,N) f[i] = fmp[f[i]];
    
    repp(i,N-1){
        int a,b; geti(a,b);
        E[a].pb(b); E[b].pb(a);
    }
    tt = 0;
    dfs_build(1,-1,0);
    lca_build();
    Bsize = (int) sqrt(1.0*tt);
    
    int Q; geti(Q);
    vector<query> v;
    repp(q,Q){
        int a,b; geti(a,b);
        if( ST[a] > ST[b] ) swap(a,b);
        int l = lca(a,b);
        if( a == l || b == l){
            v.push_back({ST[a],ST[b],q});
        }
        else{
            v.push_back({EN[a],ST[b],q});
        }
    }

    sort(all(v),cmp1);
    int l=1, r=0;
    for(int i=0;i<v.size();i++){
        query& e = v[i];
        int ql = e.l, qr = e.r;
        while( r < qr ){
            r++;
            int node = arr[r];
            vis[node]++;
            if( vis[node] == 1 ) update(node,1);    
            if( vis[node] == 2 ) update(node,0);
        }
        while( r > qr ){
            int node = arr[r];
            vis[node]--;
            if( vis[node] == 0 ) update(node,0);
            if( vis[node] == 1 ) update(node,1);
            r--;
        }
        while( l < ql ){
            int node = arr[l];
            vis[node]--;
            if( vis[node] == 0 ) update(node,0);
            if( vis[node] == 1 ) update(node,1);    
            l++;
        }
        while( l > ql ){
            l--;
            int node = arr[l];
            vis[node]++;
            if( vis[node] == 1 ) update(node,1);    
            if( vis[node] == 2 ) update(node,0);
        }
        
        int u = arr[ql]; int v = arr[qr];
        int l = lca(u,v);

        if( u != l && v != l ){
            int node = l;
            vis[node]++;
            if( vis[node] == 1 ) update(node,1);    
            if( vis[node] == 2 ) update(node,0);
        }
    
        ans[e.n] += sum;
        
        if( u != l && v != l ){
            int node = l;
            vis[node]--;
            if( vis[node] == 0 ) update(node,0);
            if( vis[node] == 1 ) update(node,1);
        }

    }
    repp(i,Q) printf("%lld\n",ans[i]);
}