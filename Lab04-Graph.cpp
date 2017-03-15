
/*
Draw three shape 
Koch shape
Rose shape
Cardioid shape
*/

#include <GL/glut.h>
#include <math.h>

GLfloat xb = -0.669, yb = 0.4599;
int n = 0;

void kock(GLfloat dir, GLfloat len, GLint iter) {
	GLdouble dirRad = 0.0174533 * dir;
	GLfloat xa = xb + len * cos(dirRad);
	GLfloat ya = yb + len * sin(dirRad);
	if (iter == 0) {
		glVertex2f(xb, yb);
		glVertex2f(xa, ya);
		xb = xa;
		yb = ya;
	}
	else {
		iter--;
		kock(dir, len, iter);
		dir += 60.0;
		kock(dir, len, iter);
		dir -= 120.0;
		kock(dir, len, iter);
		dir += 60.0;
		kock(dir, len, iter);
	}
}

void kochDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	
	kock(0.0, 0.05, 3);
	kock(-120.0, 0.05, 3);
	kock(120.0, 0.05, 3);

	glEnd();
	glFlush();
}

void cardioidDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	static const float r = 0.3f;
	static const float pi = 3.1415926535897932384626433832795029f;
	for (float angle = 0.0f; angle < (pi * 2.0f); angle += 0.005f)
	{
		float x = -( 2.0f * r * cos(angle) * (1.0f + cos(angle)) - 0.5);
		float y = 2.0f * r * sin(angle) * (1.0f + cos(angle));
		glVertex3f(x, y, 0.0f);
	}
	glEnd();
	glFlush();
}

void roseDisplay() {
	int n = 4;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	
	static const float r = 0.3f;
	static const float pi = 3.1415926535897932384626433832795029f;
	for (float angle = 0.0f; angle < (pi * 2.0f); angle += 0.005f)
	{
		float x = 0.9 * cos(n*angle)*cos(angle);
		float y = 0.9 * cos(n*angle)*sin(angle);
		glVertex3f(x, y, 0.0f);
	}
	glEnd();
	glFlush();
}

void displayFunction() {
	if (n == 0) {
		kochDisplay();
	}
	else if (n == 1) {
		roseDisplay();
	}
	else {
		cardioidDisplay();
	}
}

void mouseFunction(int button, int state, int x, int y) {
	if (state != GLUT_UP) {
		return;
	}
	n = (n + 1) % 3;
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(670, 670);
	glutInitWindowPosition(1, 1);
	glutCreateWindow("Click Mouse To Change Between Koch Shape, Rose Shape and Cardioid");
	glutDisplayFunc(displayFunction);
	glutMouseFunc(mouseFunction);
	glutMainLoop();
}