typedef long long R;
typedef complex<R> C;

#define x real()
#define y imag()

R det(C c1, C c2){ return c1.x * c2.y - c1.y * c2.x; }

C start;

bool op(const C& w1, const C& w2){
	C ws1 = w1 - start, ws2 = w2 - start;
	ll cross = det(ws1, ws2);
	if(!cross){
		return norm(ws1) < norm(ws2);
	}
	return cross > 0;
}

//zmienic <= na <, jesli maja byc punkty wspolliniowe na otoczce
bool wrong(const C& v1, const C& v2, const C& v3){ return det(v2 - v1, v3 - v1) <= 0;}

struct Convex_Hull{
	vector<C> pkty;
	vector<C> odp;
	void dodaj(C& c) { pkty.pb(c); }
	void policz() {
		/*odkomentować jeśli chcemy mieć wspóliniowe pkty na otoczce, a są duplikaty w wejściu
		sort(all(pkty), [&](auto& c1, auto& c2){ return make_pair(c1.x, c1.y) < make_pair(c2.x, c2.y);});
		pkty.resize(unique(all(pkty)) - pkty.begin());
		*/
		start = pkty[0];
		int ind = 0;
		for(int i = 1; i < SZ(pkty); i++){
			if(pkty[i].y < start.y or (pkty[i].y == start.y and pkty[i].x < start.x)){
				start = pkty[i], ind = i;
			}
		}
		odp.pb(pkty[ind]);
		pkty.erase(pkty.begin() + ind);
		sort(all(pkty), op);
		/* odkomentowac jesli maja byc wspolliniowe
		int i;
		for(i = 0; i < SZ(pkty) - 1; i++){
			if(det(pkty.rbegin()[i] - start, pkty.rbegin()[i + 1] - start) != 0){
				break;
			}
		}
		reverse(pkty.rbegin(), pkty.rbegin() + i + 1);
		*/
		for(auto& p : pkty){
			while(SZ(odp) > 1 and wrong(odp.rbegin()[1], odp.back(), p)){
				odp.pop_back();
			}
			odp.pb(p);
		}
		while(SZ(odp) > 2 and wrong(odp.rbegin()[1], odp.back(), odp[0])){
			odp.pop_back();
		}
	}
	//zwrca kwadrat odleglosci. wywoluje w sobie szuknie otoczki
	R najdalsza_para_punktow()
	{
		policz();
		int p = 0, k = 0;
		for(int i=1; i<SZ(odp); i++)
		{
			if (odp[i].x < odp[p].x)
				p = i;
			if (odp[i].x >= odp[k].x)
				k = i;
		}
		R wyn = 0;
		for(int i=0; i<2*SZ(odp); i++)
		{
			wyn = max(wyn, (ll)norm(odp[p] - odp[k]));
			int np = (p + 1) % SZ(odp), nk = (k + 1) % SZ(odp);
			if (det(odp[p] - odp[np], odp[k] - odp[nk]) < 0)
				p = np;
			else
				k = nk;
		}
		return wyn;
	}
};
