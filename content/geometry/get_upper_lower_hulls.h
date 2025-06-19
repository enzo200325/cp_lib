// O(n) 
// gets upper and lower hulls from polygon P 
// passed: https://codeforces.com/problemset/problem/87/E

#include "point.h" 

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
