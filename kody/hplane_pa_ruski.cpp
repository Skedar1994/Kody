typedef double R;
typedef complex<R> C;

typedef long long RL;
typedef complex<RL> CL;

#define x real()
#define y imag()

const R eps = 1e-14;

bool eq(R r1, R r2) { return abs(r1 - r2) < eps; }

bool eq(const C& c1,const C& c2) { return eq(c1.x, c2.x) and eq(c1.y, c2.y); }

R dot(const C& c1, const C& c2) { return c1.x * c2.x + c1.y * c2.y;}
R det(const C& c1, const C& c2) { return c1.x * c2.y - c1.y * c2.x;}

RL dot(const CL& c1, const CL& c2) { return c1.x * c2.x + c1.y * c2.y;}
RL det(const CL& c1, const CL& c2) { return c1.x * c2.y - c1.y * c2.x;}

C to_C(const CL& cl){ return C(cl.x, cl.y);}

struct line{
	CL nl;
    RL cl;
	C n, d;
    R c;
    line() = default;
    line(CL p1, CL p2)
        :nl{(p2 - p1) * CL(0, 1)}, cl{dot(p1, nl)}, n{to_C(nl) / abs(to_C(nl))}, d{n.y, -n.x}, c{dot(to_C(p1), n)} {}

   	bool operator <(const line& other) const {
        RL de = det(nl, other.nl);
        if(de == 0){
            return c > other.c;
        } else {
            return de > 0;
        }
    }
	
	C val(R t) const { return c * n + t * d;}

	R tis(const line& other) const {
		return (other.c - c * dot(n, other.n)) / dot(d, other.n);
	}
};

ostream& operator <<(ostream& o, const line& l){ return o << l.n << " " << l.c;}

C is(const line& a, const line& b) { return a.val(a.tis(b));}


namespace hplane{
    const int N = 200000;
    line lns[2 * N + 1];
    C poly[2 * N + 1];
    int jd1, jd2, ju1, ju2, ans_sz, poly_sz, n = 0;
    inline int cnt(){ return ju2 + jd2 - ju1 - jd1 + 2; }
    void add(const line& l){ lns[n++] = l;}
    void clear(){ n = 0;}

    bool empty_is(const line& l1, const line& l2) { return det(l1.nl, l2.nl) == 0 and dot(l1.nl, l2.nl) < 0 and l1.c + eps > -l2.c;}
    
    bool wrong(const line& l_prev, const line& l_last, const line& l_new) { 
        if(!eq(det(l_last.nl, l_new.nl), 0)) {
            return l_last.tis(l_new) < l_last.tis(l_prev) + eps;
        } else {
            return false;
        }
    }

    int cor(int j1, int j2){
        sort(lns + j1, lns + j2 + 1);
        j2 = unique(lns + j1, lns + j2 + 1, [](line& l1, line& l2){ return dot(l1.nl, l2.nl) > 0 and det(l1.nl, l2.nl) == 0;}) - lns - 1;
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
        ju1 = partition(lns, lns + n, [](const line& l){ return det(CL(1, 0), l.nl) > 0 or (l.nl.y == 0 and l.nl.x < 0);}) - lns;
        ju2 = n - 1;
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
            rep(i, 0, ans_sz){
                poly[i] = is(lns[i], lns[(i + 1) % ans_sz]);
            }
        } else {
            poly_sz = 0;
        }
    }
}
