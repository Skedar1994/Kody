#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef long long ll;

ld eps = 0.000000001;

struct punkt
{
	int nr;
	ll x, y;
	ld kat;//atan2 zbyt niedokladny, zamineic na iloczyn wektorowy?
	punkt(){}
	punkt(int x, int y, int nr):x(x), y(y), nr(nr){kat = atan2(y, x);}
	bool operator<(punkt p) const{if(kat<p.kat-eps || (abs(kat-p.kat)<eps && abs(x)+abs(y)<abs(p.x)+abs(p.y)))return true; return false;}
	int il_wek(punkt p1, punkt p2){return (p1.x-x)*(p2.y-y) - (p1.y-y)*(p2.x-x);}
	punkt& operator-=(punkt p){x-=p.x;y-=p.y;kat=atan2(x, y); return *this;}
	punkt& operator+=(punkt p){x+=p.x;y+=p.y;kat=atan2(x, y); return *this;}
};

void otoczka(int n, vector < punkt > &V, vector < punkt > &ODP)
{
	punkt przes(1000000005, 1000000005, -1);
	for(int i=0; i<n; i++)
		if (V[i].y < przes.y || (V[i].y == przes.y && V[i].x < przes.x))
			przes = V[i];
	for(int i=0; i<V.size(); i++)
		V[i]-=przes;
	sort(V.begin(), V.end());
	ODP.push_back(punkt(0, 0, przes.nr));
	for(int i=0; i<n; i++)
	{
		if (przes.nr == V[i].nr)
			continue;
		punkt& akt = V[i];
		while(ODP.size() > 1 && ODP[ODP.size()-2].il_wek(ODP.back(), akt) >= 0)
			ODP.pop_back();
		ODP.push_back(akt);
	}
	for(int i=0; i<ODP.size(); i++)
		ODP[i] += przes;
	while(ODP.size() > 2 && ODP[ODP.size()-2].il_wek(ODP.back(), ODP[0]) >= 0)
		ODP.pop_back();
}
int main()
{
	ios_base::sync_with_stdio(0);
	int n;
	cin>>n;
	vector < punkt > V(n), ODP;
	for(int i=0; i<n; i++)
	{
		int x, y;
		cin>>x>>y;
		V[i] = punkt(x, y, i);
	}
	otoczka(n, V, ODP);
	for(int i=0; i<ODP.size(); i++)
		cout<<ODP[i].x<<" "<<ODP[i].y<<"\n";
	cout<<ODP[0].x<<" "<<ODP[0].y<<"\n";
	
	return 0;
}
