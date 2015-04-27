#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include <GLUT/glut.h>
using namespace std;
#include "includes/Camera.h"
#include "includes/Vector.h"
#include "includes/Color.h"

#define BLACK 0, 0, 0
#define WHITE 1, 1, 1
#define RED 1, 0, 0
#define GREEN 0, 1, 0
#define BLUE 0, 0, 1
#define POINT(v) v.x, v.y, v.z
#define COLOR(v) v.r, v.g, v.b
const float DEG2RAD = 3.14159/180;
const double delta = 5;
const double delAlpha = .05;
const double pi = acos(-1.0);

Camera cam(Vector(10, 0, 400), Vector(0, 0, 0), Vector(0, 0, 1));

#include "includes/listeners.h"
#include "includes/dip.h"


void drawPlane(Vector a, Vector b, Vector c, Vector d, Color cl) {
	glColor3f(COLOR(cl));
	glBegin(GL_QUADS); {
		glVertex3f(POINT(a));
		glVertex3f(POINT(b));
		glVertex3f(POINT(c));
		glVertex3f(POINT(d));
	} glEnd();
}

void drawOpenBox(Vector points[8], Color c) {
	drawPlane(points[0], points[1], points[5], points[4], c*1);
	drawPlane(points[1], points[2], points[6], points[5], c*.8);
	drawPlane(points[2], points[3], points[7], points[5], c*.6);
	drawPlane(points[0], points[3], points[7], points[4], c*.4);
}

void getPoints(Vector center, double radius, double alpha, double width, double thickness, Vector *points) {	
	points[0] = Vector(0, radius*cos(alpha), radius*sin(alpha));
	Vector widthVector = center - points[0];
	widthVector.normalize();
	widthVector = widthVector * width;
	points[3] = points[0] + widthVector;
	points[1] = points[0] + Vector(thickness, 0, 0);
	points[2] = points[3] + Vector(thickness, 0, 0);
}

void debugPoints(Vector points[8]) {
	for (int i = 0; i < 8; i++) {
		Color c = Color(BLUE)*((i+1)/8.0);
		glColor3f(COLOR(c));
		glPointSize(3.0);
		glBegin(GL_POINTS); {
			glVertex3f(POINT(points[i]));
		} glEnd();
	}
}

void drawCircularPiller(Vector center, double radius, double width, double thickness, int sections, int from, int to, Color c, Vector ret[8], int draw) {
	double del = 2*acos(-1.0)/sections;
	for (int i = from; i <= to; i++) {
		double alpha = i*del;
		double beta = ((i+1)%sections)*del;
		Vector points[8];
		getPoints(center, radius, alpha,  width, thickness, points);
		getPoints(center, radius, beta, width, thickness, points+4);
		for (int j = 0; j < 4 && draw == 0; j++) {
			if (i == from) {
				ret[j] = points[j];
			} else if (i == to) {
				ret[j+4] = points[j+4];
				//cout << "***** OK *****" << endl;
			}
		}
		if (draw) {
			drawOpenBox(points, c);
		}
	}
}

Vector drawTriangularConnector(int draw, int o) {
	Vector a(o*17, 60, -10);
	Vector b(o*15, 62.5, -10);
	Vector u = Vector(o*3, 5, 0);
	u.normalize();
	Vector c = b + (u*26);
	Vector d = a + (u*26);
	double z1 = 100, z2 = 10;
	u = Vector(-o*3, -5, 0);
	u.normalize();
	Vector e = a + (u*45) + Vector(0, 0, z1);
	Vector f = b + (u*45) + Vector(0, 0, z1);
	Vector g = f+Vector(0, 0, z2);
	Vector h = e+Vector(0, 0, z2);
	Vector points[8] = {a, b, c, d, e, f, g, h};
	if (draw) {
		drawOpenBox(points, Color(WHITE));
	}
	return e;
}

void drawUpperConnector(Vector *ret, int draw, int o) {
	Vector points[8];
	for (int i = 0; i < 4; i++){
		points[i] = ret[i];
	}
	double d = sqrt(10.25)/2*cos(atan(4/3.0));
	Vector u(-o*10, 35), v(0, 35), w(-o*16, 43);
	Vector p = v-u, q = w-u;
	p.normalize();
	q.normalize();
	points[7] = u + (p*d) + Vector(0, 0, 227.5 + 25); 
	points[6] = v + (p*d) + Vector(0, 0, 227.5 + 25);
	u = Vector(-o*5, 35), v = Vector(0, 35), w = Vector(-o*11, 43);
	p = v-u, q = w-u;
	p.normalize();
	q.normalize();
	points[4] = u + (p*d) + Vector(0, 0, 227.5+45);
	points[5] = v + (p*d) + Vector(0, 0, 227.5+45);
	if (draw) {
		drawOpenBox(points, Color(WHITE));
	}
}

void drawCurve(int o) {
	Vector points[8];
	drawCircularPiller(Vector(0, 0, 0), 140, 5, o*3.2, 64, -6, 4, Color(1, 0, 0), points, 0);
	Vector r = drawTriangularConnector(0, o);
	for (int i = 0; i < 8; i++) {
		points[i].rotate(pi-o*atan(4.0/3), Vector(0, 0, 1));
	}
	Vector t = r - points[0];
	glPushMatrix(); {
		glTranslatef(POINT(t));
		glRotatef(pi/DEG2RAD-o*atan(4.0/3)/DEG2RAD, 0, 0, 1);
		drawCircularPiller(Vector(0, 0, 0), 140, 5, o*3.2, 64, -6, 4, Color(1, 0, 0), points, 1);
	} glPopMatrix();
	drawTriangularConnector(1, o);
	for (int i = 0; i < 8; i++) {
		points[i] = points[i] + t;
	}
	drawUpperConnector(points+4, 1, o);

}

void display() {

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera is looking?
	//3. Which direction is the camera's UP direction?

	/****************************
	/ Add your objects from here
	****************************/
	//add objects
	drawAxes();
	drawGrid();
    drawBase();
    drawPiller();
	drawCurve(-1);
	drawCurve(1);
	//rotate this rectangle around the Z axis	
	glFlush();
	//////// ------ NOTE ---- ORDER matters. compare last two spheres!

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate() {
	//MISSING SOMETHING? -- YES: add the following
	glutPostRedisplay();	//this will call the display AGAIN
}

void init(){
	//codes for initialization
	//clear the screen
	glClearColor(BLACK, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(70,	1,	0.1,	10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("S. Tower");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	//ADD keyboard listeners:
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	//ADD mouse listeners:
	glutMouseFunc(mouseListener);
	//Camera cam(Vector(100, 100, 100), Vector(0, 0, 0), Vector(0, 0, 1));
	cam.setMatrix();
	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
