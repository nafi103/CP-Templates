using ftype = double;

struct Point {
    ftype x, y, z;
    Point() {}
    Point(ftype x, ftype y, ftype z): x(x), y(y), z(z) {}
    Point& operator+=(const Point &t) {
        x += t.x;
        y += t.y;
        z += t.z;
        return *this;
    }
    Point& operator-=(const Point &t) {
        x -= t.x;
        y -= t.y;
        z -= t.z;
        return *this;
    }
    Point& operator*=(ftype t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    Point& operator/=(ftype t) {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }
    Point operator+(const Point &t) const {
        return Point(*this) += t;
    }
    Point operator-(const Point &t) const {
        return Point(*this) -= t;
    }
    Point operator*(ftype t) const {
        return Point(*this) *= t;
    }
    Point operator/(ftype t) const {
        return Point(*this) /= t;
    }
};

Point operator*(ftype a, Point b) {
    return b * a;
}

ftype dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point cross(Point a, Point b) {
    return Point(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}

ftype triple(Point a, Point b, Point c) {
    return dot(a, cross(b, c));
}

Point intersect(Point a1, Point n1, Point a2, Point n2, Point a3, Point n3) {
    Point x(n1.x, n2.x, n3.x);
    Point y(n1.y, n2.y, n3.y);
    Point z(n1.z, n2.z, n3.z); 
    Point d(dot(a1, n1), dot(a2, n2), dot(a3, n3));
    return Point(triple(d, y, z),
                   triple(x, d, z),
                   triple(x, y, d)) / triple(n1, n2, n3);
}