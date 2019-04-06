#pragma once
#include <vector>
#include "pixel.h"
#include "boxsize.h"
#include "lodepng.h"
#include "box.h"
#include "boxsize.h"

class png
{
public:
	png(const char* path);
	~png();
	void getPixel(int x, int y, pixel &pixel);
	pixel * getPixel(int x, int y);
	pixel * getSample(int x, int y, boxsize * src);
	pixel * getSample(float x, float y, float sizex, float sizey);
	void getDimensions(int *x, int *y) {
		*x = size.sizeX;
		*y = size.sizeY;
	}
	void getDimensions(int &x, int &y) {
		x = size.sizeX;
		y = size.sizeY;
	}
	int getSizeX() { return size.sizeX; }
	int getSizeY() { return size.sizeY; }
	inline int getPixelCount() { return size.sizeX * size.sizeY; }
	inline int get(int x, int y) { return ((y * size.sizeX) + x); }
private:
	int load(const char* path);
	void convert(std::vector<unsigned char> image);
	std::vector<pixel> pixels;
	boxsize size;
};

