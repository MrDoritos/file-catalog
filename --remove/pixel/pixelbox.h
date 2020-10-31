#pragma once
#include "boxsize.h"
#include "olcPixelGameEngine.h"
#include <string>
#define DOUBLE_PI 6.28318530f
#define PI		  3.14159265f

class pixelbox : public boxsize {
public:
pixelbox(int offsetX, int offsetY, int sizeX, int sizeY) 
:boxsize(offsetX, offsetY, sizeX, sizeY)
{
	_framebuffersize = characters();
	_framebuffer = new olc::Pixel[characters()];
	
	doRender = true;
	isDrawing = false;
	doClear = true;
	
	clear();
}
void newFramebuffer(int count) {
	//delete _framebuffer;
	if (count > 0)
		_framebuffer = new olc::Pixel[count];
}
~pixelbox() {
	//delete _framebuffer;
}
pixelbox(boxsize& size, olc::Pixel* framebuffer, int framebuffersize) : boxsize(size) {
	_framebuffersize = framebuffersize;
	_framebuffer = framebuffer;
	
	//_absboxsize = ;
	
	doRender = true;
	isDrawing = false;
	doClear = true;
	
	clear();
}

pixelbox()
:boxsize()
{

}
//Copy constructor
//
pixelbox(pixelbox* box)
:boxsize(box)
{
	_framebuffersize = box->_framebuffersize;
	_framebuffer = box->_framebuffer;

	doRender = true;
	isDrawing = false;
	doClear = true;
}

bool isDrawing;
bool doRender;
bool doClear;

void clear() {
	const olc::Pixel clear = olc::Pixel(255,255,255);
	if (doClear) {
		while (isDrawing);
		isDrawing = true;
		int count = characters();
		for (int i = 0; i < count; i++) {
			_framebuffer[i] = clear;
		}
		isDrawing = false;
	}
}
void forceclear(){
	const olc::Pixel clear = olc::Pixel(255,255,255);
	while (isDrawing);
	isDrawing = true;
	int count = characters();
	for (int i = 0; i < count; i++) {
		_framebuffer[i] = clearchar;
	}
	isDrawing = false;
}

void settitle(std::string& str) {
	int length = str.length();
	if (sizeX < length) {
		return;
	}
	int offset = getscaleX(0.5f, length);
	set(str, length, offset, 0);
}
void draw(char character, int repetitions, int x, int y) {
	int maxPos = get(x, y) + repetitions;
	maxPos = maxPos > characters() ? characters() : maxPos;

	for (int i = get(x, y); i < maxPos; i++) {
		_framebuffer[get(x, y)] = character;
	}
}
void draw(char character, int repetitions, bool stopatedge, int x, int y) {

}
void set(float val, int count, int x, int y) {
	char* buf = (char*)alloca(count);
	snprintf(buf, count, "%f", val);
	set(buf, count, x, y);
}

void set(int val, int count, int x, int y) {
	char* buf = (char*)alloca(count);
	snprintf(buf, count, "%i", val);
	set(buf, count, x, y);
}

void set(char* str, int count, int x, int y) {
	clip(x, y);
	int offset = get(x, y);
	int max = characters();
	for (int i = offset, b = 0; i < max && b < count; i++, b++) {
		_framebuffer[i] = str[b];
	}
}

void clip(int &x, int &y) {
	x = x > 0 ? x : 0;
	y = y > 0 ? y : 0;
	x = x >= sizeX ? sizeX - 1 : x;
	y = y >= sizeY ? sizeY - 1 : y;
}

void set(std::string& str, int count, int x, int y) {
	while (isDrawing);
	isDrawing = true;
	int length = str.length();
	int offset = get(x,y);
	int max = characters();
	for (int i = offset, b = 0; b < length && b < count && i < offset + count && i < offset + length && i < max; i++, b++){
		_framebuffer[i] = str[b];
	}
	isDrawing = false;	
}
//Draws a circle with the maximum possible diameter
void drawCircle(char border = '#') {
	float centerX = floorf(getscaleX(0.5f)), centerY = floorf(getscaleY(0.5f));
	float radius = centerX > centerY ? centerY : centerX;
	float diameter = radius * 2;
	if (diameter > sizeX) {
#ifdef GCC		
		exit(1);
#else
		_ASSERT("your dominance");
#endif
	}
	float step = diameter / (diameter * 30);
	int x, y;
	for (float theta = 0.0f; theta < DOUBLE_PI; theta += step) {
		x = (centerX + radius * cos(theta));
		y = (centerY - radius * sin(theta));
		if (inBounds(x, y)) {
			_framebuffer[get(x, y)] = border;
		}
	}
}
bool inBounds(int x, int y) {
	return ((x >= 0&& x < offsetX + sizeX) && (y >= 0 && y < offsetY + sizeY));
}
void copyto(char* screen, int maxX, int maxY) {
	while (isDrawing);
	isDrawing = true;
	
	for (int scrY = offsetY, winY = 0; scrY < maxY && winY < sizeY; scrY++, winY++) {
        for (int scrX = offsetX, winX = 0; scrX < maxX && winX < sizeX; scrX++, winX++) {
            screen[(scrY * maxX) + scrX] = _framebuffer[get(winX, winY)];
        }
    }
	
	isDrawing = false;
}
char* getFramebuffer() { return _framebuffer; }
private:
boxsize* _absboxsize;
protected:
int _framebuffersize;
char* _framebuffer;
char clearchar;
bool useAlpha;
};