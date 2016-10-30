const int INF = 987654321;
int n;
int cap[n][n], flow[n][n];

int edmond(int s, int t){
    memset(flow, 0, sizeof(flow));
    int totalflow = 0;
    while(true){
        vector<int> parent(n,-1);
        queue<int> q;
        parent[s]=s;
        q.push(s);
        while(!q.empty()){
            int here = q.front();q.pop();
            for(int there = 0;there < n;there++){
                if(cap[here][here] - flow[here][there] > 0 && parent[there] == -1){
                    q.push(there);
                    parent[there] = here;
                }
            }
        }
        if(parent[t] == -1)break;
        int amount = INF;
        for(int p=t;p!=s;p=parent[p]){
            amount = min(cap[parent[p]][p] - flow[parent[p]][p], amount);
        }
        for(int p=t;p!=s;p=parent[p]){
            flow[parent[p]][p]+=amount;
            flow[p][parent[p]]-=amount;
        }
        totalflow+=amount;
    }
    return totalflow;
}
