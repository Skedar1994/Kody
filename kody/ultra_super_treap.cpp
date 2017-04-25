//pozwala na odwracanie kolejnosci w przedziale oraz na zapytanie na przedziale jak w drzewie przedzialowym
#define T int
const int N = 3e5+5;
//UWAGA USTAWIC TO WYZEJ

struct node {
	T val;
	pair < T, T > mini;
	int lazy;
	int prior, size;
	node *l, *r;
	node():mini(0, 0){}
};
node _arr[2 * N];
int ctr;
 
int fac[N+1], inv[N+1], ifac[N+1];
 
struct implicit_treap {
	node * root;
	implicit_treap() : root(0) {}
 
	int size(node * t) {
		return t ? t->size : 0;
	}
	void upd_size(node * t) {
		if (t)t->size = size(t->l) + 1 + size(t->r);
	}
 
	void lazy(node * t) {
		if (!t || !t->lazy)return;
		if (t->l)t->l->lazy ^= 1; //propagate lazy
		if (t->r)t->r->lazy ^= 1;
		if (!t->l) t->l = t->r, t->r = 0;
		else if (!t->r) t->r = t->l, t->l = 0;
		else swap(t->l, t->r);
		t->lazy = 0;
		t->mini.sd = size(t) - t->mini.sd - 1;//hax jak chcemy miec indeks minimum
	}
	void combine(node * &t, node * l, node * r) { //dzieci policzone -> policzmy co u nas 
		if (!t) return;
		t->mini = {t->val, size(l)};
		if (l && l->mini.ft <= t->mini.ft) t->mini = l->mini;
		if (r && r->mini.ft < t->mini.ft) {t->mini = r->mini; t->mini.sd += 1 + size(l);}
		
	}
	void operation(node * t) { //operation of segtree tu nie ruszac
		if (!t)return;
		lazy(t->l); lazy(t->r); //imp:propagate lazy before combining t->l,t->r;
		combine(t, t->l, t->r);
	}
	void split(node * t, node * &l, node * &r, int pos, int offset = 0) {
		if (!t)return void(l = r = NULL);
		lazy(t);
		int curr_pos = offset + size(t->l);
		if (curr_pos <= pos) //element at pos goes to left subtree(l)
			split(t->r, t->r, r, pos, curr_pos + 1), l = t;
		else
			split(t->l, l, t->l, pos, offset), r = t;
		upd_size(t);
		operation(t);
	}
	void merge(node * &t, node * l, node * r) { //l->leftarray,r->rightarray,t->resulting array
		lazy(l); lazy(r);
		if (!l || !r) t = l ? l : r;
		else if (l->prior > r->prior)merge(l->r, l->r, r), t = l;
		else    merge(r->l, l, r->l), t = r;
		upd_size(t);
		operation(t);
	}
	node * init(int val) {
		node * ret = &_arr[ctr++];
		ret->prior = rand(); ret->size = 1;
		ret->val = val;
		ret->mini = {val, 0}; ret->lazy = 0;//te linijke tez ustawic
		return ret;
	}
	pair < int, int > range_query(node * t, int l, int r) { //[l,r]
		node * L, * mid, * R;
		split(t, L, mid, l - 1);
		split(mid, t, R, r - l); //note: r-l!!
		auto ans = t->mini;
		ans.sd += l; /////////////////odcinamy lewo, prawo i zwracamy odpowiedz w korzeniu
		merge(mid, L, t);
		merge(t, mid, R);
		return ans;
	}
	void range_update(node * t, int l, int r) { //[l,r], odwracamy przedzial
		node * L, * mid, * R;
		split(t, L, mid, l - 1);
		split(mid, t, R, r - l); //note: r-l!!
		t->lazy ^= 1; //lazy_update
		merge(mid, L, t);
		merge(t, mid, R);
	}
	node* add(T val)
	{
		node * temp;
		merge(temp, root, init(val));
		root = temp;
		return root;
	}
};
#undef T
/*
auto ind_min = t.range_query(t.root, i, n-1); zapytanie na przedziale
t.range_update(t.root, i, ind_min.sd); odwrocenie przedzialu, indeksujemy od 0
*/
