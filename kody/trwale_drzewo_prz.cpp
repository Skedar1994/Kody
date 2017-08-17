/*
trwale drzewo przedzialowe
dodaj w punkcie
spytaj o sume w danym momencie
*/
struct Wezel
{
	Wezel* l, * p;
	ll war;
	Wezel(ll _w, Wezel* _l, Wezel* _p) : l(_l), p(_p), war(_w) {}
	Wezel(Wezel* w) {*this = *w;}
};
struct TDP
{
	vector < Wezel* > korzenie;
	int pot;
	TDP(int roz)
	{
		pot = (1 << ( 32 - __builtin_clz(roz) ));
		korzenie.pb(new Wezel(0, 0, 0)); 
		init(korzenie[0], pot);
	}
	void init(Wezel* w, int dl)
	{
		if (dl == 1) return;
		dl/=2;
		w->l = new Wezel(0, 0, 0);
		w->p = new Wezel(0, 0, 0);
		init(w->l, dl);
		init(w->p, dl);
	}
	void popraw(Wezel* w, int l, int p, int gdzie, int co)
	{
		if (l == p)
		{
			assert(l == gdzie);
			w->war += co;
			return;
		}
		int s = (l + p)/2;
		if (gdzie <= s)
		{
			w->l = new Wezel(w->l);
			popraw(w->l, l, s, gdzie, co);
		}	
		else
		{
			w->p = new Wezel(w->p);
			popraw(w->p, s+1, p, gdzie, co);
		}
		w->war = w->l->war + w->p->war;
	}
	ll suma(Wezel* k, int l, int p, int low, int high)
	{
		if (low >= l && high <= p) return k->war;
		if (low > p || high < l) return 0;
		int s = (low + high)/2;
		return suma(k->l, l, p, low, s) + suma(k->p, l, p, s+1, high);
	}
//-----------------------------------------------	to ponizej do uzywania
	void dodaj(int gdzie, int co) 
	{ 
		korzenie.pb(new Wezel(korzenie.back()));
		popraw(korzenie.back(), 0, pot-1, gdzie, co);
	}
	ll suma(int ktory, int l, int p) {return suma(korzenie[ktory], l, p, 0, pot-1);}
};
///////////////////////szukanie k-tej liczby na przedziale, jak liczby sa duze to przenumerowac
TDP* drzewo;
void init(vector < int >& tablica)//ta funkcja sie inicjuje drzewo
{
	int roz = 1;
	for(auto& el : tablica) roz = max(el, roz);
	drzewo = new TDP(roz);
	for(int i=0; i<SZ(tablica); i++)
		drzewo->dodaj(tablica[i], 1);
}
int zapyt(Wezel* duzo, Wezel* malo, int l, int p, int ktorego)
{
	if (l == p)
		return l;
	int ile = duzo->l->war - malo->l->war;
	if (ile >= ktorego)
		return zapyt(duzo->l, malo->l, l, (l+p)/2, ktorego);
	else
		return zapyt(duzo->p, malo->p, (l+p)/2+1, p, ktorego-ile);
}
int zapyt(int a, int b, int k) {return zapyt(drzewo->korzenie[b], drzewo->korzenie[a-1], 0, drzewo->pot-1, k);}//ta sie pyta, numerujemy od 1
