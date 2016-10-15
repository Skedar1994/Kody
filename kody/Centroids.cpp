struct Centroids {
    
    int n; // indeksowanie od 1
    vector<vector<int>>& v;
    
    vector<int> parent;
    vector<vector<int>> children; 
    vector<int> h;
    int root;
    
    vector<int> odw, w;
    
    Centroids (vector<vector<int>>& v) : v(v) {
        n = v.size();
        parent.resize(n + 1);
        children.resize(n + 1);
        h.resize(n + 1, -1);
        odw.resize(n + 1);
        w.resize(n + 1);
        root = makeCentroid(1, 0, 0);
        
    }
    
    int makeCentroid(int x, int hei, int p) {
        int centroid = findCentroid(x);
        h[centroid] = hei;
        parent[centroid] = p;
        children[p].pb(centroid);
        for (auto y: v[centroid]) if (h[y] == -1){
            makeCentroid(y, hei + 1, centroid);
        }
        return centroid;
    }
        
    int findCentroid (int pocz) {
        vector<int> garbage;
        int sum = dfs1(pocz, garbage);
        for (auto x: garbage) odw[x] = 0;
        garbage.clear();
        int centroid = dfs2(pocz, sum, garbage);
        for (auto x: garbage) odw[x] = 0;
        garbage.clear();
        return centroid;
    }
    
    int dfs1 (int x, vector<int>& garbage) {
        odw[x] = 1;
        garbage.pb(x);
        int s = 1;
        for (auto y: v[x]) if (!odw[y] and h[y] == -1) {
            s += dfs1(y, garbage);
        }
        w[x] = s;
        return s;
    }
    
    int dfs2 (int x, int sum, vector<int>& garbage) {
        odw[x] = 1;
        garbage.pb(x);
        for (auto y: v[x]) if (!odw[y] and h[y] == -1 and w[y] > sum / 2) {
            return dfs2(y, sum, garbage);
        }
        return x;
    }
};
