
ll a[MAXN], b[MAXN], dp[MAXN];
ll la[MAXN], lb[MAXN];
int sz, cur, n;

double cross(int x, int y) {
    return (double)(lb[x] - lb[y]) / (la[y] - la[x]);
}

void newLine(ll p, ll q) {
    la[sz] = p;
    lb[sz] = q;

    while(sz > 1 && cross(sz-1, sz-2) > cross(sz, sz-1)) {
        la[sz-1] = la[sz];
        lb[sz-1] = lb[sz];
        sz--;
    }
    sz++;
}

ll find(ll x) {
    while(cur+1 < sz && x > cross(cur, cur+1)) cur++;
    return la[cur] * x + lb[cur];
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= n; i++)
        cin >> b[i];

    dp[1] = 0;
    newLine(b[1], 0);
    for(int i = 2; i <= n; i++) {
        dp[i] = find(a[i]);
        newLine(b[i], dp[i]);
    }
    cout << dp[n];
}