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


struct LCA
{
	int n, k, czas, pot;
	vector < vector < int > >&V;
	vector < int > cz, pw, pom;
	LCA(int n, int korzen, vector < vector < int > >&V) : n(n), k(korzen), czas(0), V(V), cz(n+1), pw(n+1, 0)
	{
		pot = 1;
		while(pot < 2*n+2) pot *= 2;
		pom.reserve(2*pot);
		pom.resize(pot+1);
		dfs(k);
		for(int i = pot-1; i>0; i--)
			pom[i] = min(pom[2*i], pom[2*i+1]);
		
	}
	void dfs(int v)
	{
		int t = ++czas;
		cz[t] = v;
		pw[v] = pom.size();
		pom.pb(czas);
		for(int i=0; i<SZ(V[v]); i++)
			if (!pw[ V[v][i] ])
			{
				dfs( V[v][i] );
				pom.pb(t);
			}
	}
	int znajdz(int v, int u)
	{
		v = pw[v];
		u = pw[u];
		if (v > u)
			swap(v, u);
		int mini = min(pom[v], pom[u]);
		while(u - v > 1)
		{
			if (v%2 == 0)
				mini = min(mini, pom[v+1]);
			if (u%2 == 1)
				mini = min(mini, pom[u-1]);
			u/=2; v/=2;
		}
		return cz[mini];
	}
};

struct Zap{
	int l, r, nr, P;
	Zap(int l, int r, int nr, int P) : l(l), r(r), nr(nr), P(P)
	{}
	bool operator<(const Zap& inny) const 
	{
		return r < inny.r;
	}
};


/*
 * uzupelnic co ma sie dziac jak dodajemy wartosc, usuwamy ja albo pytamy sie jaka jest odpowiedz dla przedzialu
 * przykladowe uzupelnienie ponizej, nazwy funkcji musza zostac
 */
struct Przedzial
{
	/*
	vector < int > V, W;
	int wk;
	*/
	Przedzial()
	{
		/*
		V.resize(100005, 0);
		wk = 300;
		W.resize(400);
		for(auto& el : W)
			el = wk;
		*/ 
	}
	void dodaj(int co)
	{
		/*
		if (co > 100000)
			return;
		V[co]++;
		if (V[co] == 1)
			W[co/wk]--;					
		*/
	}
	void wyciagnij(int co)
	{
		/*
		if (co > 100000)
			return;
		V[co]--;
		if (!V[co])
			W[co/wk]++;
		*/
	}
	int pytaj()
	{
		/*
		int kk = 0;
		for(int i=0; i<400; i++)
			if (W[i])
			{
				kk = i;
				break;
			}
		for(int i=kk*wk; true; i++)
			if (!V[i])
				return i;
		*/ 
	}
};


/*
 * numerujemy od 1
 * V listy sasiedztwa
 * Z  lista zapytan
 * W lista wartosci w wierzcholkach
 * 
 * funkcja dodaj - co sie dzije, jak dochodzi wartosc do przedzialu
 * funkcja odejmij - co sie dzieje, jak wartosc z przedzialu wychodzi
 * 
 * UWAGA jesli mamy wartosci na krawedziach a nie w wierzcholkach:
 * W[v] to wartosc na krawedzi z v do ojca
 * podmienic dwie oznaczone ponizej linijki kodu
 */
struct MoDrzewo
{
	vector < int > ST, EN, T, Odp, wartosci;
	vector < vector < int > >& V;
	vector < vector < Zap > > zap;
	int t;
	LCA lca;
	MoDrzewo(int n, vector < vector < int > >&V, vector < pair < int, int > >& Z, vector < int >& W) : 
	ST(n+1), EN(n+1), T(2*n+2), Odp(SZ(Z)), V(V), t(0), lca(n, 1, V)
	{
		int pierw = sqrt(2*n);
		zap.resize(pierw+5);
		dfs(1);
		for(int i=0; i<SZ(Z); i++)
		{
			int u = Z[i].ft, v = Z[i].sd, p = lca.znajdz(u, v);
			if (ST[u] >= ST[v])
				swap(u, v);
			if (u == p)
			{
				int l = ST[u], r = ST[v];
				zap[l/pierw].pb(Zap(l, r, i, -1));// jesli krawedzie to linijka ma wygladac: zap[l/pierw].pb(Zap(l, r, i, ST[u]));
			}
			else
			{
				int l = EN[u], r = ST[v];
				zap[l/pierw].pb(Zap(l, r, i, ST[p]));//jesli krawedzie to linijka ma wygladac: zap[l/pierw].pb(Zap(l, r, i, -1));
			}
		}
		for(auto& el : zap)
			sort(all(el));
		for(int i=0; i<SZ(zap); i++)
		{
			if (!SZ(zap[i]))
				continue;
			Przedzial P;
			vector < int > ile(n+1, 0);
			int p = zap[i][0].l, k = p-1;
			for(auto& el : zap[i])
			{
				while(k < el.r)
				{
					k++;
					ile[T[k]]++;
					dodaj_do_przedzialu(P, T[k], ile, W);
				}
				while(p > el.l)
				{
					p--;
					ile[T[p]]++;
					dodaj_do_przedzialu(P, T[p], ile, W);
				}
				while(p < el.l)
				{
					ile[T[p]]--;
					dodaj_do_przedzialu(P, T[p], ile, W);
					p++;
				}
				if (el.P != -1)
				{
					ile[T[el.P]]++;
					dodaj_do_przedzialu(P, T[el.P], ile, W);
				}
				Odp[el.nr] = P.pytaj();
				if (el.P != -1)
				{
					ile[T[el.P]]--;
					dodaj_do_przedzialu(P, T[el.P], ile, W);
				}
			}
		} 
	}
	void dodaj_do_przedzialu(Przedzial& P, int v, vector < int>& ile, vector < int>& W)
	{
		if (ile[v] & 1)
			P.dodaj(W[v]);
		else
			P.wyciagnij(W[v]);
	}	
	void dfs(int v)
	{
		ST[v] = ++t;
		T[t] = v;
		for(int i=0; i<SZ(V[v]); i++)
			if (!ST[ V[v][i] ])
				dfs( V[v][i] );
		EN[v] = ++t;
		T[t] = v;
	}
};

int main()
{
}
