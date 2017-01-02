/*
KMR kmr(tekst);
potem zeby sprawdzic czy dwa podciagi sa rowne to sprawdzamy kmr.wartosc(pocz1, kon1) == mr.wartosc(pocz2, kon2)
*/

#define najmniejsza_litera 0 //Mozna dac 'A', przydatne gdy sa krotkie stringi
struct KMR
{
	typedef pair < pair < int, int >, int > Trzy;
	vector < vector < int > > V;
	string s;
	int loga;
	KMR(const string& tekst)
	{
		assert(SZ(tekst)>0);
		s = tekst;
		int dl = SZ(tekst);
		loga = 31 - __builtin_clz(SZ(tekst));
		if (__builtin_popcount(dl) != 1)
		{
			loga++;
			dl = (1<<loga);
			s.resize(dl, najmniejsza_litera);
		}
		V.resize(loga+1);
		for(int i=0; i<SZ(V); i++)
			V[i].reserve(dl);
		V[0].resize(dl);
		for(int i=0; i<dl; i++)//4, 3, 1
			V[0][i] = s[i] - najmniejsza_litera;
		for(int i=1; i<=loga; i++)
		{
			int siz = SZ(V[i-1]) - (1<<(i-1)); 
			vector < Trzy > T(siz);
			V[i].resize(siz);
			for(int j=0; j<siz; j++)
				T[j] = make_pair(make_pair(V[i-1][j], V[i-1][j + (1<<(i-1))]), j);
			//sort(all(T));//wolniejsze, ale szybciej sie przepisuje
			sort_kubelkowy(T);//szybesz, ale trzeba przepisac sort_kubelkowy i kubelki_do_vec
			int nr = 0;
			for(int j=0; j<siz; j++)
			{
				if (j > 0 && (T[j].ft != T[j-1].ft))
					nr++;
				V[i][ T[j].sd ] = nr;
			}
		}
	}
	pair < int, int > wartosc(int pocz, int kon)
	{
		int x = 31 - __builtin_clz(kon-pocz+1);
		return make_pair(V[x][pocz], V[x][kon+1-(1<<x)]);
	}
	void sort_kubelkowy(vector < Trzy >& W)
	{
		int maks = 0;
		for(int i=0; i<SZ(W); i++)
		{
			maks = max(maks, W[i].ft.ft);
			maks = max(maks, W[i].ft.sd);
		}
		vector < vector < Trzy > > Kubelki(maks+1);
		for(int i=0; i<SZ(W); i++)
		{
			Kubelki[W[i].ft.sd].pb(W[i]);
		}
		kubelki_do_vec(Kubelki, W);
		for(int i=0; i<SZ(W); i++)
			Kubelki[W[i].ft.ft].pb(W[i]);
		kubelki_do_vec(Kubelki, W);
	}
	void kubelki_do_vec(vector < vector < Trzy > >&K, vector < Trzy >& W)
	{
		W.clear();
		for(int i=0; i<SZ(K); i++)
		{
			for(int j=0; j<SZ(K[i]); j++)
				W.pb(K[i][j]);
			K[i].clear();
		}
	}
};
