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

struct LCA
{
	int** ANC;
	int* wys;
	int n, korzen, logn;
	vector < vector < int > > V;
	LCA(int n, int korzen, vector < vector < int > > &V) : n(n), korzen(korzen), V(V)
	{
		V.resize(n+1);
		ANC = new int*[n+1];
		wys = new int[n+1];
		logn = 34 -__builtin_clz(n);
		for(int i=0; i<=n; i++)
				ANC[i] = new int[logn];
		oblicz_ANC();
	}
	void oblicz_ANC()
	{
		wys[korzen]=-1;
		dfs(korzen, korzen);
		for(int i=1; i<logn; i++)
			for(int j=1; j<=n; j++)
				ANC[j][i] = ANC[ ANC[j][i-1] ][i-1];
	}
	void dfs(int v, int ojciec)
	{
		wys[v] = 1 + wys[ojciec];
		ANC[v][0] = ojciec;
		for(auto sas : V[v])
			if (sas != ojciec)
				dfs(sas, v);
	}
	int znajdz(int v, int w)
	{
		if (wys[v] > wys[w]) 
			swap(v, w);
		for(int i = logn-1; i>=0; i--)
			if (wys[w] - (1<<i) >= wys[v])
				w = ANC[w][i];
		for(int i = logn-1; i>=0; i--)
			if (ANC[w][i] != ANC[v][i])
				w = ANC[w][i], v = ANC[v][i];
		return w == v ? w : ANC[w][0];
	}
};

int main()
{
}
