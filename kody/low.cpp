#include <bits/stdc++.h>
#define MAXN 1000005
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1000000007;


vector < vector < int > > V;
vector < int > PA;//punkty artykulacji
vector < pair < int, int > > M;//mosty
int low[MAXN], d[MAXN], nr = 1;

void DFS(int v,	int ojciec)//przy pierwszym odpaleniu ojciec = 0!
{
	int ile=0,pkt_art=false;
	low[v]=d[v]=nr++;
	for(int i=0; i<(int)V[v].size(); i++)
	{
		int sas = V[v][i];
		if (sas != ojciec)
		{
			if (!d[sas])
			{
				DFS(sas,v);
				ile++;
				low[v]=min(low[v],low[sas]);
				if (ojciec && low[sas]>=d[v]) 
					pkt_art=true;
				if (low[sas]>d[v]) 
					M.push_back({v, sas}); // most 
			}
			else 
				low[v]=min(low[v],d[sas]);
		}
	}
	if (!ojciec && ile>1) 
		pkt_art=true;
	if (pkt_art) 
		PA.push_back(v);
}
int main()
{
	ios_base::sync_with_stdio(0);
	int n, m, a, b;
	cin>>n>>m;
	V.resize(n+1);
	while(m--)
	{
		cin>>a>>b;
		V[a].push_back(b);
		V[b].push_back(a);
	}
	DFS(1, 0);
	for(int i=1; i<=n; i++)
		if (!d[i])
		{
			nr = 1;
			DFS(i, 0);
		}
	sort(PA.begin(), PA.end());
	cout << PA.size()<<"\n";
	for(int i=0; i<(int)PA.size(); i++)
		cout<<PA[i]<<" ";
	

	return 0;
}


