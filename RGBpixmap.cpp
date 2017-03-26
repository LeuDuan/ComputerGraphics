#include "RGBpixmap.h"

void RGBpixmap::makeCheckerboard()
{ // make checkerboard pattern
	nRows = nCols = 64;
	pixel = new RGB[1 * nRows * nCols];
	if (!pixel) { cout << "out of memory!”"; return; }
	long count = 0;
	for (int i = 0; i < nRows; i++)
		for (int j = 0; j < nCols; j++)
		{
			int c = (((i / 8) + (j / 8)) % 2) * 255;
			pixel[count].r = c; // red
			pixel[count].g = c; // green
			pixel[count++].b = 0; // blue
		}
}

void RGBpixmap::setTexture(GLuint textureName)
{
	glBindTexture(GL_TEXTURE_2D, textureName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, nCols, nRows, 0, GL_RGB,
		GL_UNSIGNED_BYTE, pixel);
}

int RGBpixmap::readBMPFile(char * fname)
{
	ifstream f(fname, ios::binary);

	// read bmp header
	char *header = new char[54];
	f.read(header, 54);
	nCols = *(int*)&(header[0x12]);
	nRows = *(int*)&(header[0x16]);

	char *rgb = new char[3*nCols*nRows];
	f.read(rgb, 3 * nCols*nRows);
	f.close();
	long count = 0;
	cout << "Count" << f.gcount() << endl;
	cout << "Current:" << f.tellg() << endl;
	pixel = new RGB[nRows*nCols];
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			pixel[count].b = (unsigned char)(rgb[3 * count]);
			pixel[count].g = (unsigned char)(rgb[3 * count+1]);
			pixel[count].r = (unsigned char)(rgb[3 * count+2]);
			count++;
		}
	}

	return 1;
}
