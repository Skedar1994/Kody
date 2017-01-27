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

/*
Jak mamy cos robic na krawedziach
to myslimy, ze kazda krawedz jest przypisana do nizszego z wierzcholkow koncowch

NUMER WIERZCHOLKA v W DRZEWIE PRZEDZIALOWYM TO num[v] !!!!!!!!!!!!!!!!!!
* UWAZAC NA LONG LONGI
*/
struct HLD
{
	vector < vector < int > > V;
	int korzen, akt_num;
	vector < int > num, wys, szczyt, wlp, ojc;//wielkosc poddrzewa
	drz_prz drzewo;
	HLD(int n, int korz, vector < vector < int > >& V_ini) : V(V_ini), korzen(korz), akt_num(1), num(n+1), wys(n+1), szczyt(n+1, 0), wlp(n+1, 0), ojc(n+1, 0), drzewo(n+1)
	{
		dfs(korz, 1, 1);
		buduj(korz, korz);
	}
	int dfs(int v, int h, int o)
	{
		wlp[v] = 1;
		wys[v] = h;		
		ojc[v] = o;
		for(auto& el : V[v])
			if(el != o)
				wlp[v] += dfs(el, h+1, v);
		return wlp[v];
	}
	void buduj(int v, int gora)
	{
		num[v] = akt_num++;
		szczyt[v] = gora;
		pair < int, int > ciezka(-1, -1);
		for(auto el : V[v])
			if(el != ojc[v])
				ciezka = max(ciezka, {wlp[el], el});
		if (ciezka.sd != -1)
			buduj(ciezka.sd, gora);
		for(auto el : V[v])
			if(el != ojc[v] && el != ciezka.sd)
				buduj(el, el);
	}
	int lca(int a, int b)
	{
		int sz_a = szczyt[a], sz_b = szczyt[b];
		if (sz_a == sz_b)
			return wys[a] < wys[b] ? a : b;
		if (wys[sz_a] > wys[sz_b])
			return lca(ojc[sz_a], b);
		else
			return lca(a, ojc[sz_b]);
	}
	vector < pair <int, int> > generuj_przedzialy(int dol, int gora)//gora to przodek szczytu
	{
		vector < pair < int, int> > Odp;
		Odp.reserve(20);
		while(szczyt[dol] != szczyt[gora])
		{
			Odp.pb({num[szczyt[dol]], num[dol]});
			dol = ojc[ szczyt[dol] ];
		}
		Odp.pb({num[gora], num[dol]});
		return Odp;
	}
	void dodaj(int gdzie, int co)
	{
		drzewo.dodaj(num[gdzie], co);
	}
	int zapyt(int a, int b)
	{
		int pom = lca(a, b), wyn = -IINF;
		auto V1 = generuj_przedzialy(a, pom), V2 = generuj_przedzialy(b, pom);
/*
Ten fragment trzeba odkomentowac, jesli nie chcemy liczyc dwa razy wierzchlka bedacego lca zapytania (np. gdy liczymy sume)
		if (V1.back().ft == V1.back().sd)
			V1.pop_back();
		else
			V1.back().ft++;
*/ 
/*
A jesli nie interesuje nas wcale wierzcholek bedacy LCA, to trzeba odkomentowac oba
		if (V2.back().ft == V2.back().sd)
			V2.pop_back();
		else
			V2.back().ft++;
*/ 
		for(auto& el : V1)
			wyn = max(wyn, drzewo.maxi(el.ft, el.sd));
		for(auto& el : V2)
			wyn = max(wyn, drzewo.maxi(el.ft, el.sd));
		return wyn;
	}
};
