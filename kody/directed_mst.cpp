// Directed minimum spanning tree
//
// Given a directed weighted graph and root node, computes the minimum spanning
// directed tree (arborescence) on it.
//
// Complexity: O(N * M), where N is the number of nodes, and M the number of edges
struct Edge { ll x, y, w; };

ll dmst(ll N, vector<Edge> E, ll root) {
  const ll oo = 1e18;

  vector<ll> cost(N), back(N), label(N), bio(N);
  ll ret = 0;

  for (;;) {
    rep(i, 0, N) cost[i] = oo;
    for (auto e : E) {
      if (e.x == e.y) continue;
      if (e.w < cost[e.y]) cost[e.y] = e.w, back[e.y] = e.x;
    }
    cost[root] = 0;
    rep(i, 0, N) if (cost[i] == oo) return -1;
    rep(i, 0, N) ret += cost[i];

    ll K = 0;
    rep(i, 0, N) label[i] = -1;
    rep(i, 0, N) bio[i] = -1;

    rep(i, 0, N) {
      ll x = i;
      for (; x != root && bio[x] == -1; x = back[x]) bio[x] = i;

      if (x != root && bio[x] == i) {
        for (; label[x] == -1; x = back[x]) label[x] = K;
        ++K;
      }
    }
    if (K == 0) break;

    rep(i, 0, N) if (label[i] == -1) label[i] = K++;

    for (auto &e : E) {
      ll xx = label[e.x];
      ll yy = label[e.y];
      if (xx != yy) e.w -= cost[e.y];
      e.x = xx;
      e.y = yy;
    }

    root = label[root];
    N = K;
  }

  return ret;
}
