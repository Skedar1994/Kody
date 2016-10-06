#include <iostream>

using namespace std;

const int pom = 262144*4;
int drzewko[2*pom+1], maks[2*pom+1];

void poprawdrzewko(int pocz, int kon, int ile)
{
    pocz += pom-1;
    kon += pom-1;
    drzewko[pocz]+=ile;
    maks[pocz] = drzewko[pocz];
    if (pocz == kon)
		return;
	drzewko[kon]+=ile;
	while(pocz/2 != kon/2)
	{
		if (pocz%2==0)
		{
			drzewko[pocz+1]+=ile;
			maks[pocz+1]+=ile;
		}
		if (kon%2==1)
		{
			drzewko[kon-1]+=ile;
			maks[kon-1]+=ile;
		}
		pocz/=2;
		kon/=2;
	}
}

void poprawmaks(int pocz, int kon)
{
    pocz += pom-1;
    maks[pocz] = drzewko[pocz];
    while(pocz>1)
    {
		pocz/=2;
		maks[pocz] = max(maks[pocz*2+1], maks[pocz*2]) + drzewko[pocz];
	}
	kon += pom-1;
	maks[kon] = drzewko[kon];
	while(kon>1)
	{
		kon/=2;
		maks[kon] = max(maks[kon*2+1], maks[kon*2])+drzewko[kon];
	}
}

void dodaj(int pocz, int kon, int ile)
{
	poprawdrzewko(pocz, kon, ile);
	poprawmaks(pocz, kon);
}

int znajdzmax(int pocz, int kon)
{
    pocz += pom-1;
    kon += pom-1;
    int aktpocz = maks[pocz], aktkon=maks[kon];
    while(pocz/2 != kon/2)
    {
        if (pocz%2==0)
            aktpocz = max(aktpocz, maks[pocz+1]); 
        aktpocz+= drzewko[pocz/2];
        
        if (kon%2==1)
            aktkon = max(aktkon, maks[kon-1]);
        aktkon += drzewko[kon/2];
        pocz/=2;
        kon/=2;
    }
    pocz/=2;
    int maks = max(aktpocz, aktkon) + drzewko[pocz]; 
    while(pocz > 0)
    {
		pocz/=2;
        maks += drzewko[pocz];
    }
    return maks;
}

int main()
{
    return 0;
}
