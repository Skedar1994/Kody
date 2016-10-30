typedef long double R;
typedef complex<R> C;

#define x real()
#define y imag()

static bool whatever;

const R eps = 1e-10;

bool eq(R r1, R r2) { return fabs(r1 - r2) < eps; }

bool eq(C c1, C c2) { return eq(c1.x, c2.x) and eq(c1.y, c2.y); }

R dot(C c1, C c2) { return c1.x * c2.x + c1.y * c2.y;}
R det(C c1, C c2) { return c1.x * c2.y - c1.y * c2.x;}

struct line{
	C n;
	R c;
	line(C n1, R c1) 
		:n{n1 / abs(n1)}, c{c1} {}
	
	line(C p1, C p2) 
		:n{((p2 - p1) / abs(p2 - p1)) * C(0, 1)}, c{dot(p1, n)} {}

    line() = default;

    bool operator <(const line& other) const {
        return make_pair(arg(n), -c) < make_pair(arg(other.n), -other.c);
    }

	C dir() const { return n * C(0, -1); }
	
	C val(R t) const { return c * n + t * dir();}
	
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

C is(const seg& s1, const seg& s2, bool& ok = whatever) {
	R t1 = s1.l.tis(s2.l), t2 = s2.l.tis(s1.l);
	ok = !eq(det(s1.l.n, s2.l.n), 0) and s1.okt(t1) and s2.okt(t2);
	return s1.l.val(t1);
}

C is(const seg& s, const line& l, bool& ok = whatever) {
	R t = s.l.tis(l);
	ok = s.okt(t) and !eq(det(s.l.n, l.n), 0); 
    return s.l.val(t);
}

bool wrong(const line& l_prev, const line& l_last, const line& l_new) { 
    if(!eq(det(l_last.n, l_new.n), 0)) {
        return l_last.tis(l_new) < l_last.tis(l_prev) + eps;
    } else {
        return false;
    }
}

deque<line> cor(const vector<line>& lns) {
    deque<line> ans;
    for(auto& l : lns) {
        while(SZ(ans) >= 2 and wrong(ans.rbegin()[1], ans.back(), l)) {
            ans.pop_back();
        }
        ans.push_back(l);
    }
    return ans;
}

bool empty_is(const line& l1, const line& l2) { return eq(dot(l1.n, l2.n), -1.0) and l1.c + eps > -l2.c;}

vector<line> hplane(vector<line> lns) {
    sort(all(lns));
    lns.resize(distance(lns.begin(), unique(all(lns), [](line l1, line l2){ return eq(dot(l1.n, l2.n), 1.0); })));
    vector<line> lup, ldown;
    for(auto& l : lns) {
        if(arg(l.n) > 0) {
            ldown.pb(l);
        } else {
            lup.pb(l);
        }
    }
    deque<line> aup = cor(lup), adown = cor(ldown);

    while(SZ(aup) >= 2 or SZ(adown) >= 2) {
        if(empty_is(aup[0], adown.back()) or empty_is(adown[0], aup.back())){
            return vector<line>();
        }
        if(SZ(aup) >= 2 and wrong(adown.back(), aup[0], aup[1])) {
            aup.pop_front();
        } else if(SZ(aup) >= 2 and wrong(aup.rbegin()[1], aup.back(), adown[0])) {
            aup.pop_back();
        } else if(SZ(adown) >= 2 and wrong(aup.back(), adown[0], adown[1])) {
            adown.pop_front();
        } else if(SZ(adown) >= 2 and wrong(adown.rbegin()[1], adown.back(), aup[0])) {
            adown.pop_back();
        } else {
            break;
        }
    }
    vector<line>ans;ans.insert(ans.end(), all(aup)); ans.insert(ans.end(), all(adown));
    return ans;
}

vector<C> poly(const vector<line>& lns) {
    vector<C> ans;
    if(SZ(lns) > 2) {
        rep(i, 0, SZ(lns)) {
            ans.pb(is(lns[(SZ(lns) + i - 1) % SZ(lns)], lns[i]));
        }
    }
    return ans;
}