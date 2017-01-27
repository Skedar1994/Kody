struct AhoCorasick{
    static const int CHARSET = 26;
    
    vector<int> tag, fail;
    vector<vector<int> > trie;

    void add_vertex() {
        tag.pb(0); fail.pb(0);
        trie.pb(vector<int>(CHARSET, -1));
    }

    AhoCorasick() {
        add_vertex();
    }

    int size() {
        return trie.size();
    }

    void add(const string& s, int val) {
        int v = 0;
        for(auto c : s) {
            if(trie[v][c - 'a'] == -1) {
                add_vertex();
                trie[v][c - 'a'] = size() - 1;
            }
            v = trie[v][c - 'a'];
        }
        tag[v]+=val;
    }

    void build() {
        vector<int> bfs;
        
        for(auto& w : trie[0]) {
            if(w != -1) {
                bfs.pb(w);
            } else {
                w = 0;
            }
        }
        
        rep(i, 0, bfs.size()) {
            int v = bfs[i];
            tag[v] += tag[fail[v]];
            rep(j, 0, CHARSET) {
                int& w = trie[v][j], u = trie[fail[v]][j];
                if(w != -1) {
                    fail[w] = u;
                    bfs.pb(w);
                } else {
                    w = u;
                }
            }
        }
    }

    int count(const string& s) {
        int v = 0, res = 0;
        for(auto& c : s) {
            v = trie[v][c - 'a'];
            res += tag[v];
        }
        return res;
    }
};

struct dynamicAho{
    vector<vector<string> > inputs;
    vector<AhoCorasick> onlineAho;

    dynamicAho() {
        inputs.resize(20);
        onlineAho.resize(20);
        for(auto& AC : onlineAho) {
            AC.build();
        }
    }

    void add(const string& s) {
        vector<string> added = {s};
        rep(i, 0, 20) {
            auto& v = inputs[i];
            if(v.size()) {
                added.insert(added.end(), v.begin(), v.end());
                v.clear();
                onlineAho[i] = AhoCorasick();
                onlineAho[i].build();
            } else {
                v = added;
                onlineAho[i] = AhoCorasick();
                for(auto& str : v) {
                    onlineAho[i].add(str, 1);
                }
                onlineAho[i].build();
                break;
            }
        }
    }

    int query(const string& s) {
        int res = 0;
        for(auto& AC : onlineAho) {
            res += AC.count(s);
        }
        return res;
    }
};


//pewnie szybsze ale gunwo troche
namespace AhoCorasick{
    const int MAX_SZ = 1e6, CHARSET = 26;
    int trie[MAX_SZ + 10][CHARSET], tag[MAX_SZ + 10], fail[MAX_SZ + 10], bfs[MAX_SZ + 10];
    int sz = 1;

    void init(){ 
        rep(i, 1, MAX_SZ + 10){
            fail[i] = 1;
        }
    }

    void add(const string& s, int val) {
        int v = 1;
        for(auto& c : s) {
            if(trie[v][c - 'a'] == 0) {
                trie[v][c - 'a'] = ++sz;
            }
            v = trie[v][c - 'a'];
        }
        tag[v] += val;
    }

    void build() {
        int bfs_sz = 1;
        for(auto& w : trie[1]) {
            if(w != 0) {
                bfs[bfs_sz++] = w;
            } else {
                w = 1;
            }
        }
        
        rep(i, 0, bfs_sz) {
            int v = bfs[i];
            tag[v] += tag[fail[v]];
            rep(j, 0, CHARSET) {
                if(trie[v][j] != 0) {
                    fail[trie[v][j]] = trie[fail[v]][j];
                    bfs[bfs_sz++] = trie[v][j];
                } else {
                    trie[v][j] = trie[fail[v]][j];
                }
            }
        }
    }

    int count(const string& s){
        int v = 0, res = 0;
        for(auto& c : s){
            v = trie[v][c - 'a'];
            res += tag[v];
        }
        return res;
    }
};
