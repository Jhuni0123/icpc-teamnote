map<set<int>,int> grundy;
map<ll,set<int>> mp;

int get_grundy(set<int> x){
    // base case
    if( sz(x) == 0 ) return 0;
    if( grundy.find(x) != grundy.end() ) return grundy[x];
    
    set<int> S;
    int res = 0;

    auto iter = x.end(); iter--;
    int mx = *iter;

    // transition : which k to select
    for(int i=1;i<=mx;i++){
        set<int> nxt;
        for(auto e : x){
            if( e < i ) nxt.insert(e);
            else if( e == i ) continue;
            else nxt.insert(e-i); 
        }
        S.insert(get_grundy(nxt));
    }

    // find mex and return
    while( S.find(res) != S.end() ) res++;
    grundy[x] = res;
    return res;
}
int main(void){
    int n; geti(n);

    // Simple prime factorization
    rep(i,n){
        ll x; scanf("%lld",&x);
        for(ll i=2;i*i<=x;i++){
            if( x>0 && x%i == 0 ){
                int cnt = 0;
                while( x>0 && x%i == 0 ){
                    cnt++; x/= i;
                }
                mp[i].insert(cnt);
            }
        }
        if( x > 1 ){
            mp[x].insert(1);
        }
    }

    int res = 0;
    for(auto e : mp){
        res ^= get_grundy(e.Se);
    }    

    if( res == 0 ) printf("Arpa");
    else printf("Mojtaba");
    
}