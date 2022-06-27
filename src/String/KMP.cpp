#include <vector>
#include <string>
using namespace std;

vector<int> build_fail(string &p){
    vector<int> fail(p.size());
    int j = 0;
    for(int i=1;i<(int)p.size();i++){
        while (j>0 && p[i]!=p[j]) j = fail[j-1];
        if (p[i] == p[j]) fail[i] = ++j;
    }
    return fail;
}

vector<int> kmp(string &s, string &p){
    auto fail = build_fail(p);
    vector<int> ans(s.size());
    int j = 0;
    for(int i=0;i<(int)s.size();i++){
        while (j>0 && s[i]!=p[j]) j = fail[j-1];
        if (s[i] == p[j]) ans[i] = ++j;
        if (j == p.size()) j = fail[j-1];
    }
    return ans;
}
