#pragma once
#include "pch.h"
#include "png.h"
#include "lodepng.h"
#include <iostream>
#include "boxsize.h"
#include <vector>
#include <string>

png::png(const char * path)
	:size(0,0,0,0)
{
	load(path);
}

png::~png()
{
}

void png::getPixel(int x, int y, pixel & pixel)
{
	pixel = pixels[size.get(x, y)];
}

pixel* png::getPixel(int x, int y) {
	return &pixels[size.get(x, y)];
}

pixel * png::getSample(int x, int y, boxsize * src)
{
	float scaleX = float(src->sizeX) / float(size.sizeX), scaleY = float(src->sizeY) / float(size.sizeY);
	return getPixel((int)(x / scaleX), (int)(y / scaleY));
}

pixel *png::getSample(int x, int y, int sizex, int sizey) {
	float scaleX = float(sizex) / float (size.sizeX), scaleY = float(sizey) / float(size.sizeY);
	return getPixel((int)(x / scaleX), (int)(y / scaleY));
}

int png::load(const char * path)
{
	std::vector<unsigned char> image;
	unsigned width, height, error;

	error = lodepng::decode(image, width, height, path);
	
	if (error)
	{
		std::cout << "lodepng error: " << error << std::endl;
		exit(error);
	}

	size.sizeX = width;
	size.sizeY = height;

	convert(image);
}

void png::convert(std::vector<unsigned char> image)
{
	int size = image.size();
	int pixelcount = size / 4;	
	pixels.reserve(pixelcount);
	pixel* thesepixels = (pixel*)malloc(sizeof(pixel) * pixelcount);
	for (int i = 0, p = 0; i < size;p++, i+=4) {		 
		pixels.push_back(thesepixels[p] = pixel(image[i], image[i+1], image[i+2], image[i+3]));
	}
}
