#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <memory.h>
#include <math.h>
#include <assert.h>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> Pi;
typedef pair<ll, ll> Pll;
#define Fi first
#define Se second
#define pb(x) push_back(x)
#define rep(i, n) for(int i=0;i<n;i++)
#define repp(i, n) for(int i=1;i<=n;i++)
#define all(x) x.begin(), x.end()
 
#define ABS(x) (((x) > 0 ) ? (x) : (-(x)))
#define MAX2(x, y) (((x) > (y)) ? (x) : (y))
#define MIN2(x, y) (((x) < (y)) ? (x) : (y))
#define MAX3(x, y, z) ( (x) > (y)  ? ( (x) > (z) ? (x) : (z)  ) : ( (y) > (z) ? (y) : (z) )  )
#define MIN3(x, y, z) ( (x) < (y)  ? ( (x) < (z) ? (x) : (z)  ) : ( (y) < (z) ? (y) : (z) )  )
#define MID3(val1,val2,val3) MAX2(MIN2(MAX2(val1,val2),val3),MIN2(val1,val2))
 
 
#define geti1(X) scanf("%d",&X)
#define geti2(X,Y) scanf("%d%d",&X,&Y)
#define geti3(X,Y,Z) scanf("%d%d%d",&X,&Y,&Z)
#define geti4(X,Y,Z,W) scanf("%d%d%d%d",&X,&Y,&Z,&W)
 
#define GET_MACRO(_1,_2,_3,_4,NAME,...) NAME
#define geti(...) GET_MACRO(__VA_ARGS__, geti4, geti3, geti2, geti1) (__VA_ARGS__)
 
#define INF 987654321
#define IINF 987654321987654321

int N,K,M,tc,T;

struct segTree{ //range max query
	vector<int> v; int n;
	void init(int _n){
		_n+=3; v.resize(_n*2+10); n = _n;
	}
	void update(int x, int val){
		for(v[x+=n]=val;x>1;x>>=1)	v[x/2] = max(v[x],v[x^1]);
	}
	int query(int l, int r){ // [l,r]
		r++; //to make range as [l,r+1)
		int res = 0;
		for(l+=n,r+=n;l<r;l>>=1,r>>=1){
			if( l&1 ) res = max(res,v[l++]);
			if( r&1 ) res = max(res,v[--r]);
		}
		return res;
	}
};

#define MAXV 100500
#define LOGV 18
// cNo: node# -> hld# mapping
int cNo[MAXV];
// other arrays are accesed using hld#
int cPos[MAXV], cSize[MAXV], cHead[MAXV], cN; int cLeaf[MAXV];
vector<Pi> E[MAXV]; int pa[LOGV][MAXV]; int sz[MAXV]; int val[MAXV]; int level[MAXV];
bool vis[MAXV]; vector<segTree> tree; vector<Pi> edges;
int dfs_build(int x, int p, int v, int lev){
	pa[0][x] = p; sz[x] = 1; val[x] = v; level[x] = lev; 
	for(auto e : E[x])if(e.Fi!=p){
		sz[x] += dfs_build(e.Fi,x,e.Se,lev+1);
	}
	return sz[x];
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
		if( diff & (1<<k) )	x = pa[k][x];
			
	if( x == y ) return x;
	for(int k=LOGV-1;k>=0;k--)
		if( pa[k][x] != pa[k][y] ){
			x = pa[k][x]; y = pa[k][y];
		}
	return pa[0][x];
}

void hld(int cur){
	vis[cur] = true;
	if( cHead[cN] == 0 ) cHead[cN] = cur;
	cLeaf[cN] = cur;
	cNo[cur] = cN;
	cPos[cur] = cSize[cN]; cSize[cN]++;
	int nxt = -1; int mx = -1;
	// get max subtree (special child)
	for(auto e : E[cur])if(!vis[e.Fi]){
		if( sz[e.Fi] > mx ){
			nxt = e.Fi; mx = sz[e.Fi];
		}
	}

	if( mx >= 0 ) hld(nxt);
	for(auto e : E[cur])if(!vis[e.Fi]){
		cN++; hld(e.Fi);
	}
}

void build_hld_segTree(){
	for(int n=1;n<=cN;n++){
		int cur = cLeaf[n];
		tree[n].init(cSize[n]+5);
		while( cur!=-1 && cNo[cur]==n ){
			tree[n].update(cPos[cur],val[cur]);
			cur = pa[0][cur];
		} 
	}
}
void update_query(int x, int val){
	tree[cNo[x]].update(cPos[x],val);
}

int query_up(int u, int v){
	int uc = cNo[u], vc = cNo[v]; int ret = 0;
	while(true){
		if( uc == vc ){
			ret = max(ret, tree[uc].query(cPos[v]+1,cPos[u]) );
			break;
		}
		ret = max(ret, tree[uc].query( cPos[cHead[uc]], cPos[u]) );
		u = cHead[uc]; u = pa[0][u]; uc = cNo[u]; 
	}
	return ret;
}
int query(int u, int v){
	int l = lca(u,v);
	return max(query_up(u,l), query_up(v,l));
}

int main(){
	geti(N);
	rep(i,N-1){
		int a,b,c; geti(a,b,c);
		E[a].push_back({b,c}); E[b].push_back({a,c});
		edges.push_back({a,b});
	}

	dfs_build(1,-1,0,0); lca_build();
	cN = 1;
	hld(1);
	tree.resize(cN+3);
	build_hld_segTree();
	geti(K);
	rep(i,K){
		int a,b,c; geti(a,b,c);
		if( a == 1 ){
			b--; int u = edges[b].Fi; int v = edges[b].Se;
			if( level[u] > level[v] ) swap(u,v);
			update_query(v,c);
		}else{
			printf("%d\n",query(b,c));
		}
	}
}









