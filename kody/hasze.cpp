/*
na poczatku int main napisac Hasz::init(MAXN);
potem Hasz hasz(string s)
i pytajac hasz.haszuj(int pocz, int kon) dostajemy {s[kon]*P^0 + s[kon-1]*P^1 + ... + s[pocz]*P^(kon-pocz), s[kon]*Q^0...}
indeksowanie od 0, haszowanie dwoma liczbami pierwszymi
*/
struct Hasz
{
	const static ll p = 263, q = 269, mod = 1e9+7;
	vector < ll > Phasz, Qhasz; 
	static vector < ll > P, Q;
	static void init(int maxn)
	{
		P.resize(maxn+1), Q.resize(maxn+1);
		P[0] = Q[0] = 1;
		for(int i=1; i<=maxn; i++)
		{
			P[i] = P[i-1] * p % mod;
			Q[i] = Q[i-1] * q % mod;
		}
	}
	Hasz(const string& s)
	{
		Phasz.resize(SZ(s)+1);
		Qhasz.resize(SZ(s)+1);
		for(int i=1; i<=SZ(s); i++)
		{
			Phasz[i] = (Phasz[i-1]*p + s[i-1]) % mod;
			Qhasz[i] = (Qhasz[i-1]*q + s[i-1]) % mod;
		}
	}
	pair < ll, ll > haszuj(int pocz, int kon)
	{
		ll wynP = (Phasz[kon+1] - Phasz[pocz]*P[kon - pocz + 1]) % mod;
		if (wynP < 0)
			wynP+= mod;
		ll wynQ = (Qhasz[kon+1] - Qhasz[pocz]*Q[kon - pocz + 1]) % mod;
		if (wynQ < 0)
			wynQ+= mod;
		return make_pair(wynP, wynQ);
	}
};
vector < ll > Hasz::P, Hasz::Q;
