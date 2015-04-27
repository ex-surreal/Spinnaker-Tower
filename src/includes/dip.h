#ifndef DIP_H
#define DIP_H
int drawgrid;
int drawaxes = 1;


struct point
{
	double x,y,z;
};


void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);
			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);
			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}


void drawSquare(float a)
{
	glBegin(GL_QUADS);{
		glVertex3f( a, a,0);
		glVertex3f( a,-a,0);
		glVertex3f(-a,-a,0);
		glVertex3f(-a, a,0);
	}glEnd();
}

//draws half sphere
//draws half sphere
void drawsphere(float radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=sqrt(radius*radius-h*h);
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}

	}
	for(i=0;i<stacks;i++)
	{
		for(j=0;j<slices;j++)
		{
			glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

			}glEnd();
		}

	}
}

void drawCylindar(float radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	double factor=1;

	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		//r=sqrt(radius*radius-h*h);
		r= radius*factor;
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			//points[i][j].y=radius;
			points[i][j].z=h;
		}
       // factor-=.02;
	}
	for(i=0;i<stacks;i++)
	{
		for(j=0;j<slices;j++)
		{
			glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
			glBegin(GL_QUADS);{
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

			}glEnd();
		}

	}
}

void drawCircle(float radius,float degree)
{

    glPushMatrix();{
       //glBegin(GL_LINE_LOOP);
       glPushMatrix();{
           glBegin(GL_POLYGON);{
               glVertex3f(0,0,0);
               for (int i=0; i < degree; i++)
               {
                  float degInRad = i*DEG2RAD;
                  glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius,0);
                 // glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius,-3);
               }
           }
           glEnd();
       }glPopMatrix();

       glPushMatrix();{
            //float degInRad = i*DEG2RAD;
            //glVertex3f(cos(degInRad)*radius,sin(degInRad)*radius,0);
            float degInRad1 ;
            float degInRad2 ;
            for(int i=2;i<degree;i++)
            {
                int j=i-1;
                 degInRad1 = i*DEG2RAD;
                 degInRad2 = j*DEG2RAD;
                glBegin(GL_POLYGON);{
                glVertex3f(cos(degInRad1)*radius,sin(degInRad1)*radius,0);
                glVertex3f(cos(degInRad2)*radius,sin(degInRad2)*radius,0);
                glVertex3f(cos(degInRad2)*radius,sin(degInRad2)*radius,-3);
                glVertex3f(cos(degInRad1)*radius,sin(degInRad1)*radius,-3);
                }glEnd();
            }
       }
       glPopMatrix();
   }glPopMatrix();
}

void RenderSineWave()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);  // clear background with black
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    double w = glutGet( GLUT_WINDOW_WIDTH );
    double h = glutGet( GLUT_WINDOW_HEIGHT );
    double ar = w / h;
    glOrtho( -360 * ar, 360 * ar, -120, 120, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glPointSize(10);
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_POINTS);
    for(int i=0;i<361;i=i+5)
    {
        float x = (float)i;
        float y = 100.0 * sin(i *(6.284/360.0));
        glVertex2f(x,y);
    }
    glEnd();

    glutSwapBuffers();
}

