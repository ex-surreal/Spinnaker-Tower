#ifndef LISTNERS_H
#define LISTNERS_H
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
#endif