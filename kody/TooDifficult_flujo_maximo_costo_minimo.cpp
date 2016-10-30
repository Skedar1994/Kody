#include<bits/stdc++.h>
#define rep(i,a,n) for (int i=a;i<n;i++)

using namespace std;

//na poczatku uzywamy funkcji init - zrodlo, ujscie, liczba wierzcholkow
//potem dodajemy krawedzie funkcja add
//na koniec wywolujemy solve()
//odpowiedz jest w zmiennych flow, cost
//numeracja od 0
//dziala z ujemnymi
namespace mincost {
	const int V=510,E=51000,inf=0x20202020;
	int dis[V],q[V*300],vis[V],fst[V],pre[V],nxt[E],y[E],f[E],c[E],S,T,flow,cost,tot,tn;
	void init(int s,int t,int Tn) {
		tot=1; tn=Tn;
		rep(i,0,tn) fst[i]=0;
		S=s;T=t;
	}
	void add(int u,int v,int ff,int cc) {
		tot++;y[tot]=v;nxt[tot]=fst[u];f[tot]=ff;c[tot]=cc;fst[u]=tot;
		tot++;y[tot]=u;nxt[tot]=fst[v];f[tot]=0;c[tot]=-cc;fst[v]=tot;
	}
	bool spfa() {
		rep(i,0,tn) dis[i]=inf,vis[i]=0,pre[i]=0;
		dis[S]=0;q[0]=S;vis[S]=1;
		int t=1;
		rep(i,0,t) {
			int u=q[i];
			for (int j=fst[u];j;j=nxt[j]) {
				int v=y[j];
				if (f[j]&&dis[v]>dis[u]+c[j]) {
					dis[v]=dis[u]+c[j];
					pre[v]=j;
					if (!vis[v]) vis[v]=1,q[t++]=v;
				}
			}
			vis[u]=0;
		}
		return dis[T]!=inf;
	}
	void augment() {
		int p=T,_f=inf;
		while (pre[p]) _f=min(_f,f[pre[p]]),p=y[pre[p]^1];
		flow+=_f;cost+=_f*dis[T];
		p=T;
		while (pre[p]) f[pre[p]]-=_f,f[pre[p]^1]+=_f,p=y[pre[p]^1];
	}
	void solve() {
		flow=0,cost=0;
		while (spfa()) augment();
	}
}

int main() {
}