void drawFish() {
    int mult= 1;

    glPushMatrix();{

    glBegin(GL_POLYGON);{
        glVertex3f(mult*0, mult*0,mult*0);
		glVertex3f( mult*20,mult*0,mult*0);
		glVertex3f(mult*40,mult*40,mult*0);
		glVertex3f(mult*35,mult* 45,mult*0);
		glVertex3f(mult*28, mult*60,mult*0);
		glVertex3f(mult*0, mult*60,mult*0);
    }glEnd();

     glBegin(GL_TRIANGLES);{
        glVertex3f(mult*28, mult*60,mult*0);
		glVertex3f( mult*20,mult*65,mult*0);
		glVertex3f(mult*17,mult*60,mult*0);

    }glEnd();

    glBegin(GL_POLYGON);{
        glVertex3f(mult*17, mult*60,mult*0);
		glVertex3f( mult*15,mult*62.5,mult*0);
		glVertex3f(mult*0,mult*62.5,mult*0);
		glVertex3f(mult*0,mult*60,mult*0);

    }glEnd();

    glBegin(GL_POLYGON);{
        glVertex3f(mult*15, mult*62.5,mult*0);
		glVertex3f( mult*25,mult*80,mult*0);
		glVertex3f( mult*0,mult*80,mult*0);
		glVertex3f( mult*0,mult*62.5,mult*0);
    }glEnd();


    //lenja begins

    glBegin(GL_TRIANGLES);{
        glVertex3f(mult*25, mult*80,mult*0);
		glVertex3f( mult*20,mult*82.5,mult*0);
		glVertex3f(mult*20,mult*80,mult*0);

    }glEnd();


    glBegin(GL_POLYGON);{
        glVertex3f(mult*20, mult*80,mult*0);
		glVertex3f( mult*20,mult*82.5,mult*0);
		glVertex3f(mult*15,mult*84.5,mult*0);
		glVertex3f(mult*15,mult*80,mult*0);

    }glEnd();

    glBegin(GL_POLYGON);{
        glVertex3f(mult*15, mult*80,mult*0);
		glVertex3f( mult*15,mult*84.5,mult*0);
		glVertex3f(mult*10,mult*86,mult*0);
		glVertex3f(mult*10,mult*80,mult*0);

    }glEnd();

    glBegin(GL_POLYGON);{
        glVertex3f(mult*10, mult*80,mult*0);
		glVertex3f( mult*10,mult*86,mult*0);
		glVertex3f(mult*5,mult*87,mult*0);
		glVertex3f(mult*5,mult*80,mult*0);

    }glEnd();

    glBegin(GL_POLYGON);{
        glVertex3f(mult*5, mult*80,mult*0);
		glVertex3f( mult*5,mult*87,mult*0);
		glVertex3f(mult*0,mult*87,mult*0);
		glVertex3f(mult*0,mult*80,mult*0);

    }glEnd();


    }
    glPopMatrix();
}


