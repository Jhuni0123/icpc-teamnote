int N,M,cnt=0;

// DFS discover time of vertex
int vis[100500];
vector<int> E[100500];
set<int> articulation;

// Returns the earlist discover time that x's child can visit
// without using x  
int dfs(int x, int p){
    vis[x] = ++cnt;
    int child = 0;
    int res = vis[x];
    for(auto e : E[x]){
        if(vis[e]==0){
            // low : the earlist discover time that e can visit
            // without using x
            int low = dfs(e,x);
            child++;
            // check if not root
            if( p != -1 && low >= vis[x] ) articulation.insert(x);
            res = min(res,low);
        }
        else{
            res = min(res,vis[e]);
        }
    }

    // check if root
    if( p == -1 && child >= 2 ) articulation.insert(x);

    return res;
}

int main()
{
    geti(N,M);
    rep(i,M){
        int a,b; geti(a,b);
        E[a].pb(b); E[b].pb(a);
    }

    repp(i,N) if( vis[i] == 0 ) dfs(i,-1);

    printf("%d\n",(int)articulation.size());
    for(auto e : articulation) printf("%d ",e);
}
