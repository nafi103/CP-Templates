const double EPS = 1e-9;

struct Point {
    double x, y;
    Point() { x = y = 0.0; }

    Point(double _x, double _y) : x(_x), y(_y) {}

    bool operator < (Point other) const {
        if (fabs(x-other.x) > EPS)
            return x < other.x;
        return y < other.y;
    }
    bool operator == (const Point &other) const {
        return (fabs(x-other.x) < EPS) && (fabs(y-other.y) < EPS);
    }
};

double dist(const Point &p1, const Point &p2) {
    return hypot(p1.x-p2.x, p1.y-p2.y);
}

double DEG_to_RAD(double d) { return d*pi / 180.0; }

double RAD_to_DEG(double r) { return r*180.0 / pi; }

Point rotate(const Point &p, double theta) {
    double rad = DEG_to_RAD(theta);
    
    return Point(p.x*cos(rad)- p.y*sin(rad),p.x*sin(rad) + p.y*cos(rad));
}
