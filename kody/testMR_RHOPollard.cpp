#include <bits/stdc++.h>
#define LT 1						//dla liczb powyzej miliona powinno wystarczyc 1
typedef unsigned long long ull;
using namespace std;

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
 
bool TestMR(ull liczba) //dla malych liczb sito? 0 gdy zlozona
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
    ull ile=0, akt=1, next;
	ull D=1;
	ull pom = rand()%K;
	if (pom == 0 ) 
		pom++;
	if (TestMR(K))	//TestMR moze slabo dzialac dla K<10000
		return K;
	ull x=F(F(pom, K), K), y=F(pom, K);
	while(x!=y)
	{
        ile++;
        next = mnozenie(akt, abs(x-y), K);
       if (next==0) 
            ile=100;
        else
            akt=next;
        if (ile==100)
        {
            ile = 0;
		    D=__gcd( K, akt );
		    if (D>1)
			    return D;
			akt=1;
        }
		x=F(F(x, K), K);
		y=F(y, K);
	}
	D=__gcd( K, akt );
	if (D>1)
		return D;
	return RHOPollard(K);
}

int main()
{

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
