/*
    a00 a01 a02 .. a0(n-1)
    a10 a11 ...... an2
    .
    .
    a(n-1)0 .......a(n-1)(n-1)
    Macierz[i][j] = aij

    Uwaga:
    Macierz({{1, 1, 1, 1, 1}}) to wektor poziomy (M[0][0] do M[0][n-1])
    Macierz m -> SZ(m.V) to liczba wierszy, SZ(m.V[0]) to liczba kolumn
*/
struct Macierz{
    long long MOD;
    vector < vector < ll > > V;
    Macierz() = default;
    Macierz(ll mod, vector < vector < ll > > V_ini) : MOD(mod), V(V_ini)
    {}
    Macierz(ll mod, ll wiersze, ll kolumny, ll na_przekatnej = 1) : MOD(mod), V(wiersze, vector < ll >(kolumny, 0))
    {
        for(int i=0; i<min(wiersze, kolumny); i++)
            V[i][i] = na_przekatnej;
    }
    vector < ll >& operator[](const int& ind)
    {
        return V[ind];
    }
    Macierz operator*(Macierz& m)
    {
        assert(SZ(V) > 0 && SZ(V[0]) > 0 && SZ(m.V) > 0 && SZ(m.V[0]) > 0);
        assert(SZ(V[0]) == SZ(m.V));
        int h = SZ(V), w = SZ(m.V[0]), a = SZ(m.V);
        Macierz wynik(MOD, SZ(V), SZ(m.V[0]), 0);
        for(int i=0; i<h; i++){
            for(int j=0; j<w; j++){
                for(int k=0; k<a; k++)
                {
                    wynik[i][j] += V[i][k] * m.V[k][j];
                    wynik[i][j] %= MOD;
                }
            }
        }
        return wynik;
    }
    Macierz transpozycja()
    {
        Macierz m(MOD, SZ(V[0]), SZ(V));
        for(int i=0; i<SZ(V); i++)
            for(int j=0; j<SZ(V[0]); j++)
                m[j][i] = V[i][j];
        return m;
    }
};

Macierz poteguj(Macierz m, ll wyk)
{
    Macierz wynik(m.MOD, SZ(m.V), SZ(m.V[0]));
    if (!wyk)
        return wynik;
    wynik = poteguj(m*m, wyk/2);
    if (wyk & 1)
        wynik = wynik * m;
    return wynik;
}
