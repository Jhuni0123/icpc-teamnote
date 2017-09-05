int N,M,K,Q;

vector<Pi> edge[1000500];
int pa[MAXN]; int sz[MAXN];

// each query's answer
Pi ans[MAXN];
// each query's possible answer range for binary search
int low[MAXN], high[MAXN];
// focus[x] : list of query # where it's mid value is x
vector<int> focus[1000500];

int find(int x){
    if( x == pa[x] ) return x;
    return pa[x] = find(pa[x]);
}
int x[MAXN], y[MAXN];

void uni(int a, int b){
    a = find(a); b = find(b);
    if( a == b ) return;
    pa[a] = b;
    sz[b] += sz[a];
}

int main(void){
    //ios::sync_with_stdio(false);
    geti(N,M);
    int C = -1;
    repp(i,M){
        int a,b,c; geti(a,b,c);
        edge[c].push_back({a,b});
        C = max(C, c);
    }

    geti(Q);
    repp(i,Q){
        int a,b;
        geti(a,b); x[i] = a; y[i] = b;
        ans[i] = {INF,-1};
        // Initially, every query has answer in [0,C] range
        low[i] = 0; high[i] = C;
    }

    bool changed = true;
    while( changed ){
        changed = false;
            
        // Clear variables
        rep(i,C+1) focus[i].clear();
        repp(i,N) pa[i] = i, sz[i] = 1;
        
        // Put each query into corresponding focus group
        repp(i,Q){
            if( low[i] > high[i] ) continue;
            focus[ (low[i] + high[i])/2 ].push_back(i);
        }

        // for every time 0~C
        for(int k=0;k<=C;k++){
            // perform action of that time
            for(auto e : edge[k]) uni(e.Fi,e.Se);

            // for each focus group
            // determine it's answer & next position
            for(auto e : focus[k]){
                changed = true;
                int a = x[e]; int b = y[e];
                if( find(a) == find(b) ){
                    ans[e].Fi = min(ans[e].Fi, k);
                    ans[e].Se = sz[find(a)];
                    high[e] = k-1;
                }    
                else{
                    low[e] = k+1;
                }
            }
        }
    }

    repp(i,Q){
        if( ans[i].Fi == INF ) printf("%d\n",-1);
        else printf("%d %d\n",ans[i].Fi, ans[i].Se);
    }

}