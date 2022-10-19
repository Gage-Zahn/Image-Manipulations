#pragma once
#include <iostream>
using namespace std;

struct Pixel {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	
	Pixel(unsigned char r, unsigned char g, unsigned char b);
	Pixel();
	bool operator==(const Pixel& rhs);
	Pixel operator*(const Pixel& rhs);
	Pixel operator-(const Pixel& rhs);

	Pixel Scale(float scaleFactor);
	Pixel Overlay(Pixel filter);
	static unsigned char Cap(float x);
};