void drawfishbones()
{
    int mult = 1;
      glPushMatrix();{
        glBegin(GL_POLYGON);{
            glVertex3f(mult*0, mult*0,mult*0);
            glVertex3f( mult*20,mult*0,mult*0);
            glVertex3f(mult*20,mult*00,mult*-10);
            glVertex3f(mult*0,mult*0,mult*-10);
        }glEnd();
    }glPopMatrix();

    glPushMatrix();{
        glBegin(GL_POLYGON);{
            glVertex3f(mult*0, mult*0,mult*0);
            glVertex3f( mult*-20,mult*0,mult*0);
            glVertex3f(mult*-20,mult*00,mult*-10);
            glVertex3f(mult*0,mult*0,mult*-10);
        }glEnd();

    }glPopMatrix();

    glPushMatrix();{
        glBegin(GL_POLYGON);{
            glVertex3f(mult*20, mult*0,mult*0);
            glVertex3f( mult*40,mult*40,mult*0);
            glVertex3f(mult*40,mult*40,mult*-10);
            glVertex3f(mult*20,mult*0,mult*-10);
        }glEnd();

    }glPopMatrix();

    glPushMatrix();{
        glBegin(GL_POLYGON);{
           // glColor3f(1,0,0);
            glVertex3f(mult*-20, mult*0,mult*0);
            glVertex3f( mult*-40,mult*40,mult*0);
            glVertex3f(mult*-40,mult*40,mult*-10);
            glVertex3f(mult*-20,mult*0,mult*-10);
           // glColor3f(1,0,0);
        }glEnd();

    }glPopMatrix();

    glPushMatrix();{
         glBegin(GL_POLYGON);{
           // glColor3f(1,0,0);
            glVertex3f(mult*40, mult*40,mult*0);
            glVertex3f( mult*35,mult*45,mult*0);
            glVertex3f(mult*35,mult*45,mult*-10);
            glVertex3f(mult*40,mult*40,mult*-10);
           // glColor3f(1,0,0);
        }glEnd();


        glBegin(GL_POLYGON);{
           // glColor3f(1,0,0);
            glVertex3f(mult*-40, mult*40,mult*0);
            glVertex3f( mult*-35,mult*45,mult*0);
            glVertex3f(mult*-35,mult*45,mult*-10);
            glVertex3f(mult*-40,mult*40,mult*-10);
           // glColor3f(1,0,0);
        }glEnd();

    }glPopMatrix();

    glPushMatrix();{
         glBegin(GL_POLYGON);{
           // glColor3f(1,0,0);
            glVertex3f(mult*35, mult*45,mult*0);
            glVertex3f( mult*28,mult*60,mult*0);
            glVertex3f(mult*28,mult*60,mult*-10);
            glVertex3f(mult*35,mult*45,mult*-10);

        }glEnd();


        glBegin(GL_POLYGON);{
           // glColor3f(1,0,0);
            glVertex3f(mult*-35, mult*45,mult*0);
            glVertex3f( mult*-28,mult*60,mult*0);
            glVertex3f(mult*-28,mult*60,mult*-10);
            glVertex3f(mult*-35,mult*45,mult*-10);

        }glEnd();

    }glPopMatrix();

    glPushMatrix();{
        glBegin(GL_POLYGON);{
           // glColor3f(1,0,0);
            glVertex3f(mult*28, mult*60,mult*0);
            glVertex3f( mult*20,mult*65,mult*0);
            glVertex3f(mult*20,mult*65,mult*-10);
            glVertex3f(mult*28,mult*60,mult*-10);

        }glEnd();


        glBegin(GL_POLYGON);{
           // glColor3f(1,0,0);
            glVertex3f(mult*-28, mult*60,mult*0);
            glVertex3f( mult*-20,mult*65,mult*0);
            glVertex3f(mult*-20,mult*65,mult*-10);
            glVertex3f(mult*-28,mult*60,mult*-10);

        }glEnd();

    }glPopMatrix();

    glPushMatrix();{
        glBegin(GL_POLYGON);{
           // glColor3f(1,0,0);
            glVertex3f(mult*25, mult*80,mult*0);
            glVertex3f( mult*20,mult*82.5,mult*0);
            glVertex3f(mult*15,mult*84.5,mult*0);
            glVertex3f(mult*10,mult*86,mult*0);
            glVertex3f(mult*5,mult*87,mult*0);
            glVertex3f(mult*0,mult*87,mult*0);
            glVertex3f(mult*0,mult*87,mult*-10);
            glVertex3f(mult*5,mult*87,mult*-10);
            glVertex3f(mult*10,mult*86,mult*-10);
            glVertex3f(mult*15,mult*84.5,mult*-10);
            glVertex3f( mult*20,mult*82.5,mult*-10);
            glVertex3f(mult*25, mult*80,mult*-10);
        }glEnd();


        glBegin(GL_POLYGON);{
           // glColor3f(1,0,0);
            glVertex3f(mult*-25, mult*80,mult*0);
            glVertex3f( mult*-20,mult*82.5,mult*0);
            glVertex3f(mult*-15,mult*84.5,mult*0);
            glVertex3f(mult*-10,mult*86,mult*0);
            glVertex3f(mult*-5,mult*87,mult*0);
            glVertex3f(mult*-0,mult*87,mult*0);
            glVertex3f(mult*-0,mult*87,mult*-10);
            glVertex3f(mult*-5,mult*87,mult*-10);
            glVertex3f(mult*-10,mult*86,mult*-10);
            glVertex3f(mult*-15,mult*84.5,mult*-10);
            glVertex3f( mult*-20,mult*82.5,mult*-10);
            glVertex3f(mult*-25, mult*80,mult*-10);
        }glEnd();

    }glPopMatrix();
}

