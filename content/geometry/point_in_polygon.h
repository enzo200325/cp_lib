// assumes both hulls are sorted by x coordinates 
// to get both hulls you can use "get_upper_lower_hulls.cpp"  
// O(logn) 
// passed: https://codeforces.com/problemset/problem/87/E

#include "point.h" 

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
