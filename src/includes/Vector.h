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

	void rotate(double angle, Vector r) {
		float u = r.x, v = r.y, w = r.z;
		float L = (u*u + v * v + w * w);
	    float u2 = u * u;
	    float v2 = v * v;
	    float w2 = w * w; 
		
		float rotationMatrix[4][4];
			 
	    rotationMatrix[0][0] = (u2 + (v2 + w2) * cos(angle)) / L;
	    rotationMatrix[0][1] = (u * v * (1 - cos(angle)) - w * sqrt(L) * sin(angle)) / L;
	    rotationMatrix[0][2] = (u * w * (1 - cos(angle)) + v * sqrt(L) * sin(angle)) / L;
	    rotationMatrix[0][3] = 0.0; 
	 
	    rotationMatrix[1][0] = (u * v * (1 - cos(angle)) + w * sqrt(L) * sin(angle)) / L;
	    rotationMatrix[1][1] = (v2 + (u2 + w2) * cos(angle)) / L;
	    rotationMatrix[1][2] = (v * w * (1 - cos(angle)) - u * sqrt(L) * sin(angle)) / L;
	    rotationMatrix[1][3] = 0.0; 
	 
	    rotationMatrix[2][0] = (u * w * (1 - cos(angle)) - v * sqrt(L) * sin(angle)) / L;
	    rotationMatrix[2][1] = (v * w * (1 - cos(angle)) + u * sqrt(L) * sin(angle)) / L;
	    rotationMatrix[2][2] = (w2 + (u2 + v2) * cos(angle)) / L;
	    rotationMatrix[2][3] = 0.0; 
	 
	    rotationMatrix[3][0] = 0.0;
	    rotationMatrix[3][1] = 0.0;
	    rotationMatrix[3][2] = 0.0;
	    rotationMatrix[3][3] = 1.0;

	    float inputMatrix[4][1];
	    float outputMatrix[4][1];

	    inputMatrix[0][0] = this->x;
	    inputMatrix[1][0] = this->y;
	    inputMatrix[2][0] = this->z;
	    inputMatrix[3][0] = 1.0; 

	    for(int i = 0; i < 4; i++) {
        	for(int j = 0; j < 1; j++) {
            	outputMatrix[i][j] = 0;
            	for(int k = 0; k < 4; k++){
            	    outputMatrix[i][j] += rotationMatrix[i][k] * inputMatrix[k][j];
          		}
        	}
    	}

    	this->x = outputMatrix[0][0];
    	this->y = outputMatrix[1][0];
    	this->z = outputMatrix[2][0];
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
