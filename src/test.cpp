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

Camera cam(Vector(300, 0, 150), Vector(0, 0, 150), Vector(0, 0, 1));

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

void drawCircularPiller(Vector center, double radius, double width, double thickness, int sections, int from, int to, Color c) {
	double del = 2*acos(-1.0)/sections;
	for (int i = from; i <= to; i++) {
		double alpha = i*del;
		double beta = ((i+1)%sections)*del;
		Vector points[8];
		getPoints(center, radius, alpha,  width, thickness, points);
		getPoints(center, radius, beta, width, thickness, points+4);
		drawOpenBox(points, c);
	}
}

void drawTriangularConnector() {
	Vector a(17, 60, -10);
	Vector b(15, 62.5, -10);
	Vector u = Vector(3, 5, 0);
	u.normalize();
	Vector c = b + (u*26);
	Vector d = a + (u*26);
	double z1 = 60, z2 = 10;
	Vector f(0, 53, z1);
	Vector e = f+Vector(2, -2.5, 0);
	Vector g = f+Vector(0, 0, z2);
	Vector h = e+Vector(0, 0, z2);
	Vector points[8] = {a, b, c, d, e, f, g, h};
	drawOpenBox(points, Color(WHITE));
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
	glPushMatrix(); {
		glRotatef(pi/DEG2RAD, 0, 0, 1);
		glRotatef(1.03/DEG2RAD, 0, 0, 1);
		glTranslatef(0, -140, 160);
		double val = 2;
		glTranslatef(-50/val, 30/val, 0);
		drawCircularPiller(Vector(0, 0, 0), 160, 5, 3.2, 64, -10, 6, Color(1, 0, 0));
	} glPopMatrix();
	drawTriangularConnector();
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
