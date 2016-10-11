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

struct SSS
{	//numerujemy wierzcholki od 0 !!!
	vector < vector < int > >& V, W, SS, GSS;//W to bedzie graf odwrocony, SS - vector spojnych skladowych
	vector < int > odw, kol, ss_ind;	//ss[i] - indeks spojnej skladowej, w ktorej jest i-ty wierzcholek
	int nr;
	SSS(int n, vector < vector < int > >& V) : V(V), W(V.size()), odw(n), kol(n), ss_ind(n, -1), nr(0) 
	{
		for(int i=0; i<n; i++)
			for(auto el : V[i])
				W[el].pb(i);	
		for(int i=0; i<n; i++)
			if(!odw[i])
				dfs(i);
		for(int i=n-1; i>=0; i--)
			if(-1 != ss_ind[kol[i]])
			{
				SS.resize(SS.size()+1);
				dfs_odwr(kol[i]);
			}
		GSS.resize(SS.size());
		for(int i=0; i<n; i++)
			for(auto el : V[i])
				GSS[ss_ind[i]].pb(ss_ind[el]);
		for(auto& el : GSS)
		{
			sort(el.begin(), el.end());
			el.resize(distance(el.begin(), unique(all(el))));
		}
	}
	void dfs(int v)
	{
		odw[v] = 1;
		for(int i=0; i<SZ(V[v]); i++)
			if (!odw[V[v][i]])
				dfs(V[v][i]);
		kol[nr++] =  v;
	}
	void dfs_odwr(int v)
	{
		SS.back().push_back(v);
		ss_ind[v] = SS.size() - 1;
		for(int i=0; i<SZ(W[v]); i++)
			if(-1 != ss_ind[W[v][i]])
				dfs_odwr(W[v][i]);
	}
};


struct DWASAT
{
	int n;
	vector < int > Para; // Para[i] = k to nr zmiennej, ktora jest zaprzeczeniem i. Para[j] = i
	vector < vector < int > > V;
	vector < int > Wss, Wel;
	SSS* sss;
	DWASAT(int n, vector < int > P) : n(n), Para(P), V(2*n), Wss(n, 0), Wel(n, 0) {}
	void dodaj(int a, int b) //byc moze trzeba dodac zaprzeczenie? (Para[i])
	{
		V[ Para[a] ].pb(b);
		V[ Para[b] ].pb(a);
	}
	bool rob()
	{
		sss = new SSS(n, V);
		//jesli chcemy tylko wiedziec, czy sie da, to wystarczy sprawdzic, czy dla kazdej zmiennej on i para sa w innych sss.s
		vector < int > kol = toposort(n, sss->GSS);
		for(int i = SZ(kol)-1; i>=0; i--)
			if (!Wss[kol[i]])
			{
				Wss[kol[i]] = 1;
				for(auto& el : sss->SS[i])
				{
					Wel[el] = 1;
					int zaprz = Para[i];
					if (Wel[zaprz] == 1)
						return false;
					Wel[zaprz] = 1;
					Wss[sss->ss_ind[zaprz]] = -1;
				}
			}
		return true;
	}
	vector < int > toposort(int n, vector < vector < int > >& G)//grafu sa na koncu
	{
		queue < int > Q;
		vector < int > st(n, 0), odp;
		for(auto& el : G)
			for(int j=0; j<SZ(el); j++)
				st[j]++;
		for(int i=0; i<n; i++)
			if (st[i] == 0)
				Q.push(i);
		while(!Q.empty())
		{
			odp.pb(Q.front());
			for(auto& el : G[Q.front()])
			{
				st[el]--;
				if (!st[el]) 
					Q.push(el);
			}
			Q.pop();
		}
		return odp;
	}
};


bool przecinaja(int a, int b, int c, int d)
{
	if (a > b)
		swap(a, b);
	
	bool b1 = ( (d < b) && (d > a) );
	bool b2 = ( (d < c) && (c > a) );
	return b1 ^ b2;
}

int main()
{
	// ios_base::sync_with_stdio(0);
	// cin.tie(0);
	int n, m;
	cin>>n>>m;
	
	vector < int > P(2*m, 0);
	vector < pair < int, int > > V;
	for(int i=0; i<m; i++)
		P[i] = i+m, P[i+n] = i;
		
	DWASAT dwasat(2*m, P);
	while(m--)
	{
		int a, b;
		cin>>a>>b;
		V.pb({a, b});
	}
	
	for(int i=0; i<m; i++)
	{
		for(int j=i+1; j<m; j++)
		{
			if (przecinaja(V[i].ft, V[i].sd, V[j].ft, V[j].sd))
			{
				dwasat.dodaj(i, P[j]);
				dwasat.dodaj(P[i], j);
			}
		}
	}
	bool odp = dwasat.rob();
	if (odp)
	{
		for(auto el : dwasat.Wel)
		{
			if (el == 1)
				cout << "i";
			else
				cout << "o";
		}	
	}
	else
		cout << "Impossible";
	
	return 0;
}
