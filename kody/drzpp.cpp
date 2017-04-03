//iteracyjne dodaj na przedziale, suma/maks na przedziale
struct wezel
{
	ll war;//tylko dla maks
	ll mod;
	ll suma;//tylko dla sumy
};

//podajemy rozmiar, samo znajduje potege dwojki
struct drzewoprzedzialowe //max->min wystarczy zrobic define max min
{
	wezel* drzewo; int pot;
	drzewoprzedzialowe(int rozmiar)
	{
		pot = 1; while(pot <= rozmiar) pot <<= 1;
		drzewo = new wezel[2*pot];
		memset(drzewo, 0, 2*pot*(sizeof (wezel))); 
	}
	~drzewoprzedzialowe(){delete[] drzewo;}
	void dodaj(int p, int k, int war)
	{
		ll akt = 1;//tylko dla sumy
		p += pot; k += pot;
		drzewo[p].war += war; drzewo[p].suma += war;//mieszane
		if (p != k)
			drzewo[k].war += war, drzewo[k].suma += war;//mieszane //UWAGA, przecinek!
		while(p>1)
		{
			if (k-p > 1)
			{
				if (p%2 == 0)
					drzewo[p+1].mod += war, drzewo[p+1].war += war, drzewo[p+1].suma += akt*war;//mieszane
				if (k%2==1)
					drzewo[k-1].mod += war, drzewo[k-1].war += war, drzewo[k-1].suma += akt*war;//mieszane
			}
			k/=2; p/=2; akt*=2;
			drzewo[p].war = max(drzewo[2*p].war, drzewo[2*p+1].war) + drzewo[p].mod;//maks
			drzewo[k].war = max(drzewo[2*k].war, drzewo[2*k+1].war) + drzewo[k].mod;//maks
			drzewo[p].suma = drzewo[2*p].suma + drzewo[2*p+1].suma + drzewo[p].mod * akt;//suma
			drzewo[k].suma = drzewo[2*k].suma + drzewo[2*k+1].suma + drzewo[k].mod * akt;//suma
		}
	}
	ll maks(int p, int k)
	{
		p += pot; k += pot;
		ll wynp = drzewo[p].war, wynk = drzewo[k].war;
		while(p>1)
		{
			if (k-p > 1)
			{
				if (p%2 == 0)
					wynp = max(wynp, drzewo[p+1].war);
				if (k%2==1)
					wynk = max(wynk, drzewo[k-1].war);
			}
			k/=2; p/=2;
			wynp+=drzewo[p].mod; wynk+=drzewo[k].mod;			
		}
		return max(wynp, wynk);
	}
	ll suma(int p, int k)
	{
		p += pot; k += pot;
		ll suma = drzewo[p].suma, pp = 1, kp = 0, akt=1;
		if (p != k)
			suma += drzewo[k].suma, kp = 1;//UWAGA, przecinek!
		while(p>1)
		{
			if (k-p>1)
			{
				if (p%2 == 0)
					suma += drzewo[p+1].suma, pp += akt;//UWAGA, przecinek!
				if (k%2==1)
					suma += drzewo[k-1].suma, kp += akt;//UWAGA, przecinek!
			}
			k/=2; p/=2; akt*=2;
			suma += drzewo[p].mod * pp; 
			suma += drzewo[k].mod * kp;	
		}
		return suma;
	}
};
//------------------------------------------------------------------------------------
//łatwiejze do przerobienia, ciut wolniejsze
struct Wezel	//prop jest juz wliczone do sumy i maks dla wezla
{
	int l, p; 
	ll suma, maks, prop;
	void ustaw(int a, int b){l = a, p = b;}
};

struct Drzewo_przedzialowe
{
	Wezel* tab;
	int pot;
	Drzewo_przedzialowe(int n)
	{
		n++;
		pot = (1 << (32-__builtin_clz(n) ));
		DBG(pot);
		tab = new Wezel[2*pot];
		memset(tab, 0, 2*pot*sizeof(Wezel));
		tab[1].ustaw(0, pot-1);
		tab[1].p = pot-1;
		for(int i=1; i<pot; i++)
		{
			int s = (tab[i].l + tab[i].p)/2;
			tab[2*i].ustaw(tab[i].l, s);
			tab[2*i+1].ustaw(s+1, tab[i].p);
		}
	}
	void aktualizuj(int nr)/////////////to napisac tak jak potrzebujemy
	{
		tab[nr].maks = tab[nr].prop;
		tab[nr].suma = (tab[nr].p - tab[nr].l + 1ll) * tab[nr].prop;
		if (nr < pot)
		{
			tab[nr].maks += max(tab[2*nr].maks, tab[2*nr+1].maks);
			tab[nr].suma += tab[2*nr].suma + tab[2*nr+1].suma;
		}
	}
	//////// przykladowe zapytania
	ll suma(int l, int p, int nr=1)
	{
		if (l > tab[nr].p || p < tab[nr].l)
			return 0;
		if (l <= tab[nr].l && p >= tab[nr].p)
			return tab[nr].suma;
		else
			return suma(l, p, 2*nr)
				   + suma(l, p, 2*nr+1)
				   + (1ll + min(p, tab[nr].p) - max(l, tab[nr].l) ) * tab[nr].prop;
	}
	ll maks(int l, int p, int nr=1)
	{
		if (l > tab[nr].p || p < tab[nr].l)
			return -INF;
		if (l <= tab[nr].l && p >= tab[nr].p)
			return tab[nr].maks;
		else
			return max(maks(l, p, 2*nr), maks(l, p, 2*nr+1)) + tab[nr].prop;
	}
	///////////////
	void propaguj(int nr)
	{
		if (!tab[nr].prop)
			return;
		tab[2*nr].prop += tab[nr].prop;
		tab[2*nr+1].prop += tab[nr].prop;
		tab[nr].prop = 0;
		if (nr < pot)
		{
			aktualizuj(2*nr);
			aktualizuj(2*nr+1);
		}
		aktualizuj(nr);
	}
	void dodaj(ll co, int l, int p, int nr = 1)
	{
		if (l > tab[nr].p || p < tab[nr].l)
			return;
		if (l <= tab[nr].l && p >= tab[nr].p)
		{
			tab[nr].prop += co;
			aktualizuj(nr);
		}
		else
		{
			dodaj(co, l, p, 2*nr);
			dodaj(co, l, p, 2*nr+1);
			aktualizuj(nr);
		}
	}	
};
