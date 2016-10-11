#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = (int) j; i < (int) k; i++)
#define pb push_back
#define all(v) v.begin(), v.end()
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1000000007;


struct AB {
    vector<vector<int> >nei;
    vector<int> AP;
    vector<pair<int, int> > B;
    vector<int> low, d;
    int n, nr;

    void DFS(int v, int parent) {
        int cnt = 0;
        low[v] = d[v] = nr++;
        bool art_pt = false, seen_parent = false;
        for(auto w : nei[v]) {
            if(w != parent or seen_parent) {
                if(!d[w]) {
                    DFS(w, v);
                    cnt++;
                    low[v] = min(low[v], low[w]);
                    if(parent and low[w] >= d[v]) {
                        art_pt = true;
                    }
                    if(low[w] > d[v]) {
                        B.pb({v, w});
                        B.pb({w, v});
                    }
                } else {
                    low[v] = min(low[v], d[w]);
                }
            } else {
                seen_parent = true;
            }
        }
        if(!parent and cnt > 1) {
            art_pt = true;
        }
        if(art_pt) {
            AP.pb(v);
        }
    }

    AB(vector<vector<int> > ini_nei, int ini_n)
        :nei{ini_nei}, n(ini_n) {
            low.resize(n + 1); d.resize(n + 1, 0);
            rep(i, 1, n + 1) {
                if(!d[i]) {
                    nr = 1;
                    DFS(i, 0);
                }
            }
            sort(all(AP));
        }
};
