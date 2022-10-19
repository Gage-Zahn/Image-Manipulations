#include <iostream>
#include <fstream>
#include "TGAFile.h"
#include "Pixel.h"
#include <vector>
using namespace std;

TGAFile::TGAFile(string name) {
	ifstream file(name, ios_base::binary);
	if (!file.is_open())
		cout << "WARNING: Could not find file!" << endl;
	file.read((char*)&idLength, sizeof(idLength));
	file.read((char*)&colorMapType, sizeof(colorMapType));
	file.read((char*)&dataTypeCode, sizeof(dataTypeCode));
	file.read((char*)&colorMapOrigin, sizeof(colorMapOrigin));
	file.read((char*)&colorMapLength, sizeof(colorMapLength));
	file.read((char*)&colorMapDepth, sizeof(colorMapDepth));
	file.read((char*)&xOrigin, sizeof(xOrigin));
	file.read((char*)&yOrigin, sizeof(yOrigin));
	file.read((char*)&width, sizeof(width));
	file.read((char*)&height, sizeof(height));
	file.read((char*)&bitsPerPixel, sizeof(bitsPerPixel));
	file.read((char*)&imageDescriptor, sizeof(imageDescriptor));
	
	unsigned int totalPixels = ((unsigned int)width * (unsigned int)height);
	colorData = new Pixel[totalPixels];
	for (unsigned int i = 0; i < totalPixels; i++) {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		file.read((char*)&b, sizeof(b));
		file.read((char*)&g, sizeof(g));
		file.read((char*)&r, sizeof(r));
		colorData[i] = Pixel(r, g, b);
	}
	file.close();
}

TGAFile::~TGAFile() {
	delete[] colorData;
}

void TGAFile::Display() {
	cout << "idLength: " << (int)idLength << endl;
	cout << "colorMapType: " << (int)colorMapType << endl;
	cout << "dataTypeCode: " << (int)dataTypeCode << endl;
	cout << "colorMapOrigin: " << colorMapOrigin << endl;
	cout << "colorMapLength: " << colorMapLength << endl;
	cout << "colorMapDepth: " << (int)colorMapDepth << endl;
	cout << "xOrigin: " << xOrigin << endl;
	cout << "yOrigin: " << yOrigin << endl;
	cout << "width: " << width << endl;
	cout << "height: " << height << endl;
	cout << "bitsPerPixel: " << (int)bitsPerPixel << endl;
	cout << "imageDescriptor: " << (int)imageDescriptor << endl;

	for (unsigned int i = 0; i < (unsigned int)width * (unsigned int)height; i = (i + 1) * 2) {
		cout << "Pixel #: " << i << endl;
		cout << "Red: " << (int)colorData[i].red << endl;
		cout << "Green: " << (int)colorData[i].green << endl;
		cout << "Blue: " << (int)colorData[i].blue << endl << endl;
	}
}

//Image manipulations
void TGAFile::Multiply(TGAFile* filter) {
	unsigned int totalPixels = (unsigned int)this->width * (unsigned int)this->height;
	for (unsigned int i = 0; i < totalPixels; i++) {
		this->colorData[i] = this->colorData[i] * filter->colorData[i];
	}
}

void TGAFile::Subtract(TGAFile* filter) {
	unsigned int totalPixels = (unsigned int)this->width * (unsigned int)this->height;
	for (unsigned int i = 0; i < totalPixels; i++) {
		this->colorData[i] = filter->colorData[i] - this->colorData[i];
	}
}

void TGAFile::Screen(TGAFile* filter) {
	unsigned int totalPixels = (unsigned int)this->width * (unsigned int)this->height;
	for (unsigned int i = 0; i < totalPixels; i++) {
		this->colorData[i] = Pixel(255,255,255) - (Pixel(255, 255, 255) - this->colorData[i]) * (Pixel(255, 255, 255) - filter->colorData[i]);
	}
}

void TGAFile::Overlay(TGAFile* filter) {
	unsigned int totalPixels = (unsigned int)this->width * (unsigned int)this->height;
	for (unsigned int i = 0; i < totalPixels; i++) {
		this->colorData[i] = this->colorData[i].Overlay(filter->colorData[i]);
	}
}

void TGAFile::Add(unsigned int x, char color) {
	unsigned int totalPixels = (unsigned int)this->width * (unsigned int)this->height;
	for (unsigned int i = 0; i < totalPixels; i++) {
		if(color == 'r')
			this->colorData[i].red = Pixel::Cap((float)this->colorData[i].red + x);
		if (color == 'g')
			this->colorData[i].green = Pixel::Cap((float)this->colorData[i].green + x);
		if (color == 'b')
			this->colorData[i].blue = Pixel::Cap((float)this->colorData[i].blue + x);
	}
}

void TGAFile::Scale(float x, char color) {
	unsigned int totalPixels = (unsigned int)this->width * (unsigned int)this->height;
	for (unsigned int i = 0; i < totalPixels; i++) {
		if (color == 'r')
			this->colorData[i].red = Pixel::Cap((float)this->colorData[i].red * x);
		if (color == 'g')
			this->colorData[i].green = Pixel::Cap((float)this->colorData[i].green * x);
		if (color == 'b')
			this->colorData[i].blue = Pixel::Cap((float)this->colorData[i].blue * x);
	}
}

