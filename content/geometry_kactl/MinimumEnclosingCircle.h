/**
 * Author: Andrew He, chilli
 * Date: 2019-05-07
 * License: CC0
 * Source: folklore
 * Description: Computes the minimum circle that encloses a set of points.
 * Time: expected O(n)
 * Status: stress-tested
 */
#pragma once

#include "circumcircle.h"

pair<pt, double> mec(vector<pt> ps) {
	shuffle(all(ps), mt19937(time(0)));
	pt o = ps[0];
	double r = 0, EPS = 1 + 1e-8;
    for (int i = 0; i < ps.size(); i++) if ((o - ps[i]).dist() > r * EPS) {
		o = ps[i], r = 0;
		for (int j = 0; j < i; j++) if ((o - ps[j]).dist() > r * EPS) {
			o = (ps[i] + ps[j]) / 2;
			r = (o - ps[i]).dist();
			for (int k = 0; k < j; k++) if ((o - ps[k]).dist() > r * EPS) {
				o = ccCenter(ps[i], ps[j], ps[k]);
				r = (o - ps[i]).dist();
			}
		}
	}
	return {o, r};
}
