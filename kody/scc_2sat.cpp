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

/*
numerujemy wierzcholki od 0
SS to vector o rozmiarze rownym liczbe sss 
SS[i] to lista wierzcholkow dla pojedynczej spojnej
ss_ind[i] mowi, jaki jest numer spojnej skladowej wierzcholki i-tego
GSS to graf na spojnych skladowych (dag)
*/
struct SSS
{	
	vector < vector < int > >& V, W, SS, GSS;
	vector < int > odw, kol, ss_ind;
	int nr;
	SSS(int n, vector < vector < int > >& V) : V(V), W(V.size()), odw(n), kol(n), ss_ind(n, -1), nr(0) 
	{
		for(int i=0; i<n; i++)
			for(auto el : V[i])
				W[el].pb(i);	
		for(int i=0; i<n; i++)
			if(!odw[i])
				dfs(i);
				
		for(int i=n-1; i>=0; i--)
			if(-1 == ss_ind[kol[i]])
			{
				SS.resize(SS.size()+1);
				dfs_odwr(kol[i]);
			}
		GSS.resize(SS.size());
		for(int i=0; i<n; i++)
			for(auto el : V[i])
				if (ss_ind[i] != ss_ind[el])
					GSS[ss_ind[i]].pb(ss_ind[el]);
		// ta petla usuwa krawedzie wielokrotne w grafie na silnie spojnych 
		// w czasie n log n, mozna  ja usunac
		for(auto& el : GSS) 
		{
			sort(el.begin(), el.end());
			el.resize(distance(el.begin(), unique(all(el))));
		}
	}
	void dfs(int v)
	{
		odw[v] = 1;
		for(int i=0; i<SZ(V[v]); i++)
			if (!odw[V[v][i]])
				dfs(V[v][i]);
		kol[nr++] =  v;
	}
	void dfs_odwr(int v)
	{
		SS.back().push_back(v);
		ss_ind[v] = SS.size() - 1;
		for(int i=0; i<SZ(W[v]); i++)
			if(-1 == ss_ind[W[v][i]])
				dfs_odwr(W[v][i]);
	}
};

/*
Numerujemy od 0 zmienne.
Przyklad: "(x1 v x2 ) ^ (~x1 v x3)"
------------------------------
Instrukcja konstruktora:
n liczba zmiennych (dla przykladu n to 3)
------------------------------
Instrukcja uzycia:
DWASAT dwasat(n);
klauzule xi v ~xj dodajemy : dwasat.dodaj(i, i+n)
na koniec odbalamy dwasat.rob
wartosc i-tej zmiennej to dwasat.Wel[i]
*/

struct DWASAT
{
	int n;
	vector < int > Para; 
	vector < vector < int > > V;
	vector < int > Wss, Wel;
	SSS* sss;
	DWASAT(int n) : n(2*n), V(2*n), Wss(2*n, 0), Wel(2*n, 0) 
	{
		Para.resize(2*n);
		for(int i=0; i<n; i++)
			Para[i] = i + n;
		for(int i=n; i<2*n; i++)
			Para[i] = i - n;
	}
	void dodaj(int a, int b) 
	{
		V[ Para[a] ].pb(b);
		V[ Para[b] ].pb(a);
	}
	bool rob()
	{
		sss = new SSS(n, V);
		vector < int > kol = toposort(sss->SS.size(), sss->GSS);
		for(int i = SZ(kol)-1; i>=0; i--)
			if (!Wss[kol[i]])
			{
				Wss[kol[i]] = 1;
				for(auto& el : sss->SS[i])
				{
					Wel[el] = 1;
					int zaprz = Para[el];
					if (Wel[zaprz] == 1)
						return false;
					Wel[zaprz] = -1;
					Wss[sss->ss_ind[zaprz]] = -1;
				}
			}
		return true;
	}
	vector < int > toposort(int n, vector < vector < int > >& G)//grafu sa na koncu
	{
		queue < int > Q;
		vector < int > st(n, 0), odp;
		for(auto& el : G)
			for(auto v : el)
				st[v]++;
		for(int i=0; i<n; i++)
			if (st[i] == 0)
				Q.push(i);
		while(!Q.empty())
		{
			odp.pb(Q.front());
			for(auto& el : G[Q.front()])
			{
				st[el]--;
				if (!st[el]) 
					Q.push(el);
			}
			Q.pop();
		}
		return odp;
	}
};

int main()
{
	return 0;
}
