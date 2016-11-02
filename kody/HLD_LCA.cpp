struct drz_prz
{
	vector < int > V;
	int pot;
	drz_prz(int n)
	{
		pot = 2;
		while(pot < n)
			pot *= 2;
		V.resize(2*pot, 0);
	}
	void dodaj(int gdzie, int war)
	{
		gdzie += pot;
		V[gdzie] += war;
		while(gdzie > 1)
		{
			gdzie /= 2;
			V[gdzie] = max(V[gdzie*2], V[gdzie*2+1]);
		}
	}
	int maxi(int pocz, int kon)
	{
		pocz += pot; kon += pot;
		int wyn = max(V[pocz], V[kon]);
		while(kon - pocz > 1)
		{
			if (pocz%2 == 0)
				wyn = max(wyn, V[pocz+1]);
			if (kon%2 == 1)
				wyn = max(wyn, V[kon-1]);
			pocz/=2; kon/=2;
		}
		return wyn;
	}
};

struct Sciezka
{
	vector < int > V;
	drz_prz* drzewo;
	void inicjuj()
	{
		drzewo = new drz_prz(V.size());
	}
	void dodaj_wierzch(int v)
	{
		V.pb(v);
	}
	void dodaj(int ind_pocz, int ind_kon, int war)
	{
		assert(ind_pocz == ind_kon); //bo dla != nie testowalem
		drzewo->dodaj(ind_pocz, war);
	}
	int maxi(int pocz, int kon)
	{
		return drzewo->maxi(pocz, kon);
	}
};

struct Info
{
	int nr_na_sciezce;
	int nr_sciezki;
	int roz_pod;//rozmiar poddrzewa
	int ojciec;
};


//wierzcholki numerujemy od 1
struct HLD
{
	vector < vector < int > >& V;
	vector < Sciezka > S;
	vector < Info > I;
	vector < int > Odw;//do dfs
	HLD(vector < vector < int > >& V, int korzen) : V(V), I(V.size()), Odw(V.size(), 0)
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
	int maxi(int pocz, int kon)
	{
		int nr = I[pocz].nr_sciezki;
		if (nr == I[kon].nr_sciezki)
			return S[nr].maxi(I[kon].nr_na_sciezce, I[pocz].nr_na_sciezce);
		int m1 = S[nr].maxi(0, I[pocz].nr_na_sciezce), m2 = maxi(I[S[nr].V[0]].ojciec, kon);
		return max(m1, m2);
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

//wierzcholki numerujemy od 1
struct LCA
{
	vector < vector < int > >&V;
	vector < int > cz, pw, pom;
	int n, k, czas, pot;
	LCA(int n, int korzen, vector < vector < int > >&V) : n(n), k(korzen), V(V), cz(n+1), pw(n+1, 0), czas(0)
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
		for(int i=0; i<V[v].size(); i++)
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
