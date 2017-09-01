#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;
//Max index Tree
typedef struct IT{
    int n;
    vector<int> mx;
    IT(const vector<int>& a){
        n=a.size();
        mx.resize(n*4);
        init(a,0,n-1,1);
    }

    int init(const vector<int>& a,int l,int r,int n){
        if(l==r)mx[n]=a[l];
        int m=(l+r)/2;
        return mx[n]=max(init(a,l,m,n*2),init(a,m+1,r,n*2+1));
    }
    int quary(int l,int r,int n,int nl,int nr){
        if(r<nl||nr<l)return 0;
        if(l<=nl&&nr<=r)return mx[n];
        int m=(nl+nr)/2;
        return max(quary(l,r,n*2,nl,m),quary(l,r,n*2+1,m+1,nr));
    }

    int quary(int l,int r){
        return quary(l,r,1,0,n-1);
    }

    int update(int i,int x,int n,int nl,int nr){
        if(i<nl&&nr<i)return mx[n];
        if(nl==nr)return mx[n]=x;
        int m = (nl+nr)/2;
        return mx[n]=max(update(i,x,n*2,nl,m), update(i,x,n*2+1,m+1,nr));
    }
    
    int update(int i, int x){
        return update(i,x,1,0,n-1);
    }
}IT;
