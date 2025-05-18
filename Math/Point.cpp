const double EPS = 1e-9;

struct Point {
    double x, y;

    Point(int _x, int _y) : x(_x), y(_y){}

    void read(){
        cin>>x>>y;
    }

    bool operator == (const Point &other) const {
    return (fabs(x-other.x) < EPS) && (fabs(y-other.y) < EPS);
    }
};

double DEG_to_RAD(double d) { return d*pi / 180.0; }

double RAD_to_DEG(double r) { return r*180.0 / pi; }

Point rotate(const Point &p, double theta) {
    double rad = DEG_to_RAD(theta);
    return Point(p.x*cos(rad)- p.y*sin(rad),p.x*sin(rad) + p.y*cos(rad));
}

struct vec { double x, y;
    vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(const Point &a, const Point &b) {
    return vec(b.x-a.x, b.y-a.y);
}
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

bool ccw(Point p, Point q, Point r) {
    return cross(toVec(p, q), toVec(p, r)) > EPS;
}

bool collinear(Point p, Point q, Point r) {
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}