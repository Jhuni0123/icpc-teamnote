#include <vector>
#include <string>
using namespace std;
// finds radius of longest palindrome centered at s[i]
// If you also want to find even-length paindromes, use dummy characters
// baab -> #b#a#a#b#
vector<int> ManacherAlgorithm(string s){
    int n = (int)s.size();
    int p = -1, r = -1;
    vector<int> A(n);
    for (int i=0;i<n;i++){
        int x = r < i ? 0 : min(A[2*p - i], r-i);
        while (i+x < n && i-x >= 0 && s[i+x] == s[i-x]) x++;
        x--;
        A[i] = x;

        // update r, p
        if (r < i+x){
            r = i+x;
            p = i;
        }
    }
    return A;
}
