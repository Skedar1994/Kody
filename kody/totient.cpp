
#define MAX 10000000

ll phi[MAX];
bool pr[MAX];

void totient(){
  for(int i = 0; i < MAX; i++){
    phi[i] = i;
    pr[i] = true;
  }
  for(int i = 2; i < MAX; i++)
    if(pr[i]){
      for(int j = i; j < MAX; j+=i){
        pr[j] = false;
        phi[j] = phi[j] - (phi[j] / i);
      }
      pr[i] = true;
    }
}
/*
To ponizej sluzy do liczenia sum phi(1) * 1^k + phi(2) * 2^k + .. + phi(n) * n^k 
w zlozonisci O(k*n^(2/3)) (być może z logiem z mapy jeszcze)
Jak sam totient function chcemy to nie przepisujemy tego ponizej
UWAGI: 
ustaw MAX na 10^6
zeby policzyc sumę dla danego k to funkcja Suma_poteg musi miec rozpisane case'y do k+1
*/
const ll MOD = 1e9+7;
struct Tot_pref_sum
{
	int pot;
	vector < ll > V, S;
	map < int, ll > pamiec;
	Tot_pref_sum(int _pot) : pot(_pot), V(MAX, 0), S(MAX, 0)
	{
		if (phi[2] == 0)
			totient();
		for(ll i=1; i<MAX; i++)
		{
			S[i] = 1;
			for(int j=0; j<pot; j++)
				S[i] = S[i] * i % MOD;
			V[i] = (S[i]*phi[i] + V[i-1]) % MOD;
		}
	}
	ll Suma_poteg(ll ile, int ktora = -1)//suma 1^pot + 2^pot + .. + ile^pot
	{
		if (ktora == -1)
			ktora = pot;
		ll wyn;
		switch(ktora)
		{
		case 0:
			return ile;
		case 1:
			wyn = ile * (ile+1) % MOD;
			wyn = wyn * 500000004ll % MOD; //2^-1
			return wyn;
		case 2:
			wyn = ile * (ile+1) % MOD;
			wyn = wyn * (2*ile+1) % MOD;
			wyn = wyn * 166666668ll % MOD;  //6^-1
			return wyn;
		case 3:
			wyn = ile * (ile+1) % MOD;
			wyn = wyn * wyn % MOD;
			wyn = wyn * 250000002ll % MOD; //4^-1
			return wyn;
		default:
			assert(false);
		}
		return wyn;
	}
	ll licz(int n)
	{
		if (n < MAX)
			return V[n];
		if (pamiec.find(n) != pamiec.end())
			return pamiec[n];
		int q = sqrt(n);
		ll wyn = Suma_poteg(n, pot+1);
		for(int i=2; i<=n/q; i++)
		{
			ll pom = licz(n/i);
			wyn -= pom * Suma_poteg(i);
			wyn += pom * Suma_poteg(i-1);
			wyn %= MOD;
		}
		for(int i=1; i<q; i++)
		{
			ll pom = licz(i);
			wyn -= Suma_poteg(n/i) * pom;
			wyn += Suma_poteg(n/(i+1)) * pom;
			wyn %= MOD;
		}
		if (wyn < 0)
			wyn += MOD;
		pamiec[n] = wyn;
		return wyn;
	}
};
