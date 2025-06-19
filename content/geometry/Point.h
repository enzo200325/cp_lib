// only tested for integers 
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
