#include <bits/stdc++.h>
#define pb push_back
#define ft first
#define sd second
#define inf 1000000000
using namespace std;

vector < vector < int > > V(100005);
vector < vector < int > > Baby(100005);
int mod[100005];

struct Sciezka
{
	vector < int > V;
	vector < pair <int, int> > War;
	void inicjuj()
	{
		War.resize(V.size(), {0, 0}); 
		for(int i=0; i<(int)V.size(); i++)
			War[i].sd = V[i];
	}
	void dodaj_wierzch(int v){V.pb(v);}
	//
	void dodaj(int ind_pocz, int ind_kon, int war)
	{
		assert(ind_pocz <= ind_kon);
		for(int i = ind_pocz; i<=ind_kon; i++)
			War[i].ft += war;
	}
	pair < int, int> mini(int pocz, int kon)
	{
		pair < int, int > wyn = {inf, 0};
		for(int i=pocz; i<=kon; i++)
			wyn = min(wyn, War[i]);
		return wyn;
	}
};

struct Info
{
	int nr_na_sciezce;
	int nr_sciezki;
	int roz_pod;//rozmiar poddrzewa
	int ojciec;
};

struct HLD
{
	vector < vector < int > >& V;
	vector < Sciezka > S;
	vector < Info > I;
	vector < int > Odw;//do dfs
	HLD(vector < vector < int > >& V, int korzen) : V(V), I(V.size()+1), Odw(V.size()+1, 0)
	{
		dfs_1(korzen, korzen);
		dfs_2(korzen, -1);
		for(auto& el : S)
			el.inicjuj();
	}
	int dfs_1(int v, int ojciec)
	{
		if (Odw[v])
			return 0;
		Odw[v] = 1;
		I[v].ojciec = ojciec;
		int roz = 1;
		for(auto& el : V[v])
			roz += dfs_1(el, v);
		I[v].roz_pod = roz;
		return roz;
	}
	void dfs_2(int v, int sc)
	{
		if (Odw[v] == 2)
			return;
		Odw[v] = 2;
		if (sc == -1)
		{
			sc = S.size();
			S.resize(sc+1);
		}
		I[v].nr_sciezki = sc;
		I[v].nr_na_sciezce = S[sc].V.size();
		S[sc].dodaj_wierzch(v);
		for(auto& el : V[v])
		{
			if (2 * I[el].roz_pod >= I[v].roz_pod)
				dfs_2(el, sc);
			else
				dfs_2(el, -1);
		}
	}
	pair < int, int > mini(int pocz, int kon)
	{
		int nr = I[pocz].nr_sciezki;
		if (nr == I[kon].nr_sciezki)
		{
			pair < int, int > p = S[nr].mini(I[kon].nr_na_sciezce, I[pocz].nr_na_sciezce);
			p.sd += mod[S[nr].V[0]];
			return p;
		}
		pair < int, int > p1 = S[nr].mini(0, I[pocz].nr_na_sciezce), p2 = mini(I[S[nr].V[0]].ojciec, kon);
		return min(p1, p2);
	}
	void dodaj(int pocz, int kon, int war)//UWAGA: kon to ma byc przodek pocz. Moze potrzebujesz LCA?
	{
		int nr = I[pocz].nr_sciezki;
		if (nr == I[kon].nr_sciezki)
		{
			S[nr].dodaj(I[kon].nr_na_sciezce, I[pocz].nr_na_sciezce, war);
			return;
		}
		S[nr].dodaj(0, I[pocz].nr_na_sciezce, war) ;
		dodaj(I[S[nr].V[0]].ojciec, kon, war);
		
	}
};

struct LCA
{
	int** ANC;
	int* wys;
	int n, korzen, logn;
	vector < vector < int > > V;
	LCA(int n, int korzen, vector < vector < int > > &V) : n(n), korzen(korzen), V(V)
	{
		V.resize(n+1);
		ANC = new int*[n+1];
		wys = new int[n+1];
		logn = 34 -__builtin_clz(n);
		for(int i=0; i<=n; i++)
				ANC[i] = new int[logn];
		oblicz_ANC();
	}
	void oblicz_ANC()
	{
		dfs(korzen, korzen);
		wys[korzen]=-1;
		for(int i=1; i<logn; i++)
			for(int j=0; j<=n; j++)
				ANC[j][i] = ANC[ ANC[j][i-1] ][i-1];
	}
	void dfs(int v, int ojciec)
	{
		wys[v] = 1 + wys[ojciec];
		ANC[v][0] = ojciec;
		for(auto sas : V[v])
			if (sas != ojciec)
				dfs(sas, v);
	}
	int znajdz(int v, int w)
	{
		if (wys[v] > wys[w]) 
			swap(v, w);
		for(int i = logn-1; i>=0; i--)
			if (wys[w] - (1<<i) >= wys[v])
				w = ANC[w][i];
		for(int i = logn-1; i>=0; i--)
			if (ANC[w][i] != ANC[v][i])
				w = ANC[w][i], v = ANC[v][i];
		return w == v ? w : ANC[w][0];
	}
};

int pre[100005], post[100005];

int nr = 1;
void dfs(int v)
{
	if (pre[v])
		return;
	pre[v] = nr++;
	for(auto& el : V[v])
	{
		dfs(el);
	}
	post[v] = nr;
}


int main()
{
	int n, m, q;
	cin>>n>>m>>q;
	for(int i=0; i<n-1; i++)
	{
		int a, b;
		cin>>a>>b;
		V[a].pb(b);
		V[b].pb(a);
	}
	dfs(1);
	HLD hld(V, 1);
	LCA lca(n, 1, V);
	for(int i=0; i<m; i++)
	{
		int a;
		cin>>a;
		Baby[a].pb(i);
	}
	for(int i=1; i<=n; i++)
	{
		reverse(Baby[i].begin(), Baby[i].end());
		if (!Baby[i].size())
			hld.dodaj(i, i, inf);
		else
			hld.dodaj(i, i, Baby[i].back());
	}
	
	
	while(q--)
	{
		int t;
		cin>>t;
		if (t == 1)
		{
			int v, u, k, pom;
			cin>>v>>u>>k;
			pom = lca.znajdz(v, u);
			vector < int > odp;
			while(k--)
			{
				auto p = min(hld.mini(v, pom), hld.mini(u, pom));
				int ans =  Baby[p.sd].back() + 1;
				if (ans < inf)
					odp.pb(ans);
				if (Baby[p.sd].size() == 1)
				{
					hld.dodaj(p.sd, p.sd, inf);
				}
				else
				{
					int size = Baby[p.sd].size();
					hld.dodaj(p.sd, p.sd, Baby[p.sd][size-2] - Baby[p.sd][size-1]);
				}
				Baby[p.sd].pop_back();
			}
			cout << odp.size() << " " ;
			for(auto el : odp)
				cout << el << " ";
			cout << "\n";
		}
		else
		{
			int v, k;
			cin>>v>>k;
			for(int i=pre[v]; i<=post[v]; i++)
				mod[i]+=k;
			int ojciec = hld.I[v].ojciec, sc1 = hld.I[v].nr_sciezki, sc2 = hld.I[ojciec].nr_sciezki;
			if (v != 1 && sc1 == sc2)
			{
				hld.S[sc1].dodaj(hld.I[v].nr_na_sciezce, hld.S[sc1].V.size()-1, k);
			}
		}
		
	}
}
/*
5 7 11
3 5
2 3
4 3
1 4
4 1 4 5 4 1 4
1 2 1 2
*/
