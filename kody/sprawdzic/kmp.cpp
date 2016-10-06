#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <string>
#include <list>
#include <set>
#define ll long long

using namespace std;

//na themisie acc
//na cf-ie chyba bylo wa przez funkcje prefiksowo sufiksowa czy jak jej tam

string s, z;
int P[1000005];

void tabP()
{
	P[0]=-1;
	P[1]=0;
	int akt = 0;
	for(int i=2; i<=s.size(); i++)
	{
		while(s[i-1] != s[akt] && akt>0)
			akt = P[akt];
		akt ++;
		P[i]=akt;
	}
}

bool czywz()
{
	int akt = 0;
	for(int i=0; i<z.size(); i++)
	{
		while(s[akt] != z[i] && akt>0)
			akt = P[akt];
		akt++;
		if (akt == s.size())
			return true;
	}
	return false;
}

int main()
{
	ios_base::sync_with_stdio(0);
	int testy;
	cin>>testy;
	while(testy--)
	{
		cin>>s>>z;
		if (s.size()!=z.size())
		{
			cout<<"NIE\n";
			continue;
		}
		z = z+z;
		tabP();
		if (czywz())
			cout<<"TAK\n";
		else
			cout<<"NIE\n";
	}
	return 0;
}
