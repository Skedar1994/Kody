#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct wezel
{
	ll war;
	ll mod;
};
struct drzewoprzedzialowe //max
{
	wezel* drzewo; int pot;
	drzewoprzedzialowe(int rozmiar)
	{
		pot = 1; while(pot <= rozmiar) pot <<= 1;
		drzewo = new wezel[2*pot];
		memset(drzewo, 0, 2*rozmiar*(sizeof (wezel))); 
	}
	~drzewoprzedzialowe(){delete[] drzewo;}
	void dodaj(int p, int k, int war)
	{
		p += pot; k += pot;
		drzewo[p].war += war;
		if (p != k)
			drzewo[k].war += war;
		while(p/2 != k/2)
		{
			if (p%2 == 0)
				drzewo[p+1].mod += war, drzewo[p+1].war += war;
			if (k%2==1)
				drzewo[k-1].mod += war, drzewo[k-1].war += war;
			k/=2; p/=2;
			drzewo[p].war = max(drzewo[2*p].war, drzewo[2*p+1].war) + drzewo[p].mod;
			drzewo[k].war = max(drzewo[2*k].war, drzewo[2*k+1].war) + drzewo[k].mod;
		}
		while(p > 1)
		{
			p/=2;
			drzewo[p].war = max(drzewo[2*p].war, drzewo[2*p+1].war) + drzewo[p].mod;
		}
	}
	ll maks(int p, int k)
	{
		p += pot; k += pot;
		ll wynp = drzewo[p].war, wynk = drzewo[k].war;
		while(p/2 != k/2)
		{
			if (p%2 == 0)
				wynp = max(wynp, drzewo[p+1].war);
			if (k%2==1)
				wynk = max(wynk, drzewo[k-1].war);
			k/=2; p/=2;
			wynp+=drzewo[p].mod; wynk+=drzewo[k].mod;			
		}
		wynp = max(wynp, wynk);
		while(p > 1)
		{
			p/=2;
			wynp+=drzewo[p].mod;
		}
		return wynp;
	}
	/*void wypisz()
	{
		int pom = 1;
		while(pom <= pot)
		{
			for(int i=pom; i<2*pom; i++)
				cout<<"("<<drzewo[i].war<<", "<<drzewo[i].mod<<") ";
			cout<<endl;
			pom *= 2;
		}
	}*/
};

int main()
{
	ios_base::sync_with_stdio(0); cin.tie(0);
	int n;
	drzewoprzedzialowe d(1000000);
	cin>>n;
	while(n--)
	{
		int a, b, c;
		cin>>a;
		if (a)
		{
			cin>>b>>c;
			d.dodaj(b, c, 1 - 2*(a/2));
		}
		else
			cout<<d.maks(1, 1000000)<<"\n";
//		d.wypisz();
	}
	getchar();
}
