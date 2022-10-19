#include <iostream>
#include <fstream>
#include <vector>
#include "Pixel.h"
using namespace std;

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b) {
	red = r;
	green = g;
	blue = b;
}

Pixel::Pixel() {
	red = 0;
	green = 0;
	blue = 0;
}

bool Pixel::operator==(const Pixel& rhs) {
	return (this->blue == rhs.blue && this->red == rhs.red && this->green == rhs.green);
}

Pixel Pixel::operator*(const Pixel& rhs) {
	unsigned char r = (unsigned char)(((float)this->red * (float)rhs.red) / 255 + .5f);
	unsigned char g = (unsigned char)(((float)this->green * (float)rhs.green) / 255 + .5f);
	unsigned char b = (unsigned char)(((float)this->blue * (float)rhs.blue) / 255 + .5f);
	return Pixel(r, g, b);
}

Pixel Pixel::operator-(const Pixel& rhs) {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	if ((float)this->red - (float)rhs.red + .5f >= 255)
		r = (unsigned char)255;
	else if (((float)this->red - (float)rhs.red + .5f <= 0))
		r = (unsigned char)0;
	else
		r = (unsigned char)((float)this->red - (float)rhs.red + .5f);

	if (((float)this->green - (float)rhs.green) + .5f >= 255)
		g = (unsigned char)255;
	else if (((float)this->green - (float)rhs.green) + .5f <= 0)
		g = (unsigned char)0;
	else
		g = (unsigned char)(((float)this->green - (float)rhs.green) + .5f);

	if (((float)this->blue - (float)rhs.blue) + .5f >= 255)
		b = (unsigned char)255;
	else if (((float)this->blue - (float)rhs.blue) + .5f <= 0)
		b = (unsigned char)0;
	else
		b = (unsigned char)(((float)this->blue - (float)rhs.blue) + .5f);
	return Pixel(r, g, b);
}

Pixel Pixel::Scale(float scaleFactor) {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	if ((int)((float)red * (float)scaleFactor + 0.5f) >= 255)
		r = (unsigned char)255;
	else if ((int)((float)red * (float)scaleFactor + 0.5f) <= 0)
		r = (unsigned char)0;
	else
		r = (unsigned char)((float)red * (float)scaleFactor + 0.5f);

	if ((int)((float)green * (float)scaleFactor + 0.5f) >= 255)
		g = (unsigned char)255;
	else if ((int)((float)green * (float)scaleFactor + 0.5f) <= 0)
		g = (unsigned char)0;
	else
		g = (unsigned char)((float)green * (float)scaleFactor + 0.5f);

	if ((int)((float)blue * (float)scaleFactor + 0.5f) >= 255)
		b = (unsigned char)255;
	else if ((int)((float)blue * (float)scaleFactor + 0.5f) <= 0)
		b = (unsigned char)0;
	else
		b = (unsigned char)((float)blue * (float)scaleFactor + 0.5f);

	return Pixel(r, g, b);
}

Pixel Pixel::Overlay(Pixel filter) {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	
	if (filter.red > 127)
		r = Cap((1.0f - 2.0f * (1.0f - this->red / 255.0f) * (1.0f - filter.red / 255.0f)) * 255.0f);
	else
		r = Cap(((float)2 * ((float)this->red / 255 * (float)filter.red / 255)) * 255.0f);
	
	if (filter.green > 127)
		g = Cap((1.0f - 2.0f * (1.0f - this->green / 255.0f) * (1.0f - filter.green / 255.0f)) * 255.0f);
	else
		g = Cap(((float)2 * ((float)this->green / 255 * (float)filter.green / 255)) * 255.0f);
	
	if (filter.blue > 127)
		b = Cap((1.0f - 2.0f * (1.0f - this->blue / 255.0f) * (1.0f - filter.blue / 255.0f)) * 255.0f);
	else
		b = Cap(((float)2 * ((float)this->blue / 255 * (float)filter.blue / 255)) * 255.0f);

	return Pixel(r, g, b);
}

unsigned char Pixel::Cap(float x) {
	if ((int)(x + 0.5f) <= 0)
		return 0;
	else if ((int)(x + 0.5f) >= 255)
		return 255;
	else
		return (unsigned char)(x + 0.5f);
}