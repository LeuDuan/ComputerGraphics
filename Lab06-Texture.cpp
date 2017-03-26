#include "RGBpixmap.h"

RGBpixmap pix[6]; 
float xSpeed = 0.04, ySpeed = 0.03, xAngle = 0.0, yAngle = 0.0;

void myInit(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // background is white
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	pix[0].readBMPFile("0.bmp");
	pix[0].setTexture(0);
	pix[1].readBMPFile("1.bmp") ; 
	pix[1].setTexture(1);
	pix[2].readBMPFile("2.bmp");
	pix[2].setTexture(2);
	pix[3].readBMPFile("3.bmp");
	pix[3].setTexture(3);
	pix[4].readBMPFile("4.bmp");
	pix[4].setTexture(4);
	pix[5].readBMPFile("5.bmp");
	pix[5].setTexture(5);
							 
	glViewport(0, 0, 640, 480); // set up the viewing system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 640.0 / 640, 1.0, 30.0); // set camera shape
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0.0, 0.0, -4); // move camera back
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPushMatrix();
	glRotated(xAngle, 1.0, 0.0, 0.0); glRotated(yAngle, 0.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, 0); 
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 1); 
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 2);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 3);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 4); 
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 5);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();


	glFlush();
	glPopMatrix();
	glutSwapBuffers();
}

void spinner(void)
{ 
	xAngle += xSpeed; yAngle += ySpeed;
	display();
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Game Of Thrones Cube");
	glutDisplayFunc(display);
	myInit();
	glutIdleFunc(spinner);
	glutMainLoop();
}