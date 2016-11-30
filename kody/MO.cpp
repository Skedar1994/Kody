/*
Przed uzyciem MO musimy uzupelnic ponizsze 3 funkcje. 
(struktura MO mowi tylko, ktore indeksy dodajemy/wyjmujemy z przedzialu.)
Potem po wywolaniu konstruktora MO w vectorze odp beda odpowiedzi dla kolejnych zapytan (numerujemy od 0)
*/

void dodaj(int indeks)
{
}

void wyjmij(int indeks)
{
}

ll aktualny_wynik()
{
}

#define szerokosc_kubelka 1000
struct MO
{
	vector < ll > odp;
	struct Zap
	{
		int p, k, nr;
		Zap(int _p, int _k, int _nr) : p(_p), k(_k), nr(_nr) {}
		bool operator<(const Zap& z) const 
		{
			if (p/szerokosc_kubelka == z.p/szerokosc_kubelka)
				return k < z.k;
			return p/szerokosc_kubelka < z.p/szerokosc_kubelka;
		}
	};
	MO(const vector < pair < int, int > > &przedzialy) : odp(SZ(przedzialy))
	{
		vector < Zap > zapytania;
		zapytania.reserve(SZ(przedzialy));
		for(int i=0; i<SZ(przedzialy); i++)
			zapytania.pb(Zap(przedzialy[i].ft, przedzialy[i].sd, i));
		sort(all(zapytania));
		int p, k;
		if (SZ(zapytania))
		{
			p = zapytania[0].p;
			k = p-1;
		}
		for(int i=0; i<SZ(zapytania); i++)
		{
			Zap z = zapytania[i];
			while(p > z.p)
			{
				p--;
				dodaj(p);
			}
			while(k < z.k)
			{
				k++;
				dodaj(k);
			}
			while(p < z.p)
			{
				wyjmij(p);
				p++;
			}
			while(k > z.k)
			{
				wyjmij(k);
				k--;
			}
			odp[z.nr] = aktualny_wynik();
		}
	}
};
