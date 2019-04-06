#include <cmath>

inline double dist(double x0, double y0, double x1, double y1) {
	return sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0)));
}

//Reimpl in float only
inline float distf(float x0, float y0, float x1, float y1) {
	return dist(x0, y0, x1, y1);
}
