const int MAXN = 1e5 + 50;
const int LOGN = 18;

int root[MAXN], pos[MAXN], a[MAXN], rev[MAXN];
int n, cnt;

struct node {
	int sum, left, right;
} tree[3 * MAXN * LOGN];

int build(int l = 0, int r = n) {
	int id = ++cnt;
	if(r - l <= 1) {
		tree[id] = {0, 0, 0};
		return id;
	}
	int mid = (l + r) >> 1;
	tree[id] = {0, build(l, mid), build(mid, r)};
	return id;
}

int update(int x, int prev, int l = 0, int r = n) {
	if(x < l || r <= x) return prev;
	int id = ++cnt;
	if(r - l <= 1) {
		tree[id] = {1, 0, 0};
		return id;
	}
	int mid = (l + r) >> 1;
	int L = update(x, tree[prev].left, l, mid);
	int R = update(x, tree[prev].right, mid, r);
	tree[id] = {tree[L].sum + tree[R].sum, L, R};
	return id;
}

int findKth(int x, int y, int k, int l = 0, int r = n) {
	if(r - l <= 1) return l;
	int mid = (l + r) >> 1;
	int t = tree[tree[x].left].sum - tree[tree[y].left].sum;
	if(t >= k)
		return findKth(tree[x].left, tree[y].left, k, l, mid);
	else
		return findKth(tree[x].right, tree[y].right, k - t, mid, r);
}

// find ans in [lb, ub)
long long ans(int lb, int ub) {
	if(ub - lb <= 1) return 0;
	int k = (ub - lb + 1) / 2;
	int mid = a[findKth(root[lb], root[ub], k)];
	return ans(lb, mid) + ans(mid+1, ub) + (long long)(ub - lb);
}



int main() {
	geti(n);
	for(int i = 0; i < n; i++) {
		geti(a[i]);
		a[i]--;
		pos[a[i]] = i;
	}
	
	// ith segment tree: xth element is 1 iff a[x] >= i
	root[n] = build();
	for(int i = n-1; i >= 0; i--)
		root[i] = update(pos[i], root[i+1]);
	
	cout << ans(0, n) << endl;
}
