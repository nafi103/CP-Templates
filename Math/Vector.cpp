struct Vector {
    double x, y;
    Vector(double _x, double _y) : x(_x), y(_y) {}
};

Vector toVector(const Point &a, const Point &b) {
    return Vector(b.x-a.x, b.y-a.y);
}

Vector scale(const Vector &v, double s) {
    return Vector(v.x * s, v.y * s);
}

Point translate(const Point &p, const Vector &v) {
    return Point(p.x + v.x, p.y + v.y);
}

double angle(const Point &a, const Point &o, const Point &b) {
    Vector oa = toVector(o, a), ob = toVector(o, b);
    // a != o != b
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

double cross(Vector a, Vector b) { return a.x*b.y- a.y*b.x; }

bool ccw(Point p, Point q, Point r) {
    return cross(toVector(p, q), toVector(p, r)) > EPS;
}

bool collinear(Point p, Point q, Point r) {
    return fabs(cross(toVector(p, q), toVector(p, r))) < EPS;
}