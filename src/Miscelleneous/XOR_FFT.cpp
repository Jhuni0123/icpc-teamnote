#include <cstdio>
#include <complex>
 
const int SZ = 20, N = 1 << SZ;
 
using namespace std;
 
int Rev(int x) {
    int i, r = 0;
    for (i = 0; i < SZ; i++) {
        r = r << 1 | x & 1;
        x >>= 1;
    }
    return r;
}
 
void FFT(int *a, bool f) {
    int i, j, k, z;
    for (i = 0; i < N; i++) {
        j = Rev(i);
        if (i < j) {
            z = a[i];
            a[i] = a[j];
            a[j] = z;
        }
    }
    for (i = 1; i < N; i <<= 1) for (j = 0; j < N; j += i << 1) for (k = 0; k < i; k++) {
        z = a[i + j + k];
        a[i + j + k] = a[j + k] - z;
        a[j + k] += z;
    }
    if (f) for (i = 0; i < N; i++) a[i] /= N;
}
 
int X[N];
 
int main() {
    int i, n;
    scanf("%d", &n);
    for (i = 0; i < 1 << n; i++) scanf("%d", &X[i]);
    FFT(X, false);
    for (i = 0; i < N; i++) X[i] *= X[i];
    FFT(X, true);
    for (i = 0; i < 1 << n; i++) printf("%d ", X[i]);
}