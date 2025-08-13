/**
 * Author: me
 * Date:
 * License: 
 * Source: benq's library
 * Description: computes Minkowski sum of (assumed) convex polygons 'a' and 'b' 
 * O(n * log(n)) 
 * Status: not tested, trusting benq
 */

#include "Point.h"

using pt = Point<ll>; 
vector<pt> minkowski(vector<pt> a, vector<pt> b) {
	if (a.size() > b.size()) swap(a, b);
	if (!a.size()) return {};
	if (a.size() == 1) {
        for (pt &p : b) p = p + a[0]; 
		return b;
	}
	rotate(begin(a), min_element(all(a)), end(a));
	rotate(begin(b), min_element(all(b)), end(b));
	a.emplace_back(a[0]), a.emplace_back(a[1]);
	b.emplace_back(b[0]), b.emplace_back(b[1]);
	vector<pt>result;
	int i = 0, j = 0;
	while (i < (int)a.size()-2 || j < (int)b.size()-2) {
		result.emplace_back(a[i]+b[j]);
		ll crs = (a[i+1]-a[i]).cross(b[j+1]-b[j]);
		i += (crs >= 0);
		j += (crs <= 0);
	}
	return result;
}
