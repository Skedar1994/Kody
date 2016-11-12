struct wezel
{
	int war;
	wezel *l, *p;
	wezel(){l = nullptr; p = nullptr; war=0;}
	~wezel()
	{
		if (l != nullptr)
		{
			delete l;
			delete p;
		}
	}
};
struct drzewo
{
	int rozmiar=(1<<20);///////////////////////////////////////////////////////////////////
	wezel korzen;
	void dodaj(int x, int war)
	{
		wezel *w = &korzen;
		w -> war += war;
		int p = 0, k = rozmiar-1;	
		while(p != k)
		{
			if ( nullptr == w->l)
			{
				wezel *w1 = new wezel, *w2 = new wezel;
				w->l = w1;
				w->p = w2;
			}
			int s = (p + k)/2;
			if (s <	 x)
				{p = s + 1; w = w -> p;}
			else
				{k = s; w = w -> l;}
			w -> war += war;
		}
	}
	ll suma(int x, int y)
	{
		int p = 0, k = rozmiar-1, s;
		wezel *wl = &korzen, *wp = &korzen;
		while( wl->l != nullptr && wl==wp)
		{
			s = (p+k)/2;
			if (x <= s && y<=s)
				{wl = wl->l; wp = wp->l; k = s; continue;}
			if (x > s && y > s)
				{wl = wl->p; wp = wp->p; p = s+1; continue;}
			wl = wl -> l;
			wp = wp -> p;
		}
		if (wl == wp)
			return wl -> war;
		int pl = p, kl = s;
		ll wynik = 0;
		while( wl->p != nullptr)
		{
			int sl = (pl+kl)/2;
			if (x <= sl)
				{kl = sl; wynik += (ll)(wl->p)->war; wl = wl->l;}
			else
				{pl = sl+1; wl = wl->p;}
		}
		wynik += (ll)wl->war;
		p = s+1;
		while( wp->p != nullptr)
		{
			s = (p+k)/2;
			if (y > s)
				{p = s+1; wynik += (ll)(wp->l)->war; wp = wp->p;}
			else
				{k = s; wp = wp->l;}
		}
		wynik += (ll)wp->war;
		return wynik;
	}
};
