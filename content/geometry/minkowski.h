// assumes P and Q are convex and ordered in a counter-clockwise manner
// O(n) 
// passed: https://codeforces.com/problemset/problem/87/E

#include "point.h" 

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
