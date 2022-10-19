#pragma once
#include <iostream>
#include "Pixel.h"
#include <vector>
using namespace std;

struct  TGAFile{
	//Data
	char idLength;
	char colorMapType;
	char dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char bitsPerPixel;
	char imageDescriptor;
	Pixel* colorData;

	TGAFile(string name);
	~TGAFile();
	void Display();
	
	//Image manipulations
	void Multiply(TGAFile* filter);
	void Subtract(TGAFile* filter);
	void Screen(TGAFile* filter);
	void Overlay(TGAFile* filter);
	void Add(unsigned int x, char color);
	void Scale(float x, char color);
	void SeparateChannels(TGAFile* red, TGAFile* green, TGAFile* blue);
	void CombineChannels(TGAFile* red, TGAFile* green, TGAFile* blue);
	void Flip();
	void Quadrants(TGAFile* topLeft, TGAFile* bottomLeft, TGAFile* bottomRight);
	
	//Verifiy
	float Verifiy(TGAFile* example);

	//Output
	void Export(string name);
};