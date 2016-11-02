#define ILE 10
ld dist(pair < ll, ll > P1, pair < ll, ll > P2)
{
	ld dx = P1.ft - P2.ft, dy = P1.sd - P2.sd;
	return sqrt(dx*dx + dy*dy);
}

ld najkrotszy(vector < pair < ll, ll > > V)
{
	sort(all(V));
	set < pair < ll, ll > > po_X, po_Y;
	ld najkrotszy = 1e50;
	for(int i=0; i<SZ(V); i++)
	{
		ll aktx = V[i].ft;
		while(po_X.begin() != po_X.end() && ld(aktx - po_X.begin()->ft) > najkrotszy) 
		{
			po_Y.erase(po_Y.find(make_pair(po_X.begin()->sd, po_X.begin()->ft)));
			po_X.erase(po_X.begin());
		}
		set < pair < ll, ll > >::iterator it1, it2;
		po_X.insert(make_pair(V[i].ft, V[i].sd));
		it2 = it1 = po_Y.insert(make_pair(V[i].sd, V[i].ft)).first;
	 	int ile = ILE;
		while(ile-- && it1 != po_Y.begin())
		{
			it1--;
			najkrotszy = min(najkrotszy, dist((*it1), make_pair(V[i].sd, V[i].ft)));
		}
		ile = ILE; it2++;
		while(ile-- && it2 != po_Y.end())
		{
			najkrotszy = min(najkrotszy, dist((*it2), make_pair(V[i].sd, V[i].ft)));
			it2++;
		}
	}
	return najkrotszy;
}
