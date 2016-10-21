//znaleziona w kodach UJ na CF-ie
//dziala dla ujemnych

#include <bits/stdc++.h>

#define FOR(i,b,e) for(int i=(b); i <= (e); ++i)
#define FORD(i,b,e) for(int i=(b); i >= (e); --i)
#define SIZE(c) (int) (c).size()
#define FORE(i,c) FOR(i,0,SIZE(c)-1)
#define FORDE(i,c) FORD(i,SIZE(c)-1,0)
#define PB push_back
#define MP make_pair
#define ST first
#define ND second

using namespace std;

typedef long long int LLI;
typedef pair < int , int > PII;
typedef pair < LLI , LLI > PLL;

typedef vector < int > VI;
typedef vector < bool > VB;
typedef vector < PII > VP;
typedef vector < LLI > VL;
typedef vector < PLL > VPL;

typedef vector < VI > VVI;
typedef vector < VL > VVL;
typedef vector < VB > VVB;
typedef vector < VP > VVP;

const int MOD = 1000000007;
const int INF = 1000000001;
const LLI LLINF = 1000000000000000001LL;

/*************************************************************************/

struct MaxCostCirculation {
    struct edge {
        int u, v, flow, cap, cost, rev;
        bool residual() { return flow < cap; }
    };

    int n;
    vector < vector<edge> > G;

    MaxCostCirculation(int n): n(n), G(n) {}

    void addEdge(int u, int v, int cap, int cost) {
        G[u].PB({u,v,0,cap,cost,SIZE(G[v])});
        G[v].PB({v,u,0,0,-cost,SIZE(G[u])-1});
    }

    vector <edge*> findCycle() {
        vector <edge*> from(n);
        VI dist(n,0);

        FOR(_,1,n-1) FOR(u,0,n-1) FORE(j,G[u]) {
            edge *e = &G[u][j];

            if (e->residual() && dist[e->v] < dist[u] + e->cost) {
                dist[e->v] = dist[u] + e->cost;
                from[e->v] = e;
            }
        }

        FOR(u,0,n-1) FORE(j,G[u]) {
            edge *e = &G[u][j];

            if (e->residual() && dist[e->v] < dist[u] + e->cost) {
                vector <edge*> path;

                while (find(path.begin(), path.end(), e) == path.end()) {
                    path.PB(e);
                    e = from[e->u];
                }

                path.erase(path.begin(), find(path.begin(), path.end(), e));
                return path;
            }
        }

        return vector <edge*> ();
    }

    int getCirculation() {
        int ans = 0;

        while (true) {
            vector <edge*> path = findCycle();
            if (path.empty()) break;

            int flow = INF;
            int cost = 0;

            for (edge *e : path) {
                flow = min(flow, e->cap - e->flow);
                cost += e->cost;
            }

            ans += flow * cost;

            for (edge *e : path) {
                e->flow += flow;
                G[e->v][e->rev].flow -= flow;
            }
        }

        return ans;
    }
};

/*************************************************************************/

int main() {
    ios_base::sync_with_stdio(0);
    freopen("arbitrage.in", "r", stdin);
    freopen("arbitrage.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    MaxCostCirculation graph(n);

    while (m--) {
        int u, v, cost, cap;
        cin >> u >> v >> cost >> cap; u--; v--;

        graph.addEdge(u, v, cap, cost);
    }

    cout << graph.getCirculation();

    return 0;
}

/*************************************************************************/
