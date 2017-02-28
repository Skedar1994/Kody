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
//rekurencyjne ustaw na przedziale, suma na przedziale
struct Wezel
{
	int l;
	int p;
	int suma;
	int ust;
};

struct drzewo_przed
{
	int pot;
	vector < Wezel > V;
	drzewo_przed(int n)
	{
		pot = 1;
		while(pot <= n)
			pot <<= 1;
		V.resize(2*pot, Wezel{0, 0, 0, -1});
		V[1].l = 1, V[1].p = pot;
		for(int i=1; i<pot; i++)
		{
			int s = (V[i].l+V[i].p)/2;
			V[2*i].l = V[i].l, V[2*i].p = s;
			V[2*i+1].l = s+1, V[2*i+1].p = V[i].p;
		}	
	}
	void propaguj(int nr)
	{
		if (V[nr].ust == -1)
			return;
		V[2*nr].ust = V[2*nr+1].ust = V[nr].ust;
		V[2*nr].suma = V[2*nr+1].suma = V[nr].suma/2;
		V[nr].ust = -1;
	}
	void ustaw(int pocz, int kon, int co, int nr = 1)
	{
		int l = V[nr].l, p = V[nr].p;
		int s = (p + l)/2;
		if (pocz == l && kon == p)
		{
			V[nr].ust = co;
			V[nr].suma = co * (p + 1 - l);
			return;
		}
		propaguj(nr);
		if (pocz <= s)
			ustaw(pocz, min(s, kon), co, 2*nr);
		if (kon >= s+1)
			ustaw(max(s+1, pocz), kon, co, 2*nr+1);
		V[nr].suma = V[nr*2].suma + V[nr*2+1].suma;
	}
	int suma(int pocz, int kon, int nr = 1)
	{
		int l = V[nr].l, p = V[nr].p;
		int s = (p + l)/2;
		if (pocz == l && kon == p)
			return V[nr].suma;
		propaguj(nr);
		int wyn = 0;
		if (pocz <= s)
			wyn += suma(pocz, min(s, kon), 2*nr);
		if (kon >= s+1)
			wyn += suma(max(s+1, pocz), kon, 2*nr+1);
		return wyn;
	}	
};
