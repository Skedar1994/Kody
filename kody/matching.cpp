//po usunieciu zmiennej zostalo jest zazwyczaj szybciej (moze nawet jakies 1.5 raza)
//ale nie moge wtedy obiecac, ze na 100% bedzie zlozonosc O(msqrt(n))


//1. W str[i] kazdy wierzcholek powinien miec nr 0 lub 1 -> w zaleznosci od tego, po ktorej stronie grafu dwudzielnego jest
//2. Wierzcholki numerujemy od 1!
//3. n na wejściu to liczba wierzchołków, nie trzeba (a jak szukamy maksymalnego
//podzbioru niezaleznego to nie wolno) dawac n+1 na wejsciu

//Matching m(..); m.matching() znajduje wynik 
//mozna dodac! m.mpn() i to zwraca maksymalny podzbior niezalezny

//mpn musze przetestowac dzis o 19.00 (12.03.17)

struct Matching
{
	int n, wynik;
	vector < int > odl, str, para, odw;
	const vector < vector < int > >& V;
	Matching(int N, const vector < vector < int > >& M, const vector < int >& s) : n(N), odl(n+1), str(s), para(n+1), odw(n+1), V(M)
	{
	}
	bool DFS(int v, int ojciec, int zostalo)
	{
		if (zostalo < 0)
			return false;
		odw[v] = 1;
		if (!str[v])
		{
			if (!para[v])
				return (para[v] = ojciec);
			if (DFS(para[v], v, zostalo-1))
				return (para[v] = ojciec);
			return false;
		}
		for(int i=0; i<SZ(V[v]); i++)
			if (odl[ V[v][i] ] == odl[v] + 1 && !odw[ V[v][i] ] && DFS(V[v][i], v, zostalo-1))
				return (para[v] = V[v][i]);
		return false;
	}	
	int sciezki() 
	{
		memset(&odl[0], 0, 4*(n+1));
		memset(&odw[0], 0, 4*(n+1));
		int minodl = 2*n+5, ilezmian = 0;
		queue < pair <int, int> > Q;
		for(int i=1; i<=n; i++)
			if (str[i] && !para[i])
			{
				Q.push(make_pair(i, 1));
				odl[i] = 1;
			}
		while(!Q.empty())
		{
			int akt = Q.front().first, od=Q.front().second; Q.pop();
			if (!str[akt])
			{
				if (para[akt])
				{
					Q.push(make_pair(para[akt], od+1));
					odl[ para[akt] ] = od+1;
				}
				else
					minodl = min(minodl, od);                
				continue;
			}
			for(int i=0; i<SZ(V[akt]); i++)
				if (odl[ V[akt][i] ] == 0)
				{
					Q.push(make_pair(V[akt][i], od+1));
					odl[ V[akt][i] ] = od+1;
				}
		}
		for(int i=1; i<=n; i++)
			if (!odw[i] && str[i] && !para[i])
				ilezmian += DFS(i, -1, minodl-1);
		return ilezmian;
	}
	int matching()
	{
		int ile = 0, akt;
		while( (akt = sciezki()) )
			ile+=akt;
		return wynik = ile;
	}
	//to ponizej przepisujemy tylko gdy chcemy znalezc maksymalny podzbior niezalezny
	//zwraca maksymalny podzbior niezalezny z wierzcholkow od 1 do n
	vector < int > mpn()
	{
		vector < int > stan(n+1, 0);//0 - nieprzetworzony, 1 - wziety, -1 - nie moge wziac
		queue < int > Q;
		for(int i=1; i<=n; i++)
		{
			if(!para[i])
			{
				stan[i] = 1;
				Q.push(i);
			}
		}
		while(!Q.empty())
		{
			int x = Q.front();
			Q.pop();
			for(auto el : V[x])
			{
				if (stan[el]==0)
				{
					stan[el] = -1;
					stan[ para[el] ] = 1;
					Q.push(para[el]);
				}
			}
		}
		vector < int > odp;
		for(int i=1; i<=n; i++)
			if (stan[i] == 1 || (!stan[i] && str[i]))
				odp.pb(i);
		return odp;
	}
	
};
