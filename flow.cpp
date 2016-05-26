#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct edge{
    int to;
    int cost;
    int from;
}edge;
//vector<int> v[11111];
vector<edge> v[11111];
int used[11111];
int flow(int s,int d,int mn){
    if(s==d)return mn;
    used[s]=1;
    for(int i=0;i<v[s].size();i++){
        edge e=v[s][i];
        if(used[e.to]==0&&e.cost>0){
            int x=flow(e.to,d,min(mn,e.cost));
            if(x>0){
                v[s][i].cost-=x;
                v[e.to][e.from].cost+=x;
                return x;
            }
        }
    }
    return 0;
}
