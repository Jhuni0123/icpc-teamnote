#include <algorithm>
using namespace std;

// '#': 35, '~': 126
struct SuffixArray {
    string s;
    vector<int> sa, lcp;
    SuffixArray(string &s) : s(s), sa(s.size()), lcp(s.size()) {
        constructSA();
        constructLCP();
    }

    vector<int> constructSA() {
        int n = s.size();
        vector<int> rank(n+1), tmp(n+1);
        int c = max(n, 256);
        vector<int> cnt(c+2), idx(n);
        for(int i=0;i<n;i++)sa[i] = i, rank[i] = s[i];
        for(int k=1;k<n;k<<=1) {
            fill(cnt.begin(), cnt.end(), 0);
            for(int i=0;i<n;i++) cnt[rank[min(i+k, n)]+1]++;
            for(int i=1;i<=c;i++) cnt[i] += cnt[i-1];
            for(int i=0;i<n;i++) idx[cnt[rank[min(i+k, n)]]++] = i;

            fill(cnt.begin(), cnt.end(), 0);
            for(int i=0;i<n;i++) cnt[rank[i]+1]++;
            for(int i=1;i<=c;i++) cnt[i] += cnt[i-1];
            for(int i=0;i<n;i++) sa[cnt[rank[idx[i]]]++] = idx[i];

            int r = tmp[sa[0]] = 1;
            for(int i=1;i<n;i++) tmp[sa[i]] = r += (rank[sa[i-1]] == rank[sa[i]] ? rank[sa[i-1]+k] < rank[sa[i]+k] : rank[sa[i-1]] < rank[sa[i]]);
            rank.swap(tmp);
            if (r == n)break;
        }
        return sa;
    }

    vector<int> constructLCP() {
        int n = s.size();
        vector<int> rank(n);
        for(int i=0;i<n;i++) rank[sa[i]] = i;
        int h = 0;
        for(int i=0;i<n;i++) {
            if (!rank[i])continue;
            int j = sa[rank[i]-1];
            while(i+h<n && j+h<n && s[i+h] == s[j+h])h++;
            lcp[rank[i]] = h;
            if (h > 0)h--;
        }
        return lcp;
    }
};
