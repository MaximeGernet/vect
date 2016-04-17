using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

#include "CImage/CImage.h"
#include "CImage/CPixel.h"
#include "CImage/CBitmap.h"

#include "forme.h"
#include "image.h"


Image::Image(int _width, int _height)
{
	cimage = new CImage(_height, _width);
	scale_factor = 1.0f;
	ref_width = _width;
	ref_height = _height;
	setBackgroundColor(30, 30, 30);
}

Image::~Image()
{
	delete cimage;
}

void Image::setBackgroundColor(unsigned char _r, unsigned char _g, unsigned char _b)
{
	background_r = _r;
	background_g = _g;
	background_b = _b;
}

void Image::output(string _output_file)
{
	cbitmap.setImage(cimage);
	cbitmap.SaveBMP(_output_file);
}

void Image::newForme(Forme* _forme)
{
	list.push_back(_forme);
}

void Image::draw()
{
	for(int i = 0; i < ref_height; i++)
	{
		for(int j = 0; j < ref_width; j++)
		{
			CPixel* cpixel = cimage->getPixel(j, i);
			cpixel->RGB(background_r, background_g, background_b);
		}
	}

	for(int indice = 0; indice < list.size(); indice++)
	{
		list[indice]->draw(cimage);
	}
}

