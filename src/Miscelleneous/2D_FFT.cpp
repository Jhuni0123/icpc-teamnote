const double EPS = 0.00001;

typedef complex<double> base;

void fft(vector<base> &a, bool invert){
    int n = a.size();
    for(int i=1,j=0;i<n;i++){
        int bit = n >> 1;
        for (;j>=bit;bit>>=1)j -= bit;
            j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    for(int len=2;len<=n;len<<=1){
        double ang = 2*acos(-1)/len*(invert?-1:1);
        base wlen(cos(ang),sin(ang));
        for(int i=0;i<n;i+=len){
            base w(1);
            for(int j=0;j<len/2;j++){
                base u = a[i+j], v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for(int i=0;i<n;i++) a[i] /= n;
    }
}

void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res){ 
    vector<base> fa(a.begin(), a.end()), fb(b.begin(),b.end());
    int n = 1;
    while(n < max(a.size(), b.size())) n <<= 1;
    n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa,false);fft(fb,false);
    for(int i=0;i<n;i++) fa[i] *= fb[i];
        fft(fa,true);
    res.resize(n);
    for(int i=0;i<n;i++) res[i] = int(fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
}

void multiply_complex(const vector<base> &a, const vector<base> &b, vector<base> &res){ 
    vector<base> fa(a.begin(), a.end()), fb(b.begin(),b.end());
    int n = 1;
    while(n < max(a.size(), b.size())) n <<= 1;
    n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa,false);fft(fb,false);
    for(int i=0;i<n;i++) fa[i] *= fb[i];
        fft(fa,true);
    res.resize(n);
    for(int i=0;i<n;i++) res[i] = fa[i];
}

const int MAXN = 405;
const int LOGN = 19;

string S[MAXN], T[MAXN];

int main() {
    int n, m;
    geti(n, m);
    for(int i = 0; i < n; i++)
        cin >> S[i];
    int r, c;
    geti(r, c);
    for(int i = 0; i < r; i++)
        cin >> T[i];


    int p = 1, q = 1;
    while(q < m+c) q <<= 1;
    while(p < n+r) p <<= 1;

    vector<vector<base>> a(p, vector<base>(q)), b(p, vector<base>(q));
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < q; j++) {
            int t = S[i%n][j%m] - 'a';
            double ang = 2*acos(-1)*t/26;
            a[i][j] = base(cos(ang), sin(ang));
        }
    }
    int cnt = 0;
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            if(T[i][j] != '?') {
                cnt++;
                int t = T[i][j] - 'a';
                double ang = 2*acos(-1)*t/26;
                b[(r-1)-i][(c-1)-j] = base(cos(-ang), sin(-ang));
            }
        }
    }

    vector<vector<base>> fa, fb, res;
    for(int i = 0; i < p; i++) {
        vector<base> ta(a[i].begin(), a[i].end()), tb(b[i].begin(), b[i].end());
        fft(ta, false);
        fft(tb, false);
        fa.push_back(ta);
        fb.push_back(tb);
    }

    for(int j = 0; j < q; j++) {
        vector<base> ta(p), tb(p), tmp;
        for(int i = 0; i < p; i++) {
            ta[i] = fa[i][j];
            tb[i] = fb[i][j];
        }
        multiply_complex(ta, tb, tmp);
        if(j == 0)
            res.resize(tmp.size(), vector<base>(q));

        for(int i = 0; i < res.size(); i++)
            res[i][j] = tmp[i];
    }

    for(int i = 0; i < res.size(); i++)
        fft(res[i], true);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(abs(res[i+r-1][j+c-1].real() - cnt) < EPS && abs(res[i+r-1][j+c-1].imag()) < EPS) printf("1");
            else printf("0");
        }
        printf("\n");
    }
}