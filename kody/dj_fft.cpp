typedef unsigned T;//ma byc unsigned int albo ll albo ull

const T P = 2013265921; //15*2^27+1
const T ROOT = 440564289; //root
const int MN=21; // musi być < 26
unsigned omega[1<<MN];


T pw (T x, T n) {
    T res = 1;
    while(n) {
        if (n&1) res = (ull)res*x%P;
        x = (ull)x*x%P;
        n>>=1;
    }
    return res;
}

void fft(vector<T> &a, int n, bool inverse=false) {
    int N = 1<<n;
    a.insert(a.end(), N-SZ(a), 0);
    T root = pw(ROOT, (1<<27)/N*(inverse?(N-1):1));
    omega[0] = 1;
    rep(i, 1, N) omega[i] = (ull)omega[i-1]*root%P;
    rep(i, 0, n) {
        rep(j, 0, 1<<i) {
            rep(k, 0, 1<<(n-i-1)) {
                int s = (j<<(n-i))+k;
                int t = s + (1<<(n-i-1));
                T w = omega[k<<i];
                T temp = a[s] + a[t];
                if (temp >= P) temp -= P;
                T t2 = a[s] - a[t] + P;
                a[t] = (ull) w * t2 % P;
                a[s] = temp;
            }
        }
    }
    rep(i, 0, N) {
        int x=i,y=0;
        rep(j, 0, n)  y=(y<<1)+(x&1), x>>=1;
        if (i<y) swap(a[i],a[y]);
    }
    if (inverse) {
        T inv = pw(N, P-2);
        rep(i, 0, N) a[i] = (ull)a[i]*inv%P;
    }
}
vector<T> conv(vector<T> A, vector<T> B) {
    int n = 31-__builtin_clz(2*(SZ(A)+SZ(B))-1);
    fft(A, n);
    fft(B, n);
    rep(i, 0, (1<<n)) A[i] = (ull) A[i] * B[i] % P;
    fft(A, n, true);
    return A;
}
vector<T> square(vector<T> A) {
    int n = 32-__builtin_clz(2*SZ(A)-1);
    fft(A, n);
    rep(i, 0, (1<<n)) A[i] = (ull) A[i] * A[i] % P;
    fft(A, n, true);
    return A;
}
