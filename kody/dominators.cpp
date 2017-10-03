struct Dominators{
  int n_orig, n;
  VI parent, semi, vertex, dom, ancestor, label;
  vector<VI> succ, pred, bucket;
  
  Dominators(int _n):n_orig(_n), n(2 * (_n + 1)), parent(n), semi(n), vertex(n), dom(n), ancestor(n), label(n), succ(n), pred(n), bucket(n) {
    n = n_orig;
  }
  
  void add_edge(int a,int b){
    debug(a,b);
    a++;b++;
    succ[a].PB(b);
  }
  
  void COMPRESS(int v) {
    if(ancestor[ancestor[v]] != 0) {
      COMPRESS(ancestor[v]);
      if(semi[label[ancestor[v]]] < semi[label[v]]) {
        label[v] = label[ancestor[v]];
      }
      ancestor[v]=ancestor[ancestor[v]];
    }
  }

  void LINK(int v, int w) {
    ancestor[w]=v;
  }

  int EVAL(int v) {
    if(ancestor[v] == 0)
      return v;
    else {
      COMPRESS(v);
      return label[v];
    }
  }

  void DFS(int v) {
    semi[v] = ++n;
    vertex[n] = v;
    for(auto ng : succ[v]) {
      if(semi[ng] == 0) {
        parent[ng]=v;
        DFS(ng);
      }
      pred[ng].push_back(v);
    }
  }

  vector<int> doit() {
    iota(ALL(label), 0);
    DFS(1);
    for(int i=n; i>=2; --i) {
      int w = vertex[i];
      for(auto ng : pred[w]) {
        int u = EVAL(ng);
        if(semi[u] < semi[w])
          semi[w] = semi[u];
      }
      bucket[vertex[semi[w]]].push_back(w);
      LINK(parent[w],w);
      while(!bucket[parent[w]].empty()) {
        int v = bucket[parent[w]].back();
        bucket[parent[w]].pop_back();
        int u = EVAL(v);
        if(semi[u] < semi[v])
          dom[v] = u;
        else
          dom[v] = parent[w];
      }
    }

    //step 4
    for(int i=2; i<=n; ++i) {
      int w = vertex[i];
      if(dom[w] != vertex[semi[w]])
        dom[w] = dom[dom[w]];
    }
    dom[1]=0;
    vector<int> res(n_orig);
    R(i,n_orig)res[i] = dom[i + 1] - 1;
    return res;
  }
};
