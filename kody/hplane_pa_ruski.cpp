typedef double R;
typedef complex<R> C;

#define x real()
#define y imag()

const R eps = 1e-12;

bool eq(R r1, R r2) { return abs(r1 - r2) < eps; }

bool eq(const C& c1,const C& c2) { return eq(c1.x, c2.x) and eq(c1.y, c2.y); }

R dot(const C& c1, const C& c2) { return c1.x * c2.x + c1.y * c2.y;}
R det(const C& c1, const C& c2) { return c1.x * c2.y - c1.y * c2.x;}


struct line{
	C n;
	R c;
	line(C n1, R c1) 
		:n{n1 / abs(n1)}, c{c1} {}
	line(C p1, C p2) 
		:n{((p2 - p1) / abs(p2 - p1)) * C(0, 1)}, c{dot(p1, n)} {}
    	line(R a, R b)
        	:line(C(a, -1.0), b){}
    	line() = default;

   	bool operator <(const line& other) const {
        R d = det(n, other.n);
        if(eq(d, 0)){
            return c > other.c;
        } else {
            return d > 0;
        }
    }

	C dir() const { return n * C(0, -1); }
	
	C val(R t) const { return c * n + t * dir();}

	R tis(const line& other) const {
		/* if(eq(det(n, other.n), 0)){ */
            /* return 0; */
        /* } else { */
			return (other.c - c * dot(n, other.n)) / dot(dir(), other.n);
		/* } */
	}
};

C is(const line& a, const line& b) { return a.val(a.tis(b));}


namespace hplane{
    const int N = 2000;
    line lns[2 * N + 1];
    C poly[2 * N + 1];
    int jd1, jd2, ju1, ju2, ans_sz, poly_sz, n = 0;
    inline int cnt(){ return ju2 + jd2 - ju1 - jd1 + 2; }
    void add(const line& l){ lns[n++] = l;}
    void clear(){ n = 0;}

    bool empty_is(const line& l1, const line& l2) { return eq(dot(l1.n, l2.n), -1.0) and l1.c + eps > -l2.c;}
    
    bool wrong(const line& l_prev, const line& l_last, const line& l_new) { 
        if(!eq(det(l_last.n, l_new.n), 0)) {
            return l_last.tis(l_new) < l_last.tis(l_prev) + eps;
        } else {
            return false;
        }
    }

    int cor(int j1, int j2){
        sort(lns + j1, lns + j2 + 1);
        j2 = unique(lns + j1, lns + j2 + 1, [](line& l1, line& l2){ return eq(dot(l1.n, l2.n), 1.0);}) - lns - 1;
        int j = min(j1 + 1, j2);
        rep(i, j1 + 2, j2 + 1){
            j++;
            while(j >= j1 + 2 and wrong(lns[j - 2], lns[j - 1], lns[i])){
                j--;        
            }
            lns[j] = lns[i];
        }
        return j;
    }

    void c_front(int& j1, int& j2, int& j3){
        while((j3 - j2) >= 1 and wrong(lns[j1], lns[j2], lns[j2 + 1])) j2++;
    }
    void c_back(int& j1, int& j2, int& j3){
        while((j2 - j1) >= 1 and wrong(lns[j2 - 1], lns[j2], lns[j3])) j2--;
    }
    void solve(){
        ju1 = partition(lns, lns + n, [](const line& l){ return arg(l.n) > 0;}) - lns; ju2 = n - 1;
        jd1 = 0; jd2 = ju1 - 1;
        jd2 = cor(jd1, jd2); ju2 = cor(ju1, ju2);
        int chck = 0;
        while(chck != cnt() and (jd2 - jd1) >= 0 and (ju2 - ju1) >= 0 and ((jd2 - jd1) >= 1 or (ju2 - ju1) >= 1)){
            if(empty_is(lns[jd1], lns[ju2]) or empty_is(lns[ju1], lns[jd2])){
                ans_sz = 0; return;
            }
            chck = cnt();
            c_front(jd2, ju1, ju2);
            c_back(ju1, ju2, jd1);
            c_front(ju2, jd1, jd2);
            c_back(jd1, jd2, ju1);
        }
        rep(i, jd1, jd2 + 1){
            lns[i - jd1] = lns[i];
        }
        rep(i, ju1, ju2 + 1){
            lns[jd2 + 1 - jd1 + i - ju1] = lns[i];
        }
        ans_sz = cnt();
    }

    void get_poly(){
        if(ans_sz > 2){
            poly_sz = ans_sz;
            poly[0] = is(lns[ans_sz - 1], lns[0]);
            rep(i, 1, ans_sz){
                poly[i] = is(lns[i - 1], lns[i]);
            }
        } else {
            poly_sz = 0;
        }
    }
};
