/*
na poczatku int main napisac Hasz::init(MAXN);
potem Hasz hasz(string s)
i pytajac hasz.haszuj(int pocz, int kon) dostajemy {s[pocz]*P^0 + s[pocz+1]*P^1 + ... + s[kon]*P^(kon-pocz), s[pocz]*Q^0...}
indeksowanie od 0, haszowanie dwoma liczbami pierwszymi
*/
vector < ll > P, P_odwr, Q, Q_odwr;
struct Hasz
{
	const static ll p = 263, p_odwr = 836501907, q = 269, q_odwr = 743494429, mod = 1e9+7;
	vector < ll > Phasz, Qhasz; 
	static void uzupelnij_vec(vector < ll >& V, int n, ll pod)
	{
		V.resize(n+1);
		V[0] = 1;
		for(int i=1; i<=n; i++)
			V[i] = V[i-1]*pod%mod;
	}
	static void init(int maxn)
	{
		uzupelnij_vec(P, maxn, p);
		uzupelnij_vec(Q, maxn, q);
		uzupelnij_vec(P_odwr, maxn, p_odwr);
		uzupelnij_vec(Q_odwr, maxn, q_odwr);
	}
	Hasz(const string& s)
	{
		Phasz.resize(SZ(s)+1);
		Qhasz.resize(SZ(s)+1);
		for(int i=1; i<=SZ(s); i++)
		{
			Phasz[i] = (Phasz[i-1] + P[i-1]*s[i-1]) % mod;
			Qhasz[i] = (Qhasz[i-1] + Q[i-1]*s[i-1]) % mod;
		}
	}
	pair < ll, ll > haszuj(int pocz, int kon)
	{
		ll wynP = (Phasz[kon+1] - Phasz[pocz]) * P_odwr[pocz] % mod;
		if (wynP < 0)
			wynP+= mod;
		ll wynQ = (Qhasz[kon+1] - Qhasz[pocz]) * Q_odwr[pocz] % mod;
		if (wynQ < 0)
			wynQ+= mod;
		return make_pair(wynP, wynQ);
	}
};
