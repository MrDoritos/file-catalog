#include <cmath>
#define GET(x, y) ((y * sizeX) + x)
#pragma once

class boxsize {
public:
boxsize(boxsize* size) {
	this->offsetX = size->offsetX;
	this->offsetY = size->offsetY;
	this->sizeX = size->sizeX;
	this->sizeY = size->sizeY;
}
boxsize(int offsetX, int offsetY, int sizeX, int sizeY) {
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}
boxsize() {

}
int offsetX;
int offsetY;
int sizeX;
int sizeY;
inline int getMaxX() { return (sizeX + offsetX); }
inline int getMaxY() { return (sizeY + offsetY); }
inline int getMinX() { return (offsetX); }
inline int getMinY() { return (offsetY); }
inline int characters() {
	return (sizeX * sizeY);
}
inline int get(int x, int y) {
	return ((y * sizeX) + x);
}
double getscaleX(float scale) {
	return (float(sizeX) * scale);
}
int getscaleXint(float scale) {
	return (int)round(float(sizeX) * scale);
}
double getscaleY(float scale) {
	return (float(sizeY) * scale);
}
int getscaleYint(float scale) {
	return (int)round(float(sizeY) *scale);
}
int getscaleYint(float scale, int length) {
	if (length < 1.0f) {
		return (int)round(float(sizeY) * scale);
	}
	return (int)round(float(sizeY) * scale) - (float(length) / 2);
}
float getscaleY(float scale, int length) {
	if (length < 1.0f) {
		return float(sizeY) * scale;
	}
	return (float(sizeY) * scale) - (float(length) / 2);
}
int getMin() {
	return sizeX > sizeY ? sizeY : sizeX;
}
float getMinScale(float scale) {
	return (float(getMin()) * scale);
}
float getMinScale(float scale, int length) {
	if (length < 1) {
		return (float(getMin()) * scale);
	}
	return (float(getMin()) * scale) - (float(length) / 2);
}
double getscaleX(float scale, int length) {
	if (length < 1) {
		return (float(sizeX) * scale);
	}
	return (float(sizeX) * scale) - (float(length) / 2);
}
double getscaleXint(float scale, int length) {
	if (length < 1) {
		return (int)round(float(sizeX) * scale);
	}
	return (int)round(float(sizeX) * scale) - (float(length) / 2);
}
private:
};