void drawPiller()
{

        glPushMatrix();{
           // glTranslatef(4,-10,0);

           //base polygons
            glBegin(GL_POLYGON);{
                glColor3f(1,0,0);


                glVertex3f(8,43,0.5);
                glVertex3f(14,35,0.5);
                glVertex3f(24,35,0.5);
                glVertex3f(30,43,0.5);
                glVertex3f(24,51,0.5);
                glVertex3f(13,51,0.5);

            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,0,0);


                glVertex3f(-8,43,0.5);
                glVertex3f(-14,35,0.5);
                glVertex3f(-24,35,0.5);
                glVertex3f(-30,43,0.5);
                glVertex3f(-24,51,0.5);
                glVertex3f(-13,51,0.5);

            }glEnd();
            //base polygons

            //first pillar
            glBegin(GL_POLYGON);{
                glColor3f(1,0,0);
                glVertex3f(0,43,0.5+160);
                glVertex3f(6,35,0.5+160);
                glVertex3f(16,35,0.5+160);
                glVertex3f(22,43,0.5+160);
                glVertex3f(16,51,0.5+160);
                glVertex3f(6,51,0.5+160);

            }glEnd();


            glBegin(GL_POLYGON);{
                glColor3f(1,0,0);
                glVertex3f(-0,43,0.5+160);
                glVertex3f(-6,35,0.5+160);
                glVertex3f(-16,35,0.5+160);
                glVertex3f(-22,43,0.5+160);
                glVertex3f(-16,51,0.5+160);
                glVertex3f(-6,51,0.5+160);

            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);
                glVertex3f(8,43,0.5);
                glVertex3f(14,35,0.5);
                glVertex3f(6,35,0.5+160);
                glVertex3f(0,43,0.5+160);
            }glEnd();


             glBegin(GL_POLYGON);{
                glColor3f(0,0,1);
                glVertex3f(-8,43,0.5);
                glVertex3f(-14,35,0.5);
                glVertex3f(-6,35,0.5+160);
                glVertex3f(-0,43,0.5+160);

            }glEnd();

             glBegin(GL_POLYGON);{
                glColor3f(0,0,1);

                glVertex3f(14,35,0.5);
                glVertex3f(24,35,0.5);
                glVertex3f(16,35,0.5+160);
                glVertex3f(6,35,0.5+160);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);

                glVertex3f(-14,35,0.5);
                glVertex3f(-24,35,0.5);
                glVertex3f(-16,35,0.5+160);
                glVertex3f(-6,35,0.5+160);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);

                glVertex3f(24,35,0.5);
                glVertex3f(30,43,0.5);
                glVertex3f(22,43,0.5+160);
                glVertex3f(16,35,0.5+160);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);

                glVertex3f(-24,35,0.5);
                glVertex3f(-30,43,0.5);
                glVertex3f(-22,43,0.5+160);
                glVertex3f(-16,35,0.5+160);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);

                glVertex3f(30,43,0.5);
                glVertex3f(24,51,0.5);
                glVertex3f(16,51,0.5+160);
                glVertex3f(22,43,0.5+160);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);

                glVertex3f(-30,43,0.5);
                glVertex3f(-24,51,0.5);
                glVertex3f(-16,51,0.5+160);
                glVertex3f(-22,43,0.5+160);
            }glEnd();


            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);

                glVertex3f(24,51,0.5);
                glVertex3f(13,51,0.5);
                glVertex3f(6,51,0.5+160);
                glVertex3f(16,51,0.5+160);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);

                glVertex3f(-24,51,0.5);
                glVertex3f(-13,51,0.5);
                glVertex3f(-6,51,0.5+160);
                glVertex3f(-16,51,0.5+160);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);

                glVertex3f(8,43,0.5);
                glVertex3f(13,51,0.5);
                glVertex3f(6,51,0.5+160);
                glVertex3f(0,43,0.5+160);

            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);

                glVertex3f(-8,43,0.5);
                glVertex3f(-13,51,0.5);
                glVertex3f(-6,51,0.5+160);
                glVertex3f(-0,43,0.5+160);

            }glEnd();

            // end of first pillar

            //starting of second pillar

            glBegin(GL_POLYGON);{
                glColor3f(1,0,0);
                glVertex3f(-10,35,160.5+67);
                glVertex3f(10,35,160.5+67);
                glVertex3f(16,43,160.5+67);
                glVertex3f(10,51,160.5+67);
                glVertex3f(-10,51,160.5+67);
                glVertex3f(-16,43,160.5+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);
                glVertex3f(6,35,160.5);
                glVertex3f(16,35,160.5);
                glVertex3f(10,35,160.5+67);
                glVertex3f(0,35,160.5+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,0,1);
                glVertex3f(-6,35,160.5);
                glVertex3f(-16,35,160.5);
                glVertex3f(-10,35,160.5+67);
                glVertex3f(0,35,160.5+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,0,1);
                glVertex3f(16,35,160.5);
                glVertex3f(22,43,160.5);
                glVertex3f(16,43,160.5+67);
                glVertex3f(10,35,160.5+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(0,0,1);
                glVertex3f(-16,35,160.5);
                glVertex3f(-22,43,160.5);
                glVertex3f(-16,43,160.5+67);
                glVertex3f(-10,35,160.5+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,1,1);
                glVertex3f(22,43,160.5);
                glVertex3f(16,51,160.5);

                glVertex3f(10,51,160.5+67);
                glVertex3f(16,43,160.5+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,1,1);
                glVertex3f(-22,43,160.5);
                glVertex3f(-16,51,160.5);

                glVertex3f(-10,51,160.5+67);
                glVertex3f(-16,43,160.5+67);
            }glEnd();


            glBegin(GL_POLYGON);{
                glColor3f(1,0,1);
                glVertex3f(16,51,160.5);
                glVertex3f(6,51,160.5);

                glVertex3f(0,51,160.5+67);
                glVertex3f(10,51,160.5+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,0,1);
                glVertex3f(-16,51,160.5);
                glVertex3f(-6,51,160.5);

                glVertex3f(0,51,160.5+67);
                glVertex3f(-10,51,160.5+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(.5,.5,.5);
                glVertex3f(6,35,160.5);
                glVertex3f(-6,35,160.5);
                glVertex3f(0,35,160.5+67);

            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(.5,.5,.5);
                glVertex3f(6,51,160.5);
                glVertex3f(-6,51,160.5);
                glVertex3f(0,51,160.5+67);

            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,0,0);
                glVertex3f(5,35,0.5+160+67+45);
                glVertex3f(11,43,0.5+160+45+67);
                glVertex3f(5,51,0.5+160+45+67);
                glVertex3f(-5,51,0.5+160+45+67);
                glVertex3f(-11,43,0.5+160+45+67);
                glVertex3f(-5,35,0.5+160+45+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,0,1);
                glVertex3f(-10,35,0.5+160+67);
                glVertex3f(10,35,0.5+160+67);
                glVertex3f(5,35,0.5+160+45+67);
                glVertex3f(-5,35,0.5+160+45+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,1,1);
                glVertex3f(10,35,0.5+160+67);
                glVertex3f(16,43,0.5+160+67);
                glVertex3f(11,43,0.5+160+45+67);
                glVertex3f(5,35,0.5+160+45+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,1,0);
                glVertex3f(16,43,0.5+160+67);
                glVertex3f(10,51,0.5+160+67);
                glVertex3f(5,51,0.5+160+45+67);
                glVertex3f(11,43,0.5+160+45+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,1,1);
                glVertex3f(10,51,0.5+160+67);
                glVertex3f(-10,51,0.5+160+67);
                glVertex3f(-5,51,0.5+160+45+67);
                glVertex3f(5,51,0.5+160+45+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,1,0);
                glVertex3f(-10,51,0.5+160+67);
                glVertex3f(-16,43,0.5+160+67);
                glVertex3f(-11,43,0.5+160+45+67);
                glVertex3f(-5,51,0.5+160+45+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,1,1);
                glVertex3f(16,43,0.5+160+67);
                glVertex3f(10,51,0.5+160+67);
                glVertex3f(5,51,0.5+160+45+67);
                glVertex3f(11,43,0.5+160+45+67);
            }glEnd();


            glBegin(GL_POLYGON);{
                glColor3f(1,1,1);
                glVertex3f(-16,43,0.5+160+67);
                glVertex3f(-10,35,0.5+160+67);
                glVertex3f(-5,35,0.5+160+45+67);
                glVertex3f(-11,43,0.5+160+45+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,1,0);
                glVertex3f(16,43,0.5+160+67);
                glVertex3f(10,51,0.5+160+67);
                glVertex3f(5,51,0.5+160+45+67);
                glVertex3f(11,43,0.5+160+45+67);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,0,0);
                glVertex3f(-.6,43,0.5+160+67+45+90);
                glVertex3f(.6,43,0.5+160+67+45+90);
                glVertex3f(1.2,43.8,0.5+160+67+45+90);
                glVertex3f(.6,44.6,0.5+160+67+45+90);
                glVertex3f(-.6,44.6,0.5+160+67+45+90);
                glVertex3f(-1.2,43.8,0.5+160+67+45+90);
            }glEnd();


            glBegin(GL_POLYGON);{
                glColor3f(1,1,0);
                glVertex3f(-5,35,0.5+160+67+45);
                glVertex3f(5,35,0.5+160+67+45);
                glVertex3f(.6,43,0.5+160+45+67+90);
                glVertex3f(-.6,43,0.5+160+45+67+90);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,0,0);
                glVertex3f(5,35,0.5+160+67+45);
                glVertex3f(11,43,0.5+160+67+45);
                glVertex3f(1.2,43.8,0.5+160+45+67+90);
                glVertex3f(.6,43,0.5+160+45+67+90);
            }glEnd();




            glBegin(GL_POLYGON);{
                glColor3f(1,1,0);
                glVertex3f(11,43,0.5+160+67+45);
                glVertex3f(5,51,0.5+160+67+45);
                glVertex3f(.6,44.6,0.5+160+45+67+90);
                glVertex3f(1.2,43.8,0.5+160+45+67+90);
            }glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,0,1);
                glVertex3f(5,51,0.5+160+67+45);
                glVertex3f(-5,51,0.5+160+67+45);
                glVertex3f(-.6,44.6,0.5+160+45+67+90);
                glVertex3f(.6,44.6,.5+160+45+67+90);
            }glEnd();

                        glBegin(GL_POLYGON);{
                glColor3f(1,0,0);
                glVertex3f(-5,51,0.5+160+67+45);
                glVertex3f(-11,43,0.5+160+67+45);
                glVertex3f(-1.2,43.8,0.5+160+45+67+90);
                glVertex3f(-.6,44.6,0.5+160+45+67+90);
            }glEnd();

                        glBegin(GL_POLYGON);{
                glColor3f(1,1,0);
                glVertex3f(-5,35,0.5+160+67+45);
                glVertex3f(-11,43,0.5+160+67+45);
                glVertex3f(-1.2,43.8,0.5+160+45+67+90);
                glVertex3f(-.6,43,0.5+160+45+67+90);
            }glEnd();
	    }
	    glPopMatrix();

}


