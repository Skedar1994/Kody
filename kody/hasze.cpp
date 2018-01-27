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


//zmien litere, spytaj o hasz
int VPOT[4] = {257, 293, 307, 313};
ll pr = -1;

struct HD
{
	const ll MOD = 1e9+7;
	int pot = (1<<17);
	vector < ll > tab;
	vector < ll > P;
	HD(int roz) : MOD(1e9+7)
	{
		pot = 1;
		while(pot <= roz+2) pot *= 2;
		tab.resize(2*pot);
		P.resize(pot+1);
		P[0] = 1;
		srand((ll)(new int));
		if (pr == -1) pr = VPOT[rand() % 4];
		for(int i=1; i<SZ(P); i++) P[i] = P[i-1] * pr % MOD;
	}
	void ustaw(int gdzie, char co)
	{
		int aa = co - 'a'+1;
		gdzie += pot;
		tab[gdzie] = aa;
		int wyk = 1;
		
		while(gdzie > 1)
		{
			gdzie/=2;
			tab[gdzie] = (tab[2*gdzie]*P[wyk] + tab[2*gdzie+1]) % MOD;
			wyk *= 2;
		}
	}

	ll wez(int l, int p)
	{
		l += pot, p += pot;
		if (l == p)
			return tab[l];
		
		ll lh = tab[l]%MOD, ph = tab[p];
		ll da = 1;//dl akt
		ll dp = 1;//dl prawego
		while(l+1<p)
		{
			if (l%2 == 0)
			{
				lh = (lh * P[da] + tab[l+1])%MOD;
			}
			if (p%2==1)
			{
				ph = (tab[p-1]*P[dp] + ph)%MOD;
				dp += da;
			}
			l/=2; p/=2;
			da *= 2;
		}
		return (lh * P[dp] + ph)%MOD;
	}
};

