#include <iostream>
#include <vector>

using namespace std;

vector < int > O, S; //O - odpowiedz, S - stos
vector < vector < pair <int,int > > > V;
int odw[1000005];
int main()
{
	int n, m, a, b;
	cin>>n>>m;
	V.resize(n+5);
	for(int i=0; i<m; i++)
	{
		cin>>a>>b;
		V[a].push_back(make_pair(b, i));
		V[b].push_back(make_pair(a, i));
	}
	S.push_back(1);
	while(S.size()>0)
	{
		int akt = S[S.size()-1];
		while(V[akt].size() && odw[V[akt][V[akt].size()-1].second]==1)
			V[akt].pop_back();
		if (V[akt].size() == 0)
		{
			S.pop_back();
			O.push_back(akt);
		}
		else
		{
			odw[V[akt][V[akt].size()-1].second]=1;
			S.push_back(V[akt][V[akt].size()-1].first);
		}
	}
	for(int i=0; i<(int)O.size(); i++)
		cout<<O[i]<<" ";
	return 0;
}