void drawBase()
{
    glPushMatrix();
	{


        //outer half circle
	    glPushMatrix();{

            glBegin(GL_POLYGON);{
                glColor3f(1,0,0);
                glVertex3f(-43,50,-13);
                glVertex3f(-60,85,-13);
                glVertex3f(-50,90,-13);
                glVertex3f(0,50,-13);
                glVertex3f(0,0,-13);
            }
            glEnd();

	        glBegin(GL_POLYGON);{
                glColor3f(1,0,0);
                glVertex3f(50,24,-13);
                glVertex3f(60,27,-13);
                //glVertex3f(70,24,-13);
                glVertex3f(60,35,-13);
                glVertex3f(0,35,-13);
                glVertex3f(0,0,-13);
            }
            glEnd();

            glBegin(GL_POLYGON);{
                glColor3f(1,0,0);
                //glVertex3f(50,24,-13);
                glVertex3f(60,27,-13);
                //glVertex3f(70,24,-13);
                glVertex3f(73,24,-13);
                glVertex3f(73,35,-13);
                glVertex3f(60,35,-13);
            }
            glEnd();

	        glColor3f(1,0,0);
	        glTranslatef(0,0,-13);
	        glTranslatef(0,25,0);
            glRotatef(150,0,0,1);
            drawCircle(50,210);

        }glPopMatrix();

        //inner half circle
	    glPushMatrix();{
	        glColor3f(0,0,1);
	        glTranslatef(0,0,-10);
	        glTranslatef(3,30,0);
            glRotatef(180,0,0,1);

            drawCircle(43,185);
        }glPopMatrix();


        //main part drawing here

        glPushMatrix();{

            glColor3f(1,0,0);
            drawfishbones();
            glColor3f(0,1,0);
            drawFish();
            glRotatef(180,0,1,0);
            drawFish();
        }glPopMatrix();
	    //main part drawing here
	}
	glPopMatrix();
}
#endif
