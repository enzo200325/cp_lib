// tested for integer values here: https://judge.yosupo.jp/problem/static_convex_hull

#include <point.h> 

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
