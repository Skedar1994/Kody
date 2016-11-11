typedef long long R;
typedef complex<R> C;
const long double eps = 1e-12;

#define x real()
#define y imag()

bool eq(R r1, R r2) { return abs(r1 - r2) < eps; }

bool cmpX(const C& a, const C& b) { return a.x < b.x; }
bool cmpY(const C& a, const C& b) { return a.y < b.y; }

R dot(const C& a, const C& b){ return a.x * b.x + a.y * b.y; }

R sqlen(const C& a){ return norm(a); }

struct KDT{
    vector<C> pts;
    vector<bool>divX;

    R sqd;
    int cln;

    void build(int left, int right){ 
        int mid = (left + right) >> 1;
        vector<C>::iterator itl = pts.begin() + left, itr = pts.begin() + right + 1;
        auto pcx = minmax_element(itl, itr, cmpX), pcy = minmax_element(itl, itr, cmpY);
        divX[mid] = (*pcx.sd).x - (*pcx.ft).x > (*pcy.sd).y - (*pcy.ft).y;
        nth_element(pts.begin() + left, pts.begin() + mid, pts.begin() + right + 1, divX[mid] ? cmpX : cmpY); 

        if (left + 2 >= right)
            return;
        build(left, mid - 1);
        build(mid + 1, right);
    }

    KDT(const vector<C>& ipts) : pts(ipts), divX(SZ(pts)) { build(0, SZ(pts) -1); }

    void find_near(int left, int right, C pt) {
        if(left > right){
            return;
        }
        int mid = (left + right) >> 1;
        C d = pt - pts[mid];
        if(sqd > sqlen(d) and !eq(sqlen(d), 0)){
            sqd = sqlen(d);
            cln = mid;
        }
        R delta = divX[mid] ? d.x : d.y;
        int l1 = left, r1 = mid - 1, l2 = mid + 1, r2 = right;
        if(delta > 0){
            swap(l1, l2); swap(r1, r2);
        }
        find_near(l1, r1, pt);
        if(sqlen(C(delta, 0)) < sqd){
            find_near(l2, r2, pt);
        }
    }

    C find_near(C pt) {
        sqd = 1e9;
        find_near(0, SZ(pts) - 1, pt);
        return pts[cln];
    }
};
