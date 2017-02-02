#define llint long long
#define REP(i, n) rep(i, 0, n)

namespace Mcmf {
  const int MAXV = 1000100;
  const int MAXE = 1000100;
  const llint oo = 1e9;

  int V, E;
  int last[MAXV], how[MAXV]; llint dist[MAXV], pi[MAXV];
  int next[MAXE], from[MAXE], adj[MAXE]; llint cap[MAXE], cost[MAXE];

  struct cmpf {
    bool operator () (int a, int b) {
      if (dist[a] != dist[b]) return dist[a] < dist[b];
      return a < b;
    }
  };
  set<int, cmpf> S;

  void init(int n) {
    V = n;
    E = 0;
    REP(i, V) last[i] = -1;
  }

  void add(int x, int y, llint c, llint w) {
    from[E] = x; adj[E] = y; cap[E] = c; cost[E] = +w; next[E] = last[x]; last[x] = E++;
    from[E] = y; adj[E] = x; cap[E] = 0; cost[E] = -w; next[E] = last[y]; last[y] = E++;
  }

  pair<llint, llint> run(int src, int sink) {
    llint total = 0;
    llint flow = 0;

    REP(i, V) pi[i] = oo;
    pi[src] = 0;

    for (;;) {
      bool done = true;
      REP(x, V) for (int e = last[x]; e != -1; e = next[e])
        if (cap[e] && pi[adj[e]] > pi[x] + cost[e])
          pi[adj[e]] = pi[x] + cost[e], done = false;
      if (done) break;
    }

    for (;;) {
      REP(i, V) dist[i] = oo;
      S.clear();

      dist[src] = 0;
      S.insert(src);

      while (!S.empty()) {
        int x = *S.begin();
        S.erase(S.begin());
        if (x == sink) break;

        for (int e = last[x]; e != -1; e = next[e]) {
          if (cap[e] == 0) continue;

          int y = adj[e];
          llint val = dist[x] + pi[x] + cost[e] - pi[y];

          if (val < dist[y]) {
            S.erase(y);
            dist[y] = val;
            how[y] = e;
            S.insert(y);
          }
        }
      }
      if (dist[sink] >= oo / 2) break;

      llint aug = cap[how[sink]];
      for (int i = sink; i != src; i = from[how[i]])
        aug = min(aug, cap[how[i]]);

      for (int i = sink; i != src; i = from[how[i]]) {
        cap[how[i]] -= aug;
        cap[how[i]^1] += aug;
        total += cost[how[i]] * aug;
      }
      flow += aug;

      REP(i, V) pi[i] = min(pi[i] + dist[i], oo);
    }

    return {total, flow};
  }
} 
