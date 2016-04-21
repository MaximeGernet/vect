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


Image::Image(int _width, int _height, float _scale_factor)
{
	scale_factor = _scale_factor;
	cimage = new CImage(_height, _width);
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

void Image::setScaleFactor(float _scale_factor)
{
	scale_factor = _scale_factor;
	/*
	 *
	 * Problème : On ne peut pas accéder aux attributs de l'objet fils après l'avoir converti en un objet père
	 *
	 * On peut en revanche recharger toutes les formes à partir du fichier, avec le nouveau facteur d'échelle
	 *
	for(int i = 0; i < list.size(); i++)
	{
		list[i].setDrawArea();
		list[i].draw();
	}
	*/
}

void Image::fit()
{
	if(list.size() < 1)
		return;
	int x_min = list[0].getXOrig();
	int y_min = list[0].getYOrig();
	int x_max = list[0].getXMax();
	int y_max = list[0].getYMax();

	for(int i = 1; i < list.size(); i++)
	{
		x_min = (x_min < list[i].getXOrig()) ? x_min : list[i].getXOrig();
		y_min = (y_min < list[i].getYOrig()) ? y_min : list[i].getXOrig();
		x_max = (x_max > list[i].getXMax()) ? x_max : list[i].getXMax();
		y_max = (y_max > list[i].getYMax()) ? y_max : list[i].getXMax();
	}

	for(int i = 0; i < list.size(); i++)
	{
		list[i].translate(-x_min, -y_min);
	}

	float x_scale_factor = (float)ref_width / (x_max - x_min);
	float y_scale_factor = (float)ref_height / (y_max - y_min);
	float new_scale_factor = (x_scale_factor < y_scale_factor) ? x_scale_factor : y_scale_factor;

	setScaleFactor(new_scale_factor);
}

float Image::getScale()
{
	return scale_factor;
}

void Image::output(string _output_file)
{
	cbitmap.setImage(cimage);
	cbitmap.SaveBMP(_output_file);
}

void Image::newForme(Forme _forme)
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
		list[indice].draw(cimage, ref_width, ref_height);
	}
}

