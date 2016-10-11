#include<bits/stdc++.h>
#define rep(i,k,n) for(int i= (int) k;i< (int) n;i++)
#define pb push_back
typedef long long ll;
const long long inf = 8223372036854775807ll;
using namespace std;

int source, sink, n;
vector<int> starte, d;
vector<vector<ll> > cap;
vector<vector<int> > nei;

inline bool bfs()
{
    d = vector<int>(n + 1, -1);
    d[source] = 0;
    vector<int> q = {source};
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
      starte[v]++;
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

ll dinic()
{
    ll maxflow = 0;
    while(bfs())
    {
        starte = vector<int>(n + 1, 0);
        maxflow += dfs(source, inf);
    }
    return maxflow;
}

int main()
{
  return 0;
}
