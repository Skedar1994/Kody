#include<bits/stdc++.h>
#define rep(i,k,n) for(ll i= (ll) k;i< (ll) n;i++)
#define all(v) (v).begin(), (v).end()
#define SZ(v) (int)((v).size())
#define pb push_back
#define ft first
#define sd second
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const long long INF = 4e18L + 1;
const int IINF = 2e9 + 1;
const int limit = 1048576;

using namespace std;

//wierzcholki numerujemy od 1
struct LCA
{
	int n, k, czas, pot;
	vector < vector < int > >&V;
	vector < int > cz, pw, pom;
	LCA(int n, int korzen, vector < vector < int > >&V) : n(n), k(korzen), czas(0), V(V), cz(n+1), pw(n+1, 0)
	{
		pot = 1;
		while(pot < 2*n+2) pot *= 2;
		pom.reserve(2*pot);
		pom.resize(pot+1);
		dfs(k);
		for(int i = pot-1; i>0; i--)
			pom[i] = min(pom[2*i], pom[2*i+1]);
		
	}
	void dfs(int v)
	{
		int t = ++czas;
		cz[t] = v;
		pw[v] = pom.size();
		pom.pb(czas);
		for(int i=0; i<SZ(V[v]); i++)
			if (!pw[ V[v][i] ])
			{
				dfs( V[v][i] );
				pom.pb(t);
			}
	}
	int znajdz(int v, int u)
	{
		v = pw[v];
		u = pw[u];
		if (v > u)
			swap(v, u);
		int mini = min(pom[v], pom[u]);
		while(u - v > 1)
		{
			if (v%2 == 0)
				mini = min(mini, pom[v+1]);
			if (u%2 == 1)
				mini = min(mini, pom[u-1]);
			u/=2; v/=2;
		}
		return cz[mini];
	}
};

int main()
{
}
