/*
Przed uzyciem MO musimy uzupelnic ponizsze 4 funkcje. 
(struktura MO mowi tylko, ktore indeksy dodajemy/wyjmujemy z przedzialu.)
Potem po wywolaniu konstruktora MO w vectorze odp beda odpowiedzi dla kolejnych zapytan (numerujemy od 0);
koniec calego przedzialu podzielony przez szerokosc musi byc mniejszy niz ile_kubelkow
*/
void czysc()//odpalane na poczatku liczenia wartosci dla danego kubelka
{
}

void dodaj(int indeks)
{
}

void wyjmij(int indeks)
{
}

ll aktualny_wynik()
{
}


struct MO
{
	struct Zap
	{
		int p, k, nr;
		Zap(int _p, int _k, int _nr) : p(_p), k(_k), nr(_nr) {}
		bool operator<(const Zap& z) const {return p < z.p;}
	};
	vector < ll > odp;
	vector < vector < Zap > > Kubelki;
	MO(int ile_kubelkow, int szerokosc, const vector < pair < int, int > > &przedzialy) : Kubelki(ile_kubelkow), odp(SZ(przedzialy))
	{
		for(int i=0; i<SZ(przedzialy); i++)
			Kubelki[przedzialy[i].sd/szerokosc].pb(Zap(przedzialy[i].ft, przedzialy[i].sd, i));
		for(int i=0; i<ile_kubelkow; i++)
		{
			if (SZ(Kubelki[i]) == 0)
				continue;
			czysc();
			sort(all(Kubelki[i]));
			int p = Kubelki[i][0].p, k = p-1;
			for(int j=0; j<SZ(Kubelki[i]); j++)
			{
				Zap z = Kubelki[i][j];
				while(p < z.p)
				{
					wyjmij(p);
					p++;
				}
				while(k < z.k)
				{
					k++;
					dodaj(k);
				}
				while(k > z.k)
				{
					wyjmij(k);
					k--;
				}
				odp[z.nr] = aktualny_wynik();
			}
		}
	}
};
