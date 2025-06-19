// only tested for integer points
// passed two problems, still in progress
template<typename T>
struct P {
    T x, y;
    T cross(const P& o) { return x * o.y - y * o.x; }
    T dist2(const P& o) { return x * o.x + y * o.y; }
    P operator+(const P& o) { return P(x + o.x, y + o.y); }
    P operator-(const P& o) { return P(x - o.x, y - o.y); }
    P operator-() { return P(-x, -y); }
    bool operator<(const P& o) const { return make_pair(x, y) < make_pair(o.x, o.y); }
    bool operator==(const P& o) const { return make_pair(x, y) == make_pair(o.x, o.y); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};
using pt = P<ll>;
void __print(pt x) {cerr << x;}
double cross(const pt& p, const pt& q, const pt& r) {
    pt vq = {q.x - p.x, q.y - p.y};
    pt vr = {r.x - p.x, r.y - p.y};
    return vq.cross(vr);
}


// tested for integer values 
// passed: https://judge.yosupo.jp/problem/static_convex_hull
vector<pt> convex_hull(vector<pt> P, bool collinear = 0) {
    sort(P.begin(), P.end()); 
    P.erase(unique(all(P)), P.end()); 
    int n = P.size(); 
    if (n <= 1) return P; 
    vector<pt> upper_hull = {P[0]}; 
    vector<pt> lower_hull = {P[0]}; 
    for (int i = 1; i < n; i++) {
        if (cross(P[0], P[n-1], P[i]) >= 0) {
            while (upper_hull.size() > 1) {
                ll cr = cross(upper_hull.end()[-2], upper_hull.end()[-1], P[i]); 
                if (cr > (collinear ? 0 : -1)) upper_hull.pop_back(); 
                else break; 
            } 
            upper_hull.emplace_back(P[i]); 
        } 
        if (cross(P[0], P[n-1], P[i]) <= 0) {
            while (lower_hull.size() > 1) {
                ll cr = cross(lower_hull.end()[-2], lower_hull.end()[-1], P[i]); 
                if (cr < (collinear ? 0 : 1)) lower_hull.pop_back(); 
                else break ;
            } 
            lower_hull.emplace_back(P[i]); 
        } 
    } 

    upper_hull.pop_back(); 
    reverse(all(upper_hull)); 
    upper_hull.pop_back(); 
    lower_hull.insert(lower_hull.end(), all(upper_hull)); 
    return lower_hull; 
} 

// assumes P and Q are convex and ordered in a counter-clockwise manner
// O(n) 
// passed: https://codeforces.com/problemset/problem/87/E
vector<pt> minkowski(vector<pt> P, vector<pt> Q) {
    rotate(P.begin(), min_element(all(P)), P.end()); 
    rotate(Q.begin(), min_element(all(Q)), Q.end()); 
    P.emplace_back(P[0]); 
    Q.emplace_back(Q[0]); 
    debug(P); 
    debug(Q); 

    vector<pt> ret; 
    int i = 0, j = 0; 
    while (i < (int)P.size()-1 || j < (int)Q.size()-1) {
        ret.emplace_back(P[i] + Q[j]); 
        if (i == (int)P.size() - 1) j++; 
        else if (j == (int)Q.size() - 1) i++; 
        else {
            pt vi = P[i+1] - P[i]; 
            pt vj = Q[j+1] - Q[j]; 
            if (vi.cross(vj) > 0) i++; 
            else j++; 
        } 
    } 

    return ret; 
} 

// O(n) 
// gets upper and lower hulls from polygon P 
// passed: https://codeforces.com/problemset/problem/87/E
pair<vector<pt>, vector<pt>> get_hulls(vector<pt>& P) {
    rotate(P.begin(), min_element(all(P)), P.end()); 
    int n = P.size(); 
    vector<pt> upper_hull = {P[0]}, lower_hull = {P[0]}; 
    for (int i = 1; i < n; i++) {
        if (cross(P[0], P[n-1], P[i]) >= 0) upper_hull.emplace_back(P[i]); 
        if (cross(P[0], P[n-1], P[i]) <= 0) lower_hull.emplace_back(P[i]); 
    } 
    return make_pair(lower_hull, upper_hull); 
} 

// assumes both hulls are sorted by x coordinates 
// to get both hulls you can use "get_upper_lower_hulls.cpp"  
// O(logn) 
// passed: https://codeforces.com/problemset/problem/87/E
bool point_in_polygon(pt p, vector<pt>& lower_hull, vector<pt>& upper_hull) {
    auto ub = upper_bound(all(upper_hull), p); 
    auto lb = upper_bound(all(lower_hull), p); 
    if (ub == upper_hull.begin()) return false; 
    if (lb == lower_hull.begin()) return false; 
    if (ub == upper_hull.end() || lb == lower_hull.end()) return p == upper_hull.back(); 

    int iu = ub - upper_hull.begin() - 1; 
    int il = lb - lower_hull.begin() - 1; 
    if (cross(lower_hull[il], lower_hull[il+1], p) >= 0 && 
            cross(upper_hull[iu], upper_hull[iu+1], p) <= 0) return true; 
    else return false; 
} 
