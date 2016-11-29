//UWAGA MOGE DODDAC 0 NA KONCU WEKTOROW WEJSCIOWYCH I WYJSCIOWEGO
vector < ll > karatsuba(vector < ll >& A, vector < ll >& B)
{
	int siz = max(SZ(A), SZ(B));
	if (SZ(A) != SZ(B) || __builtin_popcount(siz) > 1)
	{
		siz = (1 << (32 - __builtin_clz(siz)));
		A.resize(siz, 0);
		B.resize(siz, 0);
	}
	int s = siz/2;
	vector < ll > wynik(2*siz);
	if (SZ(A) < 70)
	{
		for(int i=0; i<siz; i++)
			for(int j=0; j<siz; j++)
				wynik[i+j] += A[i] * B[j];//jesli chcemy to tu %MOD
	}
	else
	{
		vector < ll > high1(s), high2(s), low1(s), low2(s);
		memcpy(&(low1[0]), &(A[0]), s * sizeof(ll));
		memcpy(&(low2[0]), &(B[0]), s * sizeof(ll));
		memcpy(&(high1[0]), &(A[s]), s * sizeof(ll));
		memcpy(&(high2[0]), &(B[s]), s * sizeof(ll));
		vector < ll > X = karatsuba(high1, high2), Y = karatsuba(low1, low2), Z;
		for(int i=0; i<s; i++) high1[i] += low1[i];//jesli chcemy to tu -MOD
		for(int i=0; i<s; i++) high2[i] += low2[i];//jesli chcemy to tu -MOD
		Z = karatsuba(high1, high2);
		for(int i=0; i<siz; i++) Z[i] -= X[i];//jesli chcemy to tu +MOD
		for(int i=0; i<siz; i++) Z[i] -= Y[i];//jesli chcemy to tu +MOD
		memcpy(&(wynik[2*s]), &(X[0]), 2 *s * sizeof(ll));
		memcpy(&(wynik[0]), &(Y[0]), 2 * s * sizeof(ll));
		for(int i=s; i<3*s; i++) wynik[i] += Z[i-s];//jesli chcemy to tu -MOD
	}
	return wynik;
}
