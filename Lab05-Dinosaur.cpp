#include <string>
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <math.h>

using namespace std;
int nlines;
double** lines;
int* numPerLine;
int n = 2;
string filename = "dinosaur.dat";
double c[3][3] = { {0.0f, 1.0f, 0.0f},{1.0f, 0.0f, 0.0f},{0.0f,0.0f, 1.0f} };
bool readAlready = false;
int mode = 0;
void displayDinosaur() {
	if (!readAlready) {
		ifstream dat(filename);

		dat >> nlines;

		lines = new double*[nlines];
		numPerLine = new int[nlines];
		for (int i = 0; i < nlines; i++) {
			dat >> numPerLine[i];
			lines[i] = new double[numPerLine[i] * 2];
			for (int j = 0; j < 2 * numPerLine[i]; j++) {
				dat >> lines[i][j];
			}
		}
		readAlready = true;
	}
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(c[n][0], c[n][1], c[n][2]);
	for (int i = 0; i < nlines; i++) {
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j < numPerLine[i]; j++) {
			float x = 0.002* lines[i][2 * j] - 0.9;
			float y = 0.002* lines[i][2 * j + 1] - 0.5;
			glVertex2f(x, y);
		}
		glEnd();
	}
	glFlush();
}
void displayFunction() {
	double scale = 0.2;
	double moveX = 0.0;
	double moveY = 0.0;
	
	double xStart = -4;
	double xEnd = 5;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
	glColor3f(0, 1, 0);
	for (double x = xStart; x < xEnd; x += 0.1) {
		double y = (x*x*x + 2 * x*x + 3)*scale;
		glVertex2f(x*scale - moveX, y*scale-moveY);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1, 0, 0);
	for (double x = xStart; x < xEnd; x += 0.1) {
		double y = (2*sin(x) + 0.5*cos(x))*scale;
		glVertex2f(x*scale - moveX, y*scale - moveY);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1, 1, 1);
	glVertex2f(xStart*scale-moveX - 0.1, 0 - moveY);
	glVertex2f(xEnd*scale - moveX + 0.1, 0 - moveY);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1, 1, 1);
	glVertex2f( - moveX , 1.5 - moveY);
	glVertex2f(- moveX , -1 - moveY);
	glEnd();
	
	glFlush();
}
void mouseFunction(int button, int state, int x, int y) {
	if (state != GLUT_UP) {
		return;
	}
	mode = (mode + 1) % 2;
	glutPostRedisplay();
}

void display() {
	if (mode == 0) {
		displayDinosaur();
	}
	else {
		displayFunction();
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(670, 670);
	glutInitWindowPosition(1, 1);
	glutCreateWindow("Click Mouse To Change Between Dinosaur and Graphs");
	glutDisplayFunc(display);
	glutMouseFunc(mouseFunction);
	glutMainLoop();
}