#ifndef FUNCTIONS_H
#define FUNCTIONS_H
void render(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions,GLUquadricObj *quadric)
{
	float vx = x2-x1;
	float vy = y2-y1;
	float vz = z2-z1;

	//handle the degenerate case of z1 == z2 with an approximation
	if(vz == 0)
	    vz = .0001;

	float v = sqrt( vx*vx + vy*vy + vz*vz );
	float ax = 57.2957795*acos( vz/v );
	if ( vz < 0.0 )
	    ax = -ax;
	float rx = -vy*vz;
	float ry = vx*vz;
	glPushMatrix(); {	
		//draw the cylinder body
		glTranslatef( x1,y1,z1 );
		glRotatef(ax, rx, ry, 0.0);
		gluQuadricOrientation(quadric,GLU_OUTSIDE);
		gluCylinder(quadric, radius, radius, v, subdivisions, 1);

		//draw the first cap
		gluQuadricOrientation(quadric,GLU_INSIDE);
		gluDisk( quadric, 0.0, radius, subdivisions, 1);
		glTranslatef( 0,0,v );

		//draw the second cap
		gluQuadricOrientation(quadric,GLU_OUTSIDE);
		gluDisk( quadric, 0.0, radius, subdivisions, 1);
	} glPopMatrix();
}
void drawCylinder(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions)
{
	GLUquadricObj *quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	render(x1,y1,z1,x2,y2,z2,radius,subdivisions,quadric);
	gluDeleteQuadric(quadric);
}

void circle(Vector a, Vector b, Vector c, float &h, float &k, float &r) {
    float bx = a.x, by = a.y;
    float cx = b.x, cy = b.y;
    float dx = c.x, dy = c.y;
    float temp = cx*cx+cy*cy;
    float bc = (bx*bx + by*by - temp)/2.0;
    float cd = (temp - dx*dx - dy*dy)/2.0;
    float det = (bx-cx)*(cy-dy)-(cx-dx)*(by-cy);
    det = 1/det;
    h = (bc*(cy-dy)-cd*(by-cy))*det;
    k = ((bx-cx)*cd-(cx-dx)*bc)*det;
    cx = h; cy = k;
    r = sqrt((cx-bx)*(cx-bx)+(cy-by)*(cy-by));
}
#endif
