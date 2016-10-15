#include<bits/stdc++.h>
#define rep(i,k,n) for(ll i= (ll) k;i< (ll) n;i++)
#define all(v) (v).begin(), (v).end()
#define SZ(v) (int)((v).size())
#define pb push_back
#define ft first
#define sd second
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const long long INF = 4e18L + 1;
const int IINF = 2e9 + 1;
const int limit = 1048576;
 
using namespace std;
 
#define LOCAL
#ifndef LOCAL
#define cerr if(0)cout
#define endl "\n"
#endif
 
 
typedef int TYP;
 
struct wezel
{
	TYP war;
	wezel* l;
	wezel* r;
	wezel* p;
	int wp;
	wezel(TYP war) : war(war), l(0), r(0), p(0), wp(1) {}
};
 
struct Splay
{
	wezel* korzen;
	Splay() : korzen(0) {}
	void napraw(wezel* w)
	{
		int wp = 1;
		if (w->l)
			wp += w->l->wp;
		if (w->r)
			wp += w->r->wp;
		w->wp = wp;
	}
	wezel* ostatni()
	{
		if (!korzen)
			return 0;
		wezel* wyn = korzen;
		while(wyn->r) 
			wyn = wyn->r;
		splay(wyn);
		return wyn;
	}
	wezel* poprzedni(wezel* w)
	{
		splay(w);
		wezel* p = 0;
		w = w->l;
		while(w)
		{
			p = w;
			w = w->r;
		}
		return p;
	}
	void splay(wezel* w)
	{
		if (korzen == w)
			return;
		if (w->p == korzen)
		{
			if (korzen->l == w)
				prawa_rotacja(korzen);
			else
				lewa_rotacja(korzen);
			return;
		}
		wezel *p = w->p, *gp = p->p;
		if (gp->l == p)
		{
			if (p->l == w)
			{
				prawa_rotacja(gp);
				prawa_rotacja(p);
			}
			else
			{
				lewa_rotacja(p);
				prawa_rotacja(gp);
			}
		}
		else
		{
			if (p->l == w)
			{
				prawa_rotacja(p);
				lewa_rotacja(gp);
			}
			else
			{
				lewa_rotacja(gp);
				lewa_rotacja(p);
			}
		} 
		return splay(w);
	}
	
	void lewa_rotacja(wezel* w) //wywolujemy na ojcu
	{
		wezel *r = w->r, *p = w->p;
		w->r = r->l;
		w->p = r;
		r->p = p;
		r->l = w;
		if (p)
		{
			if (p->r == w)
				p->r = r;
			else
				p->l = r;
		}
		if (w->r)
			w->r->p = w;
		napraw(w);
		napraw(r);
		if (w == korzen)
			korzen = r;
	}
	void prawa_rotacja(wezel* w)
	{
		wezel *l = w->l, *p = w->p;
		w->l = l->r;
		w->p = l;
		l->p = p;
		l->r = w;
		if (p)
		{
			if (p->r == w)
				p->r = l;
			else
				p->l = l;
		}
		if (w->l)
			w->l->p = w;
		napraw(w);
		napraw(l);
		if (w == korzen)
			korzen = l;
	}
	void split(Splay& T1, Splay& T2, wezel* w) //w to ostatni wezel ktory zawiera sie w T1 (moze byc nulem). dzielimy nas w dwa drzewa
	{
		if (!w)
		{
			wezel* korzen = this->korzen;
			T1.korzen = 0;
			T2.korzen = korzen;
			return;
		}
		splay(w);
		T1.korzen = w;
		T2.korzen = w->r;
		w->p = 0;
		w->r = 0;
		napraw(w);
		if (T2.korzen)
			T2.korzen->p = 0;
	}
	void join(Splay& T1, Splay& T2)//my stajemy sie joinem dwoch drzew
	{
		if (!T1.korzen)
			korzen = T2.korzen;
		else if (!T2.korzen)
			korzen = T1.korzen;
		else
		{
			T1.ostatni();
			T1.korzen->r = T2.korzen;
			T2.korzen->p = T1.korzen;
			korzen = T1.korzen;
			napraw(korzen);
		}
	}
	wezel* znajdz_ity(int i)//indeksowanie od 1 !
	{
		if (!i)
			return 0;
		wezel* w = korzen;
		while(w)
		{
			int lp = 0;
			if (w->l)
				lp = w->l->wp;
			if (lp+1 == i)
			{
				splay(w);
				return w;
			}
			if (lp >= i)
			{
				w = w->l;
				continue;
			}
			i -= lp + 1;
			w = w->r;
		}
		return 0;
	}
	void usun(wezel* w)//nie uzywam delete na nim!
	{
		Splay T1, T2;
		split(T1, T2, w);
		T1.korzen = w->l;
		if (w->l)
			w->l->p = 0;
		join(T1, T2);
	}
/// uzywaj albo tego
	void dodaj_na_koniec(TYP war){dodaj_na_koniec(new wezel(war));}
	void dodaj_na_koniec(wezel* w)
	{
		w->l = w->r = w->p = 0;
		if (!korzen)
		{
			korzen = w;
			return;
		}
		ostatni();
		korzen->p = w;
		w->l = korzen;
		korzen = w;
		napraw(w);
	}
/// albo tego (do konca)
	wezel* znajdz(TYP war)
	{
		if (!korzen)
			return korzen;
		wezel* w = korzen, *p = w;
		while(w)
		{
			p = w;
			if (w->war == war)
				break;
			if (w->war > war)
				w = w->l;
			else
				w = w->r;
		}
		splay(p);
		return p->war == war ? p : 0;
	}
	void dodaj(TYP war){dodaj(new wezel(war));}
	void dodaj(wezel* w)
	{ 
		w->l = w->r = w->p = 0;
		if (korzen)
		{
			znajdz(w->war);
			if (korzen->war == w->war)
				return;
			Splay T1, T2;
			if (korzen->war > w->war)
				split(T1, T2, poprzedni(korzen));
			else
				split(T1, T2, korzen);
			w->l = T1.korzen;
			if (T1.korzen)
				T1.korzen->p = w;
			w->r = T2.korzen;
			if (T2.korzen)
				T2.korzen->p = w;
			korzen = w;
		}
		else
			korzen = w;
		napraw(w);
	}
	int indeks(wezel* w)
	{
		if (!w) return -1;
		splay(w);
		if (w->l)
			return 1 + w->l->wp;
		return 1;
	}
};
 
int main()
{
}
