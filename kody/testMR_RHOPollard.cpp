#define LT 2						//dla liczb powyzej miliona powinno wystarczyc 2 (czasem 1)

ull DOTESTU[6] = {61, 2, 3, 5, 7, 11};

ull mnozenie(ull x, ull y, ull MOD)	//dziala dla liczb do 10^18. 
{
	ull maska = 15, wynik=0;
	while(y > 0)
	{
		wynik =  (wynik + (maska & y) * x) % MOD;
		x  = (x<<4)%MOD;
		y >>= 4;
	}
	return wynik;
}

ull pot(ull x, ull wyk, ull MOD)
{
	if (wyk == 0)
		return 1;
	if (wyk == 1)
		return x;
	if (wyk%2 == 1)
		return mnozenie(x, pot(mnozenie(x, x, MOD), wyk/2, MOD), MOD);
	return pot(mnozenie(x, x, MOD), wyk/2, MOD);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//UWAGA LT = 1 to czasem za mało, zbyt małe LT może być powodem WA !!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//dla malych liczb sito? (najlepiej yarin sieve, znajduje wszystkie pierwsze do 10^9 w 5 sekund) 
//0 gdy zlozona
bool TestMR(ull liczba) 
{
    bool czy;
    if (liczba%2==0)
        return 0;
    ull s=0, d=liczba-1, a, pom;
    while(d%2==0)
    {
        s++;
        d/=2;
    }
    for(int i=0; i<LT; i++)
    {
        czy = false;
        a = DOTESTU[i];
        pom = pot(a, d, liczba);
        if ( pom == 1)
            continue;
        czy = true;
        for(ull r=0; r<s; r++)
        {
            if (pom==liczba-1)
            {
                czy=false;
                break;
            }
            if (pom == 1)
				return 0;
            pom = mnozenie(pom, pom, liczba);
        }
        if (czy)
            return 0;
    }
    return 1;
}
 
ull F(ull x, ull M)
{
	ull temp = mnozenie(x, x, M);
	if (temp == 0)
		temp += M;
	return temp-1;
}

ull RHOPollard(ull K)
{
	ull pom = rand()%K;
	if (pom == 0)
		pom++;
	if (TestMR(K))
		return K;
	ull potega = 4;
	vector < ull > V(potega);
	V[0] = pom;
	for(uint i=1; i<potega; i++)
		V[i] = F(V[i-1], K);
	bool koncz = false;
	while(!koncz)
	{
		for(uint i=0; i<potega-1; i++)
		{
			koncz |= (V.back() == V[i]);
			ull pom = __gcd( max(V[i], V.back()) - min(V[i], V.back()), K);
			if (pom > 1 && pom < K)
				return pom;
		}
		V.resize(2*potega);
		for(uint i = potega; i<2*potega; i++)
			V[i] = F(V[i-1], K);
		potega *= 2;
	}
	return RHOPollard(K);
}


#define mala 100000
ll sito[mala+1];

vector < pair <ull,int> > rozloz(ll M)
{
	vector < ll > V = {M};
	vector < pair < ull, int > > Odp;
	while(V.size())
	{
		ll pom = V.back(), dz;
		V.pop_back();
		if (pom == 1)
			continue;
		if (pom > mala)
			dz = RHOPollard(pom);
		else
			dz = sito[pom];
		if (dz == pom)
		{
			int ile = 1;
			for(auto& el : V)
			{
				while(el % dz==0)
				{
					ile++;
					el /= dz;
				}
			}
			Odp.push_back({dz, ile});
		}
		else
		{
			V.push_back(max(dz, pom/dz));
			V.push_back(min(dz, pom/dz));
		}
	}
	return Odp;
}

void sito_eratostenesa()//uzyc na poczatku maina
{
	for(int i=2; i<=mala; i++)
		sito[i] = i;
	for(int i=2; i*i<=mala; i++)
		if (sito[i] == i)
			for(int j = 2*i; j<=mala; j+=i)
				sito[j] = i;
}

int main()
{
	sito_eratostenesa();
}
/*
if n < 2,047, it is enough to test a = 2;
if n < 1,373,653, it is enough to test a = 2 and 3;
if n < 9,080,191, it is enough to test a = 31 and 73;
if n < 25,326,001, it is enough to test a = 2, 3, and 5;
if n < 3,215,031,751, it is enough to test a = 2, 3, 5, and 7;
if n < 4,759,123,141, it is enough to test a = 2, 7, and 61;
if n < 1,122,004,669,633, it is enough to test a = 2, 13, 23, and 1662803;
if n < 2,152,302,898,747, it is enough to test a = 2, 3, 5, 7, and 11;
if n < 3,474,749,660,383, it is enough to test a = 2, 3, 5, 7, 11, and 13;
if n < 341,550,071,728,321, it is enough to test a = 2, 3, 5, 7, 11, 13, and 17.
Using the work of Feitsma and Galway enumerating all base 2 pseudoprimes in 2010, this was extended (see OEIS A014233), with the first result later shown using different methods in Jiang and Deng:[10]

if n < 3,825,123,056,546,413,051, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, and 23.
if n < 18,446,744,073,709,551,616 = 264, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37.
Sorenson and Webster[11] verify the above and calculate precise results for these larger than 64-bit results:

if n < 318,665,857,834,031,151,167,461, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, and 37.
if n < 3,317,044,064,679,887,385,961,981, it is enough to test a = 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, and 41.
*/
