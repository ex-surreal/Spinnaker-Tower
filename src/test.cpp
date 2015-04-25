#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>

#include<GLUT/glut.h>
using namespace std;
#include "includes/Camera.hpp"
#include "includes/Vector.hpp"

#define BLACK 0, 0, 0
#define WHITE 1, 1, 1
#define RED 1, 0, 0
#define GREEN 0, 1, 0
#define BLUE 0, 0, 1

const double delta = 3;
const double delAlpha = .1;

Camera cam(Vector(0, 200, 0), Vector(0, 0, 0), Vector(0, 0, 1));

void cameraMoveInPlane(int key) {
	switch(key) {
		case GLUT_KEY_DOWN:		//down arrow key
			cam.slide(0, -delta, 0);
			break;
		case GLUT_KEY_UP:		// up arrow key
			cam.slide(0, delta, 0);
			break;
		case GLUT_KEY_RIGHT:
			cam.slide(delta, 0, 0);
			break;
		case GLUT_KEY_LEFT:
			cam.slide(-delta, 0, 0);
			break;
		default:
			break;
	}
}

void cameraRotateAndFB(int key) {
	switch(key){
		case 'f':
			cam.slide(0, 0, -delta);
			break;
		case 'b':
			cam.slide(0, 0, delta);
			break;
		case '.':
			cam.roll(delAlpha);
			break;
		case ',':
			cam.roll(-delAlpha);
			break;
		case 'u':
			cam.pitch(-delAlpha);
			break;
		case 'd':
			cam.pitch(delAlpha);
			break;
		case 'r':
			cam.yaw(delAlpha);
			break;
		case 'l':
			cam.yaw(-delAlpha);
			break;
		default:
			break;
	}
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
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES); {
		glVertex3f(100, 0, 0);
		glVertex3f(-100, 0, 0);
		glVertex3f(0, -100, 0);
		glVertex3f(0, 100, 0);
		glVertex3f(0, 0, 100);
		glVertex3f(0, 0, -100);
	} glEnd();
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

void keyboardListener(unsigned char key, int x, int y) {
	cameraRotateAndFB(key);
}

void specialKeyListener(int key, int x, int y) {
	cameraMoveInPlane(key);
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		default:
			break;
	}
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
