void dfs(int s, int e, int p, int q)
{
    if (s > e) return;
    int m = (s+e)>>1, opt;
    D[m] = 1e18;
    for (int k=p;k<=q&&k<m;k++){
        lld v = E[k] + (lld)(m-k-1)*(S[m]-S[k]);
        if (D[m] > v)
            D[m] = v, opt = k;
    }
    dfs(s, m-1, p, opt);
    dfs(m+1, e, opt, q);
}