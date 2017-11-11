typedef long double R;
typedef complex<R> C;

#define x real()
#define y imag()

static bool whateverb;
const R eps = 1e-12;

bool eq(R r1, R r2) { return abs(r1 - r2) < eps; }

bool eq(C c1, C c2) { return eq(c1.x, c2.x) and eq(c1.y, c2.y); }

R dot(C c1, C c2) { return c1.x * c2.x + c1.y * c2.y;}
R det(C c1, C c2) { return c1.x * c2.y - c1.y * c2.x;}

bool an_cmp(const C& c1, const C& c2){
        bool b1 = (c1.x > 0) || (c1.x == 0 && c1.y > 0);
        bool b2 = (c2.x > 0) || (c2.x == 0 && c2.y > 0);
        if (b1 == b2)
            return det(c1, c2) > 0;
        else
            return b1>b2;
}

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
        if(eq(arg(n), arg(other.n))){
            return c > other.c;
        } else {
            return arg(n) < arg(other.n);
        }
    }

	C dir() const { return n * C(0, -1); }
	
	C val(R t) const { return c * n + t * dir();}
    R y_val(R x1) const { return (c - n.x * x1) / n.y; }
    R x_val(R y1) const { return (c - n.y * y1) / n.x; }

	R tis(const line& other) const {
		if(eq(det(n, other.n), 0)){
            return 0;
        } else {
			return (other.c - c * dot(n, other.n)) / dot(dir(), other.n);
		}
	}
};

C is(const line& a, const line& b) { return a.val(a.tis(b));}

R dist(const line& l, const C& p) { return fabs(dot(p, l.n) - l.c); }

struct seg{
	line l;
	R start, end;
	
	seg(C p1, C p2)
		:l{p1, p2}, start{dot(l.dir(), p1)}, end{dot(l.dir(), p2)} {}
		
	C p1() const { return l.val(start); }
	C p2() const { return l.val(end); }
	
	R len() const { return fabs(end - start); }
	
	bool okt(R t) const { return eq(fabs(t - start) + fabs(t - end), len()); }
};

C is(const seg& s1, const seg& s2, bool& ok = whateverb) {
	R t1 = s1.l.tis(s2.l), t2 = s2.l.tis(s1.l);
	ok = !eq(det(s1.l.n, s2.l.n), 0) and s1.okt(t1) and s2.okt(t2);
	return s1.l.val(t1);
}

C is(const seg& s, const line& l, bool& ok = whateverb) {
	R t = s.l.tis(l);
	ok = s.okt(t) and !eq(det(s.l.n, l.n), 0); 
    return s.l.val(t);
}

C max_v(const C& v1, const C& v2, const C& od){ return max(v1, v2, [&od](const C& a, const C& b){return dot(a, od) < dot(b, od);});}

bool empty_is(const line& l1, const line& l2) { return eq(dot(l1.n, l2.n), -1.0) and l1.c + eps > -l2.c;}

static C whateverc;
bool check_hplane(vector<line> hplanes, C& pt_in = whateverc){
    random_shuffle(all(hplanes));
    C od = -hplanes[0].n;
    pt_in = hplanes[0].val(0);
    for(auto& l1 : hplanes){
        if(dot(l1.n, pt_in) < l1.c - eps){
            R min_t = -INF, max_t = INF;
            for(auto& l2 : hplanes){
                if(&l2 != &l1){
                    R dp = dot(l1.dir(), l2.n), ti = l1.tis(l2);
                    if(dp > eps){
                        min_t = max(min_t, ti);
                    } else if(dp < -eps){
                        max_t = min(max_t, ti);
                    } else if(empty_is(l1, l2)){
                        return false;
                    }
                } else {
                    if(min_t > max_t){
                        return false;
                    } else{
                        pt_in = max_v(l1.val(max_t), l1.val(min_t), od);
                    }
                    break;
                }
            }
        }
    }
    return true;
}

struct Circ{
    C cent;
    R rad;
    Circ(C icent, R irad)
        :cent{icent}, rad{irad} {}

    Circ() = default;
};


R triangle_area(C v1, C v2, C v3){ return fabs(det(v2 - v1, v2 - v3)) / 2.0; }

R poly_area(vector<C> poly){
    R res = 0.0;
    rep(i, 1, SZ(poly) - 1){
        res += triangle_area(poly[0], poly[i], poly[i + 1]);
    }
    return res;
}

vector<C> poly_cut(const vector<C>& poly, line l){
    vector<C> poly1;
    rep(i, 0, SZ(poly)){
        if(dot(poly[i], l.n) > l.c){
            poly1.pb(poly[i]);
        }
        bool does_is;
        C isp = is(seg(poly[i], poly[(i + 1) % SZ(poly)]), l, does_is);
        if(does_is){
            poly1.pb(isp);
        }
    }
    return poly1;
}
