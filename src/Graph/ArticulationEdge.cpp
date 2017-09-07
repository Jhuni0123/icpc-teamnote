int N,M,cnt=0;

// DFS discover time of vertex
int vis[100500];
vector<int> E[100500];
set<pair<int,int>> articulation;

// Returns the earlist discover time that x's child can visit
// without using edge (p,x)
int dfs(int x, int p){
    vis[x] = ++cnt;
    int child = 0;
    int res = vis[x];
    for(auto e : E[x]){
        if(e==p) continue;
        if(vis[e]==0){
            // low : the earlist discover time that e can visit
            // without using edge (x,e)
            int low = dfs(e,x);
            child++;
            // keep in mind: in edge problem, low==vis[x] case
            // is not considered as articulation edge
            // also, root checking is not needed
            if( low > vis[x] )
                articulation.insert({min(e,x),max(e,x)});
            res = min(res,low);
        }
        else{
            res = min(res,vis[e]);
        }
    }

    // no root check needed for edge problem

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
    for(auto e : articulation) printf("%d %d\n",e.first,e.second);
}
