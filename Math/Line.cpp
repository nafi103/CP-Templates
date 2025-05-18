struct Line {
    double a, b, c;
    Line (int _a, int _b, int _c): a(_a), b(_b), c(_c){}
};

void pointsToLine(const Point &p1, const Point &p2, Line &l) {
    if (fabs(p1.x-p2.x) < EPS)
    l = {1.0, 0.0,-p1.x};
    else
    l = {-(double)(p1.y-p2.y) / (p1.x-p2.x),1.0,-(double)(l.a*p1.x)- p1.y};
}

void pointSlopeToLine(Point p, double m, Line &l) {
    l.a =-m;
    l.b = 1.0;
    l.c =-((l.a * p.x) + (l.b * p.y));
}

bool areParallel(Line l1, Line l2) {
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areSame(Line l1, Line l2) {
    return areParallel(l1, l2) && (fabs(l1.c-l2.c) < EPS);
}

bool areIntersect(Line l1, Line l2, Point &p) {
    if (areParallel(l1, l2)) return false;
    p.x = (l2.b*l1.c- l1.b*l2.c) / (l2.a*l1.b- l1.a*l2.b);
    if (fabs(l1.b) > EPS)
        p.y =-(l1.a*p.x + l1.c);
    else
        p.y =-(l2.a*p.x + l2.c);
    return true;
}