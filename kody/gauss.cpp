//https://github.com/t3nsor/codebook/blob/master/gaussian.cpp
// Gauss-Jordan elimination with full pivoting.
// Uses:
//   (1) solving systems of linear equations (AX=B)
//   (2) inverting matrices (AX=I)
//   (3) computing determinants of square matrices
//
// Running time: O(n^3)
//
// INPUT:    a[][] = an nxn matrix
//           b[][] = an nxm matrix
//           A MUST BE INVERTIBLE!
//
// OUTPUT:   X      = an nxm matrix (stored in b[][])
//           A^{-1} = an nxn matrix (stored in a[][])
//           returns determinant of a[][]
/*
Przerobilem troche, zeby rozwiazywalo tylko (1) i (2)
w b jest przykladowe rozwiazanie
jest jeszcze rank, det i sprzecze, mozna przekazac przez referencje
testowalem tylko na zadaniu, w ktorym zawsze byla jednoznaczna odpowiedz
przykladowe uzycie:

int n;
cin>>n;
vector < vector < T > > A(n, vector < T > (n));
vector < T > B(n);
for(int i=0; i<n; i++)
{
	for(int j=0; j<n; j++)
		cin>>A[i][j];
	cin>>B[i];
}
T odp = GaussJordan(A, B);
if (abs(odp) < EPS)
{
	cout <<"BRAK JEDNOZNACZNEGO ROZWIAZANIA";
}
else
{
	for(int i=0; i<n; i++)
		cout << B[i] << " ";
}
*/

const double EPS = 1e-10;
typedef vector<int> VI;
typedef long double T;
typedef vector<T> VT;
typedef vector<VT> VVT;
T GaussJordan(VVT &a, VT &b) {
  const int n = a.size();
  VI ipiv(n);
  T det = 1;
  int rank = 0;

  for (int i = 0; i < n; i++) {
    int pj = -1, pk = -1;
    for (int j = 0; j < n; j++) 
			if (!ipiv[j])
      	for (int k = 0; k < n; k++) 
					if (!ipiv[k])
        		if (pj == -1 || fabs(a[j][k]) > fabs(a[pj][pk])) { pj = j; pk = k; }
    if (fabs(a[pj][pk]) < EPS) 
			break;
		rank++;
    ipiv[pk]++;
    swap(a[pj], a[pk]);
    swap(b[pj], b[pk]);
    if (pj != pk) det *= -1;

    T c = 1.0 / a[pk][pk];
    det *= a[pk][pk];
    a[pk][pk] = 1.0;
    for (int p = 0; p < n; p++) a[pk][p] *= c;
    b[pk] *= c;
    for (int p = 0; p < n; p++) if (p != pk) {
      c = a[p][pk];
      a[p][pk] = 0;
      for (int q = 0; q < n; q++) a[p][q] -= a[pk][q] * c;
      b[p] -= b[pk] * c;      
    }
  }
  
  bool sprzeczne = false;
  for(int i=0; i<n; i++)
  	if (!ipiv[i] && fabs(b[i]) < EPS)
  		sprzeczne = true;
  if (rank < n)
  	det = 0;
  return det;
}
