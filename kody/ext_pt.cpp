inline int prv(int i, int n) { return i == 0 ? n-1 : i-1; }
inline int nxt(int i, int n) { return i == n-1 ? 0 : i+1; }
template <class T> inline int sgn(T a) { return (T(0) < a) - (a < T(0)); }

template <class Function>
int extremeVertex(const Polygon& poly, Function direction) {
    int n = static_cast<int>(poly.size()), left = 0, leftSgn;
    auto vertexCmp = [&poly, direction](int i, int j) {
        return sgn(det(direction(poly[j]), poly[j] - poly[i])); };
    auto isExtreme = [n, vertexCmp](int i, int& iSgn) {
        return (iSgn = vertexCmp(nxt(i, n), i)) >= 0 && vertexCmp(i, prv(i, n)) < 0; };
    for (int right = isExtreme(0, leftSgn) ? 1 : n; left + 1 < right;) {
        int middle = (left + right) / 2, middleSgn;
        if (isExtreme(middle, middleSgn)) {
            return middle;
        } else if (leftSgn != middleSgn ? leftSgn < middleSgn : leftSgn == vertexCmp(left, middle)){
            right = middle; 
        } else {
            left = middle, leftSgn = middleSgn;
        }
    }
    return left;
}

pair<int, int> tangentsConvex(const C& point, const Polygon& poly) {
      return {extremeVertex(poly, [&point](const C& q) { return q - point; }),
                extremeVertex(poly, [&point](const C& q) { return point - q; })};
}

pair<int, int> lohi(const C& dir, const Polygon& poly) {
    return {extremeVertex(poly, [&dir](const C& q) { return dir * C(0, 1);}),
            extremeVertex(poly, [&dir](const C& q) { return dir * C(0, -1);})};
}
