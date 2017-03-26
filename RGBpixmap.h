#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
using namespace std;

class RGB { 
	public: unsigned char r, g, b;
};

class RGBpixmap {
public:
	int nRows, nCols; 
	RGB* pixel; 
	int readBMPFile(char * fname);
	void makeCheckerboard();
	void setTexture(GLuint textureName);
};

