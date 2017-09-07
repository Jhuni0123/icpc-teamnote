typedef struct Point{
    ll x,y,n;
} Point;

ll ccw(Point a, Point b, Point c){
    b.x -= a.x, b.y -= a.y;
    c.x -= a.x, c.y -= a.y;
    return b.x*c.y - c.x*b.y;
}

vector<Point> convex_hull(vector<Point> ps){
    if (ps.size() < 3)return ps;
    vector<Point> upper, lower;
    sort(ps.begin(), ps.end(),[](const Point &a, const Point &b) {
        if (a.x == b.x) return a.y < b.y; return a.x < b.x;
    });
    for(const auto &p : ps){ // ccw without `=` when include every point in convex hull
        while(upper.size() >= 2 && ccw(*++upper.rbegin(), *upper.rbegin(), p) >= 0)upper.pop_back();
        while(lower.size() >= 2 && ccw(*++lower.rbegin(), *lower.rbegin(), p) <= 0)lower.pop_back();
        upper.emplace_back(p);
        lower.emplace_back(p);
    }
    lower.insert(lower.end(), ++upper.rbegin(), --upper.rend());
    return lower;
}

vector<Point> convex_hull2(vector<Point> ps){ // sorting angle
    if (ps.size() < 3)return ps;
    vector<Point> convex;
    sort(ps.begin(), ps.end(), [](Point &a, Point &b){
        if(a.x == b.x)return a.y < b.y; return a.x<b.x;
    });
    Point d = ps[0];
    for(auto &p : ps){
        p.x -= d.x;p.y -= d.y;
    }
    sort(ps.begin(), ps.end(), [](Point &a, Point &b){
        if (ccw({0,0},a,b) == 0) return a.x*a.x + a.y*a.y < b.x*b.x + b.y*b.y;
        return ccw({0,0},a,b) > 0;
    });
    for(auto &p : ps){
        while(convex.size() >= 2 && ccw(*++convex.rbegin(), *convex.rbegin(), p) <= 0)convex.pop_back();
        convex.emplace_back(p);
    }
    for(auto &p : convex){
        p.x += d.x;p.y += d.y;
    }
    return convex;
}
