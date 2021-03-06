//Zlozonosc : V^2E
//Czesto lepsza:
//Jesli ktoras warstwa ma przepustowosc jednostkowa, to zlozonosc to Esqrt(E) (Karzanov)
struct Dinic
{
	struct Edge{
		int v;
		ll cap;
		int rev_ind;
		Edge(int to, ll capa, int ind) : v(to), cap(capa), rev_ind(ind) {}
	};
	int n, source, sink;
	vector < int > starte, d;
	vector < vector<Edge> > nei;

	inline bool bfs()
	{
		d = vector<int>(n + 1, -1);
		d[source] = 0;
		vector<int> q(1,source);
		rep(i, 0, q.size())
		{
			int v = q[i];
			for(auto w: nei[v])
				if(d[w.v] == -1 && w.cap)
				{
					q.pb(w.v);
					d[w.v] = d[v] + 1;
				}
		}
		return d[sink] != -1;
	}
	ll dfs(int v, ll mincap)
	{
		if (!mincap || v == sink) return mincap;
		ll fp=0;
		rep(i, starte[v], nei[v].size())
		{
			if(!mincap)
				break;
			else
				starte[v]=i;
			Edge& edge = nei[v][i];
			int w = nei[v][i].v;
			if(d[w] == d[v] + 1)
			{
				ll f = dfs(w, min(mincap, edge.cap));
				mincap -= f;
				fp += f;
				edge.cap -= f;
				nei[edge.v][edge.rev_ind].cap += f;
				
			} 
		}
		return fp;
	}
	Dinic(int n, int source, int sink) : n(n), source(source), sink(sink), nei(n+1) 
	{	
	}
	ll flow()
	{
		ll maxflow = 0;
		while(bfs())
		{
			starte = vector<int>(n + 1, 0);
			maxflow += dfs(source, INF);
		}
		return maxflow;
	}
	void add_edge(int from, int to, ll capacity, ll cap2 = 0)
	{
		Edge e1(to, capacity, SZ(nei[to])), e2(from, cap2, SZ(nei[from]));
		nei[from].pb(e1);
		nei[to].pb(e2);
	
	}
	vector < int > find_source_cc()
	{
		bfs();
		vector < int > ans;
		for(int i=0; i<=n; i++)
			if (d[i] != -1)
				ans.pb(i);
		return ans;
	}
};

/*
UWAGA nie testowalem czy to ponizej dziala z long longami
dla kazdej krawedzi mozemy ustalic minimalny i maksymalny przeplyw
LRMaxFlow zwroci wielkosc maxflowa dla tych ograniczen albo -1 gdy sie nie da ich spelnic
jesli s = t = -1 to LRMaxFlow sprawdzi, czy istnieje jakis obieg zamkniety spelniajacy dane ograniczenia (-1 jesli sie nie da, cos innego w przeciwnym przypadku)
*/
struct Edge
{
	int a, b;
	ll mini, maxi;
};


ll LRMaxFlow(int n, int s, int t, const vector <Edge>& edges)
{
	for(auto& el : edges)
		if (el.maxi < el.mini)
		{
			return -1;
		}
	int big_source = n+1, big_sink = n+2;
	Dinic dinic(n+2, big_source, big_sink); 
	vector < ll > du(n+3, 0);
	ll sum = 0;
	for(auto& el : edges)
	{
		if (el.mini)
		{
			du[el.a] -= el.mini;
			du[el.b] += el.mini;
		}
		if (el.mini != el.maxi)
			dinic.add_edge(el.a, el.b, el.maxi - el.mini);
	}
	if (s != -1)
		dinic.add_edge(t, s, INF);
	for(int i=1; i<=n+2; i++)
	{
		if (!du[i])
			continue;
		if(du[i] < 0)
			dinic.add_edge(i, n+2, -du[i]);
		else
		{
			dinic.add_edge(n+1, i, du[i]);
			sum += du[i];
		}
	}
	ll flow1 = dinic.flow();
	if (flow1 < sum)
		return -1;
	if (s == -1)
		return sum;	
	dinic.source = s;
	dinic.sink = t;
	ll flow2 = dinic.flow();
	return flow2;
}
