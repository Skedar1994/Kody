#include<bits/stdc++.h>
#define rep(i,k,n) for(int i= (int) k;i< (int) n;i++)
#define all(v) (v).begin(), (v).end()
#define pb push_back
#define ft first
#define sd second
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;
const long long INF = 4e18L + 1;
const int IINF = 2e9 + 1;
const int limit = 1048576;
using namespace std;

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
            int& w = trie[v][c - 'a'];
            if(w == -1) {
                add_vertex();
                w = size() - 1;
            }
            v = w;
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

int main()
{
    //     cin.tie(0);
    ios_base::sync_with_stdio(0);
    return 0;
}
