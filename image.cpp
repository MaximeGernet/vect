#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include "CImage/CImage.h"


Image::Image(int _width, int _height)
{
	cimage = new CImage(_height, _width);
	output_file = "output.bmp";
	input_file = "input.txt";
	scale_factor = 1;
	ref_width = _width;
	ref_height = _height;
}

Image::~Image()
{
	delete cimage;
}

void Image::output()
{
	cbitmap.setImage(cimage);
	SaveBMP(output_file);
}

void Image::newForme(Forme* _forme)
{
	list.push_back(*_forme);
}

void Image::draw()
{
	int i;
	for(i = 0; i < list.size(); i++)
	{
		list[i].display();
	}
}

