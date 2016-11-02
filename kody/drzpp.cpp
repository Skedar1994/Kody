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
