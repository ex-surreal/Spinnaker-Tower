#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <math.h>
class Vector {
public:
	double x, y, z;
	Vector(double _x = 0, double _y = 0, double _z = 0) {
		this->x = _x;
		this->y = _y;
		this->z = _z;
	}

	Vector operator + (Vector that) {
		return Vector(this->x+that.x, this->y+that.y, this->z+that.z);
	}

	double operator / (Vector that) {
		return this->x*that.x + this->y*that.y + this->z*that.z;
	}

	Vector operator * (Vector that) {
		double a = this->y*that.z - this->z*that.y;
		double b = this->z*that.x - this->x*that.z;
		double c = this->x*that.y - this->y*that.x;
		return Vector(a, b, c);
	}

	Vector operator * (double constant) {
		return Vector(this->x*constant, this->y*constant, this->z*constant);
	}

	Vector operator - (Vector that) {
		return Vector(this->x-that.x, this->y-that.y, this->z-that.z);
	}

	double val() {
		return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
	}

	void normalize() {
		double v = this->val();
		// cout << v << endl;
		this->x /= v;
		this->y /= v;
		this->z /= v;
	}
};
#endif
