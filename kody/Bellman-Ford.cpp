//skad, dokad, dl
typedef pair < ll , pair < int, int > > Trzy;
#define x ft
#define y sd.ft
#define z sd.sd

//zwraca pusty vector, gdy jest cykl ujemny
//INF - nie ma drogi
vector < ll > BF(int n, int s, vector < Trzy >& kr)
{
	vector < ll > D(n+1, INF);
	D[s] = 0;
	bool koniec = false;
	for(int i=0; !koniec && i<n-1; i++)
	{
		koniec = true;
		for(int j=0; j<SZ(kr); j++)
		{
			Trzy& akt = kr[j];
			if (D[akt.x] != INF && D[akt.y] > D[akt.x] + akt.z)
			{
				koniec = false;
				D[akt.y] = D[akt.x] + akt.z;
			}
		}
	}
	if (!koniec)
		D.clear();
	return D;
}
------------------------------------------------------------------------
//zwraca pusty vector, gdy jest cykl ujemny
//>INF/2 - nie ma drogi
vector < ll > spfa(int n, int s, vector < vector < pair <int, int> > >& kr)
{
	vector < ll > D(n+1, INF);
	vector < ll > Ile(n+1, 0);
	D[s] = 0;
	queue < int > Q;
	Q.push(s);
	while(!Q.empty())
	{
		int v = Q.front(); 
		if (Ile[v]++ > n)
			return {};
		Q.pop();
		for(auto& el : kr[v])
		{
			if (D[el.ft] > D[v] + el.sd)
			{
				Q.push(el.ft);
				D[el.ft] = D[v] + el.sd;
			}
		}
	}
	return D;
}
