typedef long long R;//!!!!!!!!!!!!!!!!! long long
typedef complex<R> C;

#define x real()
#define y imag()


#define ILE 10

struct sortx {
  bool operator() (const C& A, const C& B) const {return A.x<B.x;}
};

struct sorty {
  bool operator() (const C& A, const C& B) const {return A.y<B.y;}
};


ld najkrotszy(vector < C > V)
{
	sort(all(V), sortx());
	set < C, sortx > po_X;
	set < C, sorty > po_Y;
	R najkrotszy = (1ll << 62);
	for(int i=0; i<SZ(V); i++)
	{
		ll aktx = V[i].x;
		while(po_X.begin() != po_X.end() && (aktx - po_X.begin()->x)*(aktx - po_X.begin()->x) > najkrotszy) 
		{
			po_Y.erase(po_Y.find(*po_X.begin()));
			po_X.erase(po_X.begin());
		}
		set < C >::iterator it1, it2;
		po_X.insert(V[i]);
		it2 = it1 = po_Y.insert(V[i]).ft;
	 	int ile = ILE;
		while(ile-- && it1 != po_Y.begin())
		{
			it1--;
			najkrotszy = min(najkrotszy, norm((*it1) - V[i]));
		}
		ile = ILE; it2++;
		while(ile-- && it2 != po_Y.end())
		{
			najkrotszy = min(najkrotszy, norm((*it2) - V[i]));
			it2++;
		}
	}
	return sqrt(ld(najkrotszy));
}

////
typedef long long R;
typedef complex<R> C;

#define x real()
#define y imag()

bool cmpX(const pair < C, int >& a, const pair < C, int >& b){ return (a.ft.x < b.ft.x) || (a.ft.x == b.ft.x && a.ft.y < b.ft.y); }
bool cmpY(const pair < C, int >& a, const pair < C, int >& b){ return a.ft.y < b.ft.y; }

namespace Najblizsze_pkty
{
	const int maxn = 100005;
	C wej[maxn];
	C odp[maxn];
	pair < C, int > pox[maxn];
	pair < C, int > poy[maxn*3];
	pair < C, int >* y_wsk;
	bool lepszy(int komu, int kogo)
	{
		C pkt = wej[komu], kand = wej[kogo];
		if (odp[komu] == pkt) return true;
		ll n1 = norm(pkt - odp[komu]), n2 = norm(pkt - kand);
		if (n1 != n2) return n2 < n1;
		if (odp[komu].x != kand.x)
			return odp[komu].x > kand.x;
		return odp[komu].y > kand.y;
	}
	void popraw(int komu, int kogo)
	{
		if (lepszy(komu, kogo)) odp[komu] = wej[kogo]; 
	}
	void popraw_z_tab(int komu, pair<C, int>* tab, int dl, int ind_kolegi, ll x_podzialu)
	{
		for(int i = ind_kolegi-1; i>=0; i--)
		{
			C kolega = tab[i].ft;
			popraw(komu, tab[i].sd);
			if (norm(C(x_podzialu, kolega.y)-wej[komu]) > norm(odp[komu] - wej[komu]))
				break;
		}
		for(int i = ind_kolegi; i<dl; i++)
		{
			C kolega = tab[i].ft;
			popraw(komu, tab[i].sd);
			if (norm(C(x_podzialu, kolega.y)-wej[komu]) > norm(odp[komu] - wej[komu]))
				break;
		}
	}
	void rob(pair<C, int>* pox, pair<C, int>* poy, int n)
	{
		if (n <= 1) return;
		int kl = n/2, kp = n-kl;
		pair<C, int> *poxl = pox, *poxp = pox+kl;
		pair<C, int> *poyl = y_wsk, *poyp = y_wsk + kl;
		C podzial = pox[kl-1].ft;
		y_wsk += n;
		int l_ind = 0, p_ind = 0;
		for(int i=0; i<n; i++)
		{
			C pkt = poy[i].ft;
			if (pkt.x < podzial.x || (pkt.x == podzial.x && pkt.y <= podzial.y))
				poyl[l_ind++] = poy[i];
			else
				poyp[p_ind++] = poy[i];
		}
		rob(poxl, poyl, kl);
		rob(poxp, poyp, kp);
		int ind_kolegi = 0;
		for(int i=0; i<kl; i++)
		{
			int moje_y = poyl[i].ft.y;
			while(ind_kolegi < kp-1 && poyp[ind_kolegi].ft.y < moje_y)
				ind_kolegi++;
			popraw_z_tab(poyl[i].sd, poyp, kp, ind_kolegi, podzial.x);
		}
		ind_kolegi = 0;
		for(int i=0; i<kp; i++)
		{
			int moje_y = poyp[i].ft.y;
			while(ind_kolegi < kl-1 && poyl[ind_kolegi].ft.y < moje_y)
				ind_kolegi++;
			popraw_z_tab(poyp[i].sd, poyl, kl, ind_kolegi, podzial.x);
		}
		y_wsk -= n;
	}
	vector<C> znajdz(const vector < C >& V)//to wywolac
	{
		int n = SZ(V);
		for(int i=0; i<n; i++)
		{
			wej[i] = V[i];
			pox[i] = {V[i], i};
			poy[i] = {V[i], i};
			odp[i] = V[i];
		}
		y_wsk = poy + SZ(V);
		sort(pox, pox+n, cmpX);
		sort(poy, poy+n, cmpY);
		rob(pox, poy, n);
		vector < C > ret(n);
		for(int i=0; i<n; i++)
			ret[i] = odp[i];
		return ret;
	}
}
////////////
