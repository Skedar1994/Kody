typedef long long R;//uwaga, tu jest long long!
typedef complex<R> C;

#define x real()
#define y imag()


R det(C c1, C c2) { return c1.x * c2.y - c1.y * c2.x;}

struct Wk
{
	C wsp;
	int nr;
};

C start;

bool op(const Wk& w1, const Wk& w2)
{
	C ws1(w1.wsp- start), ws2(w2.wsp - start);
	ll cross = det(ws1, ws2);
	if (!cross)
		return norm(ws1) < norm(ws2);
	return cross > 0;
}
//dodajemy punkty (Wk) i na koniec odpalamy policz. wynik jest w odp
struct Convex_Hull
{
	vector < Wk > pkty;
	vector < Wk > odp;
	void dodaj(Wk& W) { pkty.pb(W);}
	void policz()
	{
		assert(SZ(pkty));
		start = pkty[0].wsp;
		int ind = 0;
		for(int i=1; i<SZ(pkty); i++)
			if (pkty[i].wsp.y < start.y || (pkty[i].wsp.y == start.y && pkty[i].wsp.x < start.x))
				start = pkty[i].wsp, ind = i;
		odp.pb(pkty[ind]);
		pkty.erase(pkty.begin() + ind);
		sort(all(pkty), op);
		for(int i=0; i<SZ(pkty); i++)
		{
			while(odp.size() > 1 && det(odp.back().wsp - odp[SZ(odp)-2].wsp, pkty[i].wsp - odp[SZ(odp)-2].wsp) <= 0)
				odp.pop_back();
			odp.pb(pkty[i]);
		}
		while(odp.size() > 2 && det(odp.back().wsp - odp[SZ(odp)-2].wsp, odp[0].wsp - odp[SZ(odp)-2].wsp) <= 0)
			odp.pop_back();
	}
};
