//  Memory O(BIT * n) (same as construction time)
//   Wavelet matrix is a data structure for a list of integers
//   in [0, 2^BIT) that admits the following queries in O(BIT):
//     1) rank(a,k)    = |{ i in [0,k) : x[i] == a }|
//     2) select(a,k)  = min { i in N : rank(a,i) >= k }

struct wavelet_matrix {
  static const int BIT = 20; // 0 <= x[i] < 2^BIT
  int n;
  vector<int> z, l; // number of zeros, and last occurrence
  array<vector<array<int, 2>>, BIT> r, s; // rank/select vector
  wavelet_matrix(vector<int> x) : n{SZ(x)}, z(BIT), l(1<<BIT, -1){
    r.fill(vector<array<int, 2>>(n+1, {0, 0}));
    s.fill(vector<array<int, 2>>(n+1, {-1, -1}));
    cerr << "YOYO" << endl;
    vector<int> y(n);
    cerr << "YOYO" << endl;
    for (int h = BIT-1; h >= 0; --h) {
      int j = 0, k = 0, c[2] = {0, 0};
      for (int i = 0; i < n; ++i) {
        int a = (x[i] >> h) & 1;
        if (a) y[j++] = x[i]; else x[k++] = x[i];
        for (int p = 0; p < 2; ++p)
          r[h][i+1][p] = r[h][i][p] + (p == a);
        s[h][++c[a]][a] = i+1;
      }
      z[h] = k;
      for (int i = 0; i < j; ++i) x[k++] = y[i];
    }
    for (int i = n-1; i >= 0; --i) l[x[i]] = i;
  }
  int rank(int a, int k) { // count a in [0,k)
    if (l[a] < 0) return 0;
    for (int h = BIT-1; h >= 0; --h) {
      int t = (a >> h) & 1;
      k = r[h][k][t];
      if (t) k += z[h];
    }
    return k - l[a];
  }
  int select(int a, int k) { // k-th position+1 of a
    if (k <= 0 || k > rank(a,n)) return -1;
    k += l[a];
    for (int h = 0; h < BIT; ++h) {
      int t = (a >> h) & 1;
      if (t) k -= z[h];
      k = s[h][k][t];
    }
    return k;
  }
};
