#ifndef COLOR_H
#define COLOR_H
class Color {
public:
	double r, g, b;
	Color(double _r = 1, double _g = 1, double _b = 1) {
		this->r = _r;
		this->g = _g;
		this->b = _b;
	}

	Color operator * (double x) {
		return Color(r*x, g*x, b*x);
	}
};
#endif
