#define MAX_V 20010
int V,M;

vector<int> Edge[MAX_V];
vector<int> rEdge[MAX_V];
vector<int> vs;

bool vis[MAX_V];
int cmp[MAX_V];
set<int> printSet[MAX_V];

void addEdge(int from, int to){
    Edge[from].push_back(to);
    rEdge[to].push_back(from);
}

void dfs(int v){
    vis[v] = true;
    for (int i = 0; i < Edge[v].size(); i++){
        if (!vis[Edge[v][i]]) dfs(Edge[v][i]);
    }
    vs.push_back(v);
}

void rdfs(int v, int k){
    vis[v] = true;
    cmp[v] = k;
    printSet[k].insert(v);
    for (int i = 0; i < rEdge[v].size(); i++){
        if (!vis[rEdge[v][i]]) rdfs(rEdge[v][i], k);
    }
}

bool cmp1(set<int>& a, set<int>& b) {
    return *a.begin() < *b.begin();
}

int main()
{
    geti(V); geti(M);
    int cnt = 0;
    while (M--){
        int a, b;
        scanf("%d%d", &a, &b);
        if (a > 0 && b > 0 ){
            addEdge(a + V, b);
            addEdge(b + V, a);

        }
        else if (a > 0 && b < 0){
            b = -b;
            addEdge(a + V, b + V);
            addEdge(b , a);
        }
        else if (a < 0 && b > 0){
            a = -a;            
            addEdge(a, b);
            addEdge(b + V, a + V);

    
        }
        else{
            a = -a; b = -b;
            addEdge(a, b + V);
            addEdge(b, a + V);

        }
    }
    
    memset(vis, false, sizeof(vis));
    for (int i = 1; i <= 2*V; i++){
        if (!vis[i]) dfs(i);
    }

    memset(vis, false, sizeof(vis));
    int k = 0;
    for (int i = vs.size()-1; i >= 0 ; i--){
        if (!vis[vs[i]]) rdfs(vs[i],k++);
    }
    
    for (int i = 1; i <= V; i++){
        if (cmp[i] == cmp[V + i]){
            printf("0\n");
            return 0;
        }
    }
    printf("1\n");

    for (int i = 1; i <= V; i++){
        if (cmp[i] > cmp[V + i]){
            printf("1 ");
        }
        else printf("0 ");
    }
}