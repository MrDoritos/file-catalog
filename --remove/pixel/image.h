#include "pixelbox.h"
#include "boxsize.h"
#include "olcPixelGameEngine.h"
#include <cmath>
#include <iostream>

class image :
public box
{
public:
image() {
	
}
image(const char* path, box* camera, int offsetx, int offsety, int sizex, int sizey) :
box(offsetx,offsety,sizex,sizey)
{
	simage = new png(path);
	this->camera = camera;
	*((boxsize*)(this)) = boxsize(0,0,simage->getSizeX(),simage->getSizeY());
	newFramebuffer(characters());
	sample();
}
image(const char* path, box* imBuf, box* camera)
:box(imBuf) 
{
	simage = new png(path);
	this->camera = camera;
	sample();
}
image(png* simage, box* imBuf, box* camera) 
:box(imBuf)
{
	this->simage = simage;
	this->camera = camera;	
	sample();
}
void raster() {
	this->copyto(camera->getFramebuffer(), camera->sizeX, camera->sizeY);
}
void resize(int sizeX, int sizeY) {
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	sample();
}
void limitedResize(int sizeX, int sizeY) {
	int newW, newH;
	int y_W = sizeX;
	int y_H = sizeY;
	int m_W = simage->getSizeX();
	int m_H = simage->getSizeY();
	float rW = y_W / m_W;
	float rH = y_H / m_H;
	
	if (rW > rH) {
		newH = int(m_H / rW);
		newW = sizeX;
	} else {
		newW = int(m_W / rH);
		newH = sizeY;
	}
	
	this->sizeX = newW;
	this->sizeY = newH;
	
	newFramebuffer(characters());
	sample();
}
void limitedResize(int size) {
	limitedResize(size,size);
}
void sampletest(float valRad = 1.0472) {
	float xlim = sizeX * cos(valRad);
	float hypo, oppo, adja;
	for (float len = 0.0f; len < xlim; len++) {
		adja = cos(valRad) * len;
		if (tan(valRad) > 0.1f)
			oppo = len/tan(valRad);
		else 
			oppo = 0.0f;
		for (int y = 0; y < oppo; y++) {
			if (!(len > sizeX || getscaleY(0.5,oppo) + y > sizeY || getscaleY(0.5,oppo) + y < 0 || len < 0))				
			_framebuffer[get(len, getscaleY(0.5,oppo) + y)] = getGSC(simage->getSample(len, y, xlim, oppo)->value());
		}
	}
}
void move(int offsetx, int offsety) {
	this->offsetX = offsetx;
	this->offsetY = offsety;
}
void resize(int offsetx, int offsety, int sizex, int sizey) {
	this->offsetX = offsetx;
	this->offsetY = offsety;
	if (this->sizeX != sizex || this->sizeY != sizey) {
		this->sizeX = sizex;
		this->sizeY = sizey;
		newFramebuffer(characters());
		sample();
	}
}
void sample() {
	for (int x = 0; x < sizeX; x++) {
		for (int y = 0; y < sizeY; y++) {
			_framebuffer[get(x, y)] = getGSC(simage->getSample(x, y, sizeX, sizeY)->value());
		}
	}
}
private:
inline char getGSC(float val) {	
	const int size = 70;
	const char scC[74] = { "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.   $" };
	return scC[int(size * val)];
}
box* camera;
png* simage;
};