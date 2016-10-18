typedef long double R;
typedef complex<R> C;

static bool whatever;

const R eps = 1e-10;

bool eq(R r1, R r2) { return fabs(r1 - r2) < eps; }

bool eq(C c1, C c2) { return eq(c1.real(), c2.real()) and eq(c1.imag(), c2.imag()); }

R dot(C c1, C c2) { return c1.real() * c2.real() + c1.imag() * c2.imag();}
R det(C c1, C c2) { return c1.real() * c2.imag() - c1.imag() * c2.real();}

struct line{
	C n;
	R c;
	line(C n1, R c1) 
		:n{n1 / abs(n1)}, c{c1} {}
	
	line(C p1, C p2) 
		:n{((p2 - p1) / abs(p2 - p1)) * C(0, 1)}, c{dot(p1, n)} {}
		
	C dir() const { return n * C(0, 1); }
	
	C val(R t) const { return c * n + t * dir();}
	
	R tintersect(const line& other, bool& ok = whatever) const {
		ok = !eq(det(n, other.n), 0);
		if(ok) {
			return (other.c - c * dot(n, other.n)) / dot(dir(), other.n);
		} else {
			return 0;
		}
	}
};

C intersect(const line& a, const line& b, bool& ok = whatever) { return a.val(a.tintersect(b, ok));}

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

C intersect(const seg& s1, const seg& s2, bool& ok = whatever) {
	R t1 = s1.l.tintersect(s2.l, ok), t2 = s2.l.tintersect(s1.l, ok);
	ok &= (s1.okt(t1) and s2.okt(t2));
	return s1.l.val(t1);
}

C intersect(const seg& s, const line& l, bool& ok = whatever) {
	R t = s.l.tintersect(l, ok);
	ok &= s.okt(t); return s.l.val(t);
}
