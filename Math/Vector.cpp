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


double cross(Vector a, Vector b) { return a.x*b.y- a.y*b.x; }

bool ccw(Point p, Point q, Point r) {
    return cross(toVector(p, q), toVector(p, r)) > EPS;
}

bool collinear(Point p, Point q, Point r) {
    return fabs(cross(toVector(p, q), toVector(p, r))) < EPS;
}

double dot(Vector a, Vector b) { return (a.x*b.x + a.y*b.y); }

double norm_sq(Vector v) { return v.x*v.x + v.y*v.y; }

double distToLine(Point p, Point a, Point b, Point &c) {
    Vector ap = toVector(a, p), ab = toVector(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));
    return dist(p, c);
}

double distToLineSegment(Point p, Point a, Point b, Point &c) {
    Vector ap = toVector(a, p), ab = toVector(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) {
        c = Point(a.x, a.y);
        return dist(p, a);
    }
    if (u > 1.0) {
        c = Point(b.x, b.y);
        return dist(p, b);
    }
    return distToLine(p, a, b, c);
}

double angle(const Point &a, const Point &o, const Point &b) {
    Vector oa = toVector(o, a), ob = toVector(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

bool intersect(Point &a, Point &b, Point &c, Point &d){
    if (cross(toVector(a, b), toVector(a, c)) == 0 and in_mid(a, b, c)) {
        return true;
    }
    if (cross(toVector(a, b), toVector(a, d)) == 0 and in_mid(a, b, d)) {
        return true;
    }
    if (cross(toVector(c, d), toVector(c, a)) == 0 and in_mid(c, d, a)) {
        return true;
    }
    if (cross(toVector(c, d), toVector(c, b)) == 0 and in_mid(c, d, b)) {
        return true;
    }
    if(sign(cross(toVector(a,b),toVector(a,c)))!=sign(cross(toVector(a,b),toVector(a,d)))
        and sign(cross(toVector(c,d),toVector(c,a)))!=sign(cross(toVector(c,d),toVector(c,b)))){
        return true;
    }
    return false;
}