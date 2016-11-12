const C findCentroid(vector < C >& pts){
    int nPts = SZ(pts);
		C off = pts[0];
    R twicearea = 0;
    R x_coord = 0;
    R y_coord = 0;
    C p1, p2;
    R f;
    for (int i = 0, j = nPts - 1; i < nPts; j = i++) {
        p1 = pts[i];
        p2 = pts[j];
        f = (p1.x - off.x) * (p2.y - off.y) - (p2.x - off.x) * (p1.y - off.y);
        twicearea += f;
        x_coord += (p1.x + p2.x - 2 * off.x) * f;
        y_coord += (p1.y + p2.y - 2 * off.y) * f;
    }
    f = twicearea * 3;
    return C(x_coord / f + off.x, y_coord / f + off.y);
}
