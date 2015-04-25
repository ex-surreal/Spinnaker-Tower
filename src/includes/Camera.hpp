#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "Vector.hpp"
class Camera {
public:
	Vector eye, look;
	Vector n, u, v, up;

	Camera(Vector _eye, Vector _look, Vector _up) {
		this->eye = _eye;
		this->look = _look;
		this->up = _up;
		this->set();
	}

	void set() {
		this->n = this->eye - this->look;
		this->u = up * n;
		this->v = n * u;
		this->n.normalize();
		this->u.normalize();
		this->v.normalize();
		//setMatrix();
	}

	void setMatrix() {
		float m[16];
		m[0] = u.x; m[1] = v.x; m[2] = n.x; m[3] = 0;
		m[4] = u.y; m[5] = v.y; m[6] = n.y; m[7] = 0;
		m[8] = u.z; m[9] = v.z; m[10] = n.z; m[11] = 0;
		m[12] = -(eye/u); m[13] = -(eye/v); m[14] = -(eye/n); m[15] = 1;
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(m);
	}

	void slide(double delU, double delV, double delN) {
		this->eye = this->eye + (this->u*delU + this->v*delV + this->n*delN);
		this->look = this->look + (this->u*delU + this->v*delV + this->n*delN);
		setMatrix();
	}

	void roll(double alpha) {
		Vector x = (u*cos(alpha)) + (v*sin(alpha));
		Vector y = (v*cos(alpha)) - (u*sin(alpha));
		this->u = x;
		this->v = y;
		setMatrix();
	}
	void pitch(double alpha) {
		Vector x = (n*cos(alpha)) + (v*sin(alpha));
		Vector y = (v*cos(alpha)) - (n*sin(alpha));
		this->n = x;
		this->v = y;
		setMatrix();
	}
	void yaw(double alpha) {
		Vector x = (u*cos(alpha)) + (n*sin(alpha));
		Vector y = (n*cos(alpha)) - (u*sin(alpha));
		this->u = x;
		this->n = y;
		setMatrix();
	}
};
#endif
