#include<bits/stdc++.h>
#define rep(i,k,n) for(ll i= (ll) k;i< (ll) n;i++)
#define all(v) (v).begin(), (v).end()
#define SZ(v) (int)((v).size())
#define pb push_back
#define ft first
#define sd second
typedef long long ll;
typedef unsigned long long ull;
typedef long long ld;
const long long INF = 4e18L + 1;
const int IINF = 2e9 + 1;
const int limit = 1048576;

using namespace std;


#define LOCAL
#ifndef LOCAL
#define cerr if(0)cout
#define endl "\n"
#endif

ll pot(ll a, ll b, ll mod)
{
	if (b == 0) return 1;
	return pot(a*a%mod, b/2, mod) * ( (b&1) ? a : 1ll) % mod;
}

ll odwr(ll a, ll mod)
{
	return pot(a, mod-2, mod);
}

ll log_dys(ll a, ll b, ll mod)
{
	a%=mod; b%=mod;
	if (a == 0)
	{
		if (b==0)
			return 1;
		return -1;
	}
	if (b == 1) return 0;
	ll pier = floor(sqrt(mod)) + 1;
	vector < ll > B(pier+1, 0), G(pier+1, 0);
	map < ll, ll > M;
	M[1] = 0, B[0] = 1, G[0] = 1;
	for(int i=1; i<=pier; i++)
	{
		B[i] = B[i-1]*a % mod;
		M[B[i]] = i;
		if (B[i] == b)
			return i;
	}
	for(int i=1; i<=pier; i++)
	{
		G[i] = G[i-1] * B[pier]%mod;
		ll pom = b * odwr(G[i], mod) % mod;
		if (M.find(pom)!= M.end())
			return M[pom] + i * pier;
	}
	return -1;
}


int main()
{
	ll a, b, n;
	cin>>a>>b>>n;
	cout << log_dys(a, b, n);
	return 0;
}
