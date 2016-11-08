typedef long long R;//!!!!!!!!!!!!!!!!! long long
typedef complex<R> C;

#define x real()
#define y imag()


#define ILE 10

struct sortx : binary_function <C,C,bool> {
  bool operator() (const C& A, const C& B) const {return A.x<B.x;}
};

struct sorty : binary_function <C,C,bool> {
  bool operator() (const C& A, const C& B) const {return A.x<B.x;}
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
