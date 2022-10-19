#include <iostream>
#include <fstream>
#include "TGAFile.h"
#include "Pixel.h"
#include <vector>
using namespace std;

int main() {
	//import all files
	TGAFile* car = new TGAFile("input/car.tga");
	TGAFile* circles = new TGAFile("input/circles.tga");
	
	TGAFile* layer_blue = new TGAFile("input/layer_blue.tga");
	TGAFile* layer_green = new TGAFile("input/layer_green.tga");
	TGAFile* layer_red = new TGAFile("input/layer_red.tga");
	TGAFile* layer1 = new TGAFile("input/layer1.tga");
	TGAFile* layer2 = new TGAFile("input/layer2.tga");

	TGAFile* pattern1 = new TGAFile("input/pattern1.tga");
	TGAFile* pattern2 = new TGAFile("input/pattern2.tga");
	
	TGAFile* text = new TGAFile("input/text.tga");
	TGAFile* text2 = new TGAFile("input/text2.tga");

	//import example files
	/*
	TGAFile* EXAMPLE_part1 = new TGAFile("examples/EXAMPLE_part1.tga");
	TGAFile* EXAMPLE_part2 = new TGAFile("examples/EXAMPLE_part2.tga");
	TGAFile* EXAMPLE_part3 = new TGAFile("examples/EXAMPLE_part3.tga");
	TGAFile* EXAMPLE_part4 = new TGAFile("examples/EXAMPLE_part4.tga");
	TGAFile* EXAMPLE_part5 = new TGAFile("examples/EXAMPLE_part5.tga");
	TGAFile* EXAMPLE_part6 = new TGAFile("examples/EXAMPLE_part6.tga");
	TGAFile* EXAMPLE_part7 = new TGAFile("examples/EXAMPLE_part7.tga");
	TGAFile* EXAMPLE_part8_r = new TGAFile("examples/EXAMPLE_part8_r.tga");
	TGAFile* EXAMPLE_part8_g = new TGAFile("examples/EXAMPLE_part8_g.tga");
	TGAFile* EXAMPLE_part8_b = new TGAFile("examples/EXAMPLE_part8_b.tga");
	TGAFile* EXAMPLE_part9 = new TGAFile("examples/EXAMPLE_part9.tga");
	TGAFile* EXAMPLE_part10 = new TGAFile("examples/EXAMPLE_part10.tga");
	TGAFile* EXAMPLE_extracredit = new TGAFile("examples/EXAMPLE_extracredit.tga");
	*/

	//Part 1
	layer1->Multiply(pattern1);
	TGAFile* part1 = layer1;
	layer1 = new TGAFile("input/layer1.tga");
	//cout << "% errors on Part1: " << part1->Verifiy(EXAMPLE_part1) << endl;

	//Part 2
	layer2->Subtract(car);
	TGAFile* part2 = layer2;
	layer2 = new TGAFile("input/layer2.tga");
	//cout << "% errors on Part2: " << part2->Verifiy(EXAMPLE_part2) << endl;

	//Part 3
	layer1->Multiply(pattern2);
	text->Screen(layer1);
	TGAFile* part3 = text;
	text = new TGAFile("input/text.tga");
	delete layer1;
	layer1 = new TGAFile("input/layer1.tga");
	//cout << "% errors on Part3: " << part3->Verifiy(EXAMPLE_part3) << endl;

	//Part 4
	layer2->Multiply(circles);
	pattern2->Subtract(layer2);
	TGAFile* part4 = pattern2;
	pattern2 = new TGAFile("input/pattern2.tga");
	delete layer2;
	layer2 = new TGAFile("input/layer2.tga");
	//cout << "% errors on Part4: " << part4->Verifiy(EXAMPLE_part4) << endl;

	//Part 5
	layer1->Overlay(pattern1);
	TGAFile* part5 = layer1;
	layer1 = new TGAFile("input/layer1.tga");
	//cout << "% errors on Part5: " << part5->Verifiy(EXAMPLE_part5) << endl;

	//Part 6
	car->Add(200,'g');
	TGAFile* part6 = car;
	car = new TGAFile("input/car.tga");
	//cout << "% errors on Part6: " << part6->Verifiy(EXAMPLE_part6) << endl;

	//Part 7
	car->Scale(4, 'r');
	car->Scale(0, 'b');
	TGAFile* part7 = car;
	car = new TGAFile("input/car.tga");
	//cout << "% errors on Part7: " << part7->Verifiy(EXAMPLE_part7) << endl;

	//Part 8
	TGAFile* part8_r = new TGAFile("input/car.tga");
	TGAFile* part8_g = new TGAFile("input/car.tga");
	TGAFile* part8_b = new TGAFile("input/car.tga");
	car->SeparateChannels(part8_r, part8_g, part8_b);
	//cout << "% errors on part8_r: " << part8_r->Verifiy(EXAMPLE_part8_r) << endl;
	//cout << "% errors on part8_g: " << part8_g->Verifiy(EXAMPLE_part8_g) << endl;
	//cout << "% errors on part8_b: " << part8_b->Verifiy(EXAMPLE_part8_b) << endl;

	//Part 9
	layer_red->CombineChannels(layer_red, layer_green, layer_blue);
	TGAFile* part9 = layer_red;
	//cout << "% errors on part9: " << part9->Verifiy(EXAMPLE_part9) << endl;

	//Part 10
	text2->Flip();
	TGAFile* part10 = text2;
	//cout << "% errors on part10: " << part10->Verifiy(EXAMPLE_part10) << endl;

	//Part 11
	circles->Quadrants(car, text, pattern1);
	TGAFile* part11 = circles;
	//cout << "% errors on part11: " << part11->Verifiy(EXAMPLE_extracredit) << endl;

	//Output
	part1->Export("output/part1.tga");
	part2->Export("output/part2.tga");
	part3->Export("output/part3.tga");
	part4->Export("output/part4.tga");
	part5->Export("output/part5.tga");
	part6->Export("output/part6.tga");
	part7->Export("output/part7.tga");
	part8_r->Export("output/part8_r.tga");
	part8_g->Export("output/part8_g.tga");
	part8_b->Export("output/part8_b.tga");
	part9->Export("output/part9.tga");
	part10->Export("output/part10.tga");
	part11->Export("output/extracredit.tga");

	return 0;
}