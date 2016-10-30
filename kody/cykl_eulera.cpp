#include<bits/stdc++.h>
#define rep(i,k,n) for(ll i= (ll) k;i< (ll) n;i++)
#define all(v) (v).begin(), (v).end()
#define SZ(v) (int)((v).size())
#define pb push_back
#define ft first
#define sd second
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const long long INF = 4e18L + 1;
const int IINF = 2e9 + 1;
const int limit = 1048576;

using namespace std;

#define LOCAL
#ifndef LOCAL
#define cerr if(0)cout
#define endl "\n"
#endif

//UWAGA! na wejsciu podajemy liczbe wierzcholkow i liste krawedzi!
//zmienna znaleziono jest prawda gdy cykl istnieje
//jesli cykl istnieje, to kolejne wierzcholki sa w vectorze O, pierwszy wierzcholek jest rownie ostanim w odpowiedzi!
struct Euler
{
	bool znaleziono;
	vector < vector < pair <int, int> > > V;
	vector < int > O, S, Odw; //O - odpowiedz, S - stos, Odw - czy wrzucilismy krawedz
	Euler(int n, const vector < pair < int, int > >& E) : znaleziono(0), V(n+1), Odw(SZ(E))   
	{
		for(int i=0; i<SZ(E); i++)
		{
			V[E[i].ft].pb({E[i].sd, i});
			V[E[i].sd].pb({E[i].ft, i});
		}
		int start = 0;
		for(int i=0; i<SZ(V); i++)
		{
			if(SZ(V[i])%2 != 0)
				return;
			if (SZ(V[i]))
				start = i;
		}
		S.push_back(start);
		while(S.size()>0)
		{
			int akt = S[S.size()-1];
			while(V[akt].size() && Odw[V[akt][V[akt].size()-1].second]==1)
				V[akt].pop_back();
			if (V[akt].size() == 0)
			{
				S.pop_back();
				O.push_back(akt);
			}
			else
			{
				Odw[V[akt][V[akt].size()-1].second]=1;
				S.push_back(V[akt][V[akt].size()-1].first);
			}
		}
		if (SZ(E) + 1 == SZ(O))
			znaleziono = 1;
	}
};

int main()
{
}
