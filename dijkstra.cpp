#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int,int> pii;
const int INF = 2147483647;

int n,m,a,b,c;
int d[1111];
vector<pii> g[1111];

void dijk(int k){
	for(int i=1;i<=n;i++){
		d[i]=INF;
	}
	d[k]=0;
	priority_queue<pii,vector<pii>,greater<pii> > pq;
	pq.push(pii(0,k));
	while(!pq.empty()){
		pii p=pq.top();pq.pop();
		int dis=p.first, v=p.second;
		if(d[v]>dis)continue;
		for(int i=0;i<g[v].size();i++){
			pii q=g[v][i];
			int to = q.first, cost = q.second;
			if(d[to] > cost+dis){
				pq.push(pii(d[to] = cost+dis,to));
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d%d",&a,&b,&c);
		g[a].push_back(pii(b,c));
	}
	scanf("%d%d",&a,&b);

	dijk(a);
	
	printf("%d\n",d[b]);
}