void TGAFile::SeparateChannels(TGAFile* red, TGAFile* green, TGAFile* blue) {
	unsigned int totalPixels = (unsigned int)this->width * (unsigned int)this->height;
	for (unsigned int i = 0; i < totalPixels; i++) {
		red->colorData[i].red = this->colorData[i].red;
		red->colorData[i].green = this->colorData[i].red;
		red->colorData[i].blue = this->colorData[i].red;

		green->colorData[i].red = this->colorData[i].green;
		green->colorData[i].green = this->colorData[i].green;
		green->colorData[i].blue = this->colorData[i].green;

		blue->colorData[i].red = this->colorData[i].blue;
		blue->colorData[i].green = this->colorData[i].blue;
		blue->colorData[i].blue = this->colorData[i].blue;
	}
}

void TGAFile::CombineChannels(TGAFile* red, TGAFile* green, TGAFile* blue) {
	unsigned int totalPixels = (unsigned int)this->width * (unsigned int)this->height;
	for (unsigned int i = 0; i < totalPixels; i++) {
		this->colorData[i].red = red->colorData[i].red;
		this->colorData[i].green = green->colorData[i].green;
		this->colorData[i].blue = blue->colorData[i].blue;
	}
}

void TGAFile::Flip() {
	unsigned int totalPixels = (unsigned int)this->width * (unsigned int)this->height;
	Pixel* temp = new Pixel[totalPixels];
	for (unsigned int i = 0; i < totalPixels; i++) {
		temp[totalPixels - i - 1] = this->colorData[i];
	}
	delete[] this->colorData;
	this->colorData = temp;
}

void TGAFile::Quadrants(TGAFile* topLeft, TGAFile* bottomLeft, TGAFile* bottomRight) {
	unsigned int totalPixels = (unsigned int)this->width * (unsigned int)this->height;
	Pixel* temp = new Pixel[totalPixels * 4];
	unsigned int count = 0;

	for (unsigned int i = 0; i < totalPixels; i++) {	
		if (count % width == 0 && count != 0)
			count = count + width;
		temp[count] = bottomLeft->colorData[i];
		count++;
	}

	count = width;
	for (unsigned int i = 0; i < totalPixels; i++) {
		if (count % (width * 2) == 0)
			count = count + width;
		temp[count] = bottomRight->colorData[i];
		count++;
	}

	count = width * height * 2;
	for (unsigned int i = 0; i < totalPixels; i++) {
		if ((i) % (width) == 0 && i != 0)
			count = count + width;
		temp[count] = topLeft->colorData[i];
		count++;
	}

	count = width * height * 2 + width;
	for (unsigned int i = 0; i < totalPixels; i++) {
		if (count % (width * 2) == 0)
			count = count + width;
		temp[count] = this->colorData[i];
		count++;
	}

	delete[] this->colorData;
	this->colorData = temp;
	this->width *= 2;
	this->height *= 2;
}

//Verifiy
float TGAFile::Verifiy(TGAFile* example) {
	unsigned int totalPixels = (unsigned int)this->width * (unsigned int)this->height;
	unsigned int faultyPixels = 0;
	for (unsigned int i = 0; i < totalPixels; i++) {
		if (!(this->colorData[i] == example->colorData[i]))
			faultyPixels++;
	}
	
	if (this->idLength != example->idLength)
		faultyPixels++;
	if (this->colorMapType != example->colorMapType)
		faultyPixels++;
	if (this->dataTypeCode != example->dataTypeCode)
		faultyPixels++;
	if (this->colorMapOrigin != example->colorMapOrigin)
		faultyPixels++;
	if (this->colorMapLength != example->colorMapLength)
		faultyPixels++;
	if (this->colorMapDepth != example->colorMapDepth)
		faultyPixels++;
	if (this->xOrigin != example->xOrigin)
		faultyPixels++;
	if (this->yOrigin != example->yOrigin)
		faultyPixels++;
	if (this->width != example->width)
		faultyPixels++;
	if (this->height != example->height)
		faultyPixels++;
	if (this->bitsPerPixel != example->bitsPerPixel)
		faultyPixels++;
	if (this->imageDescriptor != example->imageDescriptor)
		faultyPixels++;
	
	return (float)faultyPixels / totalPixels;
}

//Output
void TGAFile::Export(string name) {
	ofstream file (name,ofstream::binary);
	
	file.write((char*)&idLength, sizeof(idLength));
	file.write((char*)&colorMapType, sizeof(colorMapType));
	file.write((char*)&dataTypeCode, sizeof(dataTypeCode));
	file.write((char*)&colorMapOrigin, sizeof(colorMapOrigin));
	file.write((char*)&colorMapLength, sizeof(colorMapLength));
	file.write((char*)&colorMapDepth, sizeof(colorMapDepth));
	file.write((char*)&xOrigin, sizeof(xOrigin));
	file.write((char*)&yOrigin, sizeof(yOrigin));
	file.write((char*)&width, sizeof(width));
	file.write((char*)&height, sizeof(height));
	file.write((char*)&bitsPerPixel, sizeof(bitsPerPixel));
	file.write((char*)&imageDescriptor, sizeof(imageDescriptor));

	unsigned int totalPixels = ((unsigned int)width * (unsigned int)height);
	for (unsigned int i = 0; i < totalPixels; i++) {
		file.write((char*)&colorData[i].blue, sizeof(colorData[i].blue));
		file.write((char*)&colorData[i].green, sizeof(colorData[i].green));
		file.write((char*)&colorData[i].red, sizeof(colorData[i].red));
	}

	file.close();
}