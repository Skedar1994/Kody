struct Dinic
{
	int n, source, sink;
	vector < int > starte, d;
	vector < vector<ll> > cap;
	vector < vector<int> > nei;

	inline bool bfs()
	{
		d = vector<int>(n + 1, -1);
		d[source] = 0;
		vector<int> q(1,source);
		rep(i, 0, q.size())
		{
			int v = q[i];
			for(auto w: nei[v])
				if(d[w] == -1 && cap[v][w])
				{
					q.pb(w);
					d[w] = d[v] + 1;
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
			int w = nei[v][i];
			if(d[w] == d[v] + 1)
			{
				ll f = dfs(w, min(mincap, cap[v][w]));
				mincap -= f;
				fp += f;
				cap[v][w] -= f;
				cap[w][v] += f;
			} 
		}
		return fp;
	}
	Dinic(int n, int source, int sink) : n(n), source(source), sink(sink), cap(n+1, vector < ll >(n+1, 0)), nei(n+1) 
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
		nei[from].pb(to);
		nei[to].pb(from);
		cap[from][to] += capacity;
		cap[to][from] += cap2;
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
