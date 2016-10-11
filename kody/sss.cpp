/*
 * 2SAT BEZ TOPOSORTA (tzn da sie zrobic nim TLE)
 * 
 * 
 * 
*/

#include<cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

vector < vector < int > > V, W, Z;//graf skierowany, W - graf odwrocony, Z - spojne skladowe
//w grafie V zmiennej i dpowiadaja indeksy 2*(i-1) oraz 2*i-1 (czyli 1->0, 1 itd.)
int odw[1000005], kol[1000005], ss[1000005], warss[1000005];// w warss sa liczby 1 lub 2; warss[i] = 1 <=> wszystkie indeksy Z[i] sa falszem. 
//numer to w sumie  
int nr = 0;
void dfs(int v)
{
	odw[v] = 1;
	for(int i=0; i<V[v].size(); i++)
		if (!odw[V[v][i]])
			dfs(V[v][i]);
	kol[nr++] =  v;
}
void dfs_odwr(int v)
{
	Z.back().push_back(v);
	ss[v] = Z.size();
	for(int i=0; i<W[v].size(); i++)
		if(!ss[W[v][i]])
			dfs_odwr(W[v][i]);
}

void sss(int n)
{
	for(int i=0; i<n; i++)
		if(!odw[i])
			dfs(i);
	for(int i=n-1; i>=0; i--)
		if(!ss[kol[i]])
		{
			Z.resize(Z.size()+1);
			dfs_odwr(kol[i]);
		}
}

bool dwasat(int n)
{
	sss(n);
	for(int i=Z.size()-1; i>=0; i--)
	{
		if (warss[i+1] == 1)
			continue;
		warss[i+1] = 2;
		for(int j=0; j<Z[i].size(); j++)
		{
			int v = Z[i][j];
			if (warss[ ss[v^1] ] == 2)  
				return false;
			warss[ ss[v^1] ] = 1;
			for(int k=0; k<V[v].size(); k++)
			{
				int sas = V[v][k];
				if (warss[ ss[sas] ] == 1)
					return false;
				warss[ ss[sas] ] = 2;
			}
		}
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin>>n>>m;	
	n*=2;
	V.resize(n+1);
	W.resize(n+1);
	while(m--)
	{
		int a, b, a2, b2;
		cin>>a>>b;
		a--; b--;
		a2 = a^1;
		b2 = b^1;
		V[a].push_back(b2);
		W[b2].push_back(a);
		V[b].push_back(a2);
		W[a2].push_back(b);
	}
	if (!dwasat(n))
	{
		cout<<"NIE";
	}
	else
	{
		vector < int > V;
		for(int i=0; i<Z.size(); i++)
			if (warss[i+1]==2)
				for(int j=0; j<Z[i].size(); j++)
					V.push_back(Z[i][j]+1);
		sort(V.begin(), V.end());
		for(int i=0; i<V.size(); i++)
			cout<<V[i]<<"\n";
	}
	
    

    return 0;
}
