using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "CImage/CImage.h"
#include "CImage/CPixel.h"
#include "CImage/CBitmap.h"

#include "forme.h"
#include "image.h"

using namespace std;

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
	Forme* forme;
	delete cimage;
	while(!queue.empty())
	{
		forme = queue.top();
		delete forme;
		queue.pop();
	}
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
}


void Image::fit()
{
	priority_queue<Forme*, vector<Forme*>, comparaison> copy_queue;
	Forme* forme;

	if(queue.size() < 1)
		return;

	forme = queue.top();
	copy_queue.push(forme);
	queue.pop();
	int x_min = forme->getXMin();
	int y_min = forme->getYMin();
	int x_max = forme->getXMax();
	int y_max = forme->getYMax();

	while(!queue.empty())
	{
		forme = queue.top();
		copy_queue.push(forme);
		queue.pop();
		x_min = (x_min < forme->getXMin()) ? x_min : forme->getXMin();
		y_min = (y_min < forme->getYMin()) ? y_min : forme->getYMin();
		x_max = (x_max > forme->getXMax()) ? x_max : forme->getXMax();
		y_max = (y_max > forme->getYMax()) ? y_max : forme->getYMax();
	}
	queue.swap(copy_queue);

	translate(-x_min, -y_min);

	float x_scale_factor = (float)ref_width / (x_max + 1 - x_min);
	float y_scale_factor = (float)ref_height / (y_max + 1 - y_min);
	float new_scale_factor = (x_scale_factor < y_scale_factor) ? x_scale_factor : y_scale_factor;

	printf("x_scale_factor: %f\n", x_scale_factor);
	printf("y_scale_factor: %f\n", y_scale_factor);

	scale(new_scale_factor);
}

void Image::scale(float _scale_factor)
{
	priority_queue<Forme*, vector<Forme*>, comparaison> copy_queue;
	Forme* forme;

	setScaleFactor(_scale_factor);

	while(!queue.empty())
	{
		forme = queue.top();
		forme->scale(scale_factor);
		copy_queue.push(forme);
		queue.pop();
	}
	queue.swap(copy_queue);
}

void Image::translate(int _x, int _y)
{
	priority_queue<Forme*, vector<Forme*>, comparaison> copy_queue;
	Forme* forme;

	while(!queue.empty())
	{
		forme = queue.top();
		forme->translate(_x, _y);
		copy_queue.push(forme);
		queue.pop();
	}

	queue.swap(copy_queue);
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

void Image::newForme(Forme* _forme)
{
	queue.push(_forme);
}

void Image::draw()
{
	priority_queue<Forme*, vector<Forme*>, comparaison> copy_queue;
	Forme* forme;
	for(int i = 0; i < ref_height; i++)
	{
		for(int j = 0; j < ref_width; j++)
		{
			CPixel* cpixel = cimage->getPixel(j, i);
			cpixel->RGB(background_r, background_g, background_b);
		}
	}

	while(!queue.empty())
	{
		forme = queue.top();
		forme->draw(cimage, ref_width, ref_height);
		copy_queue.push(forme);
		queue.pop();
	}
	queue.swap(copy_queue);
}

void Image::readFile(string file_name)
{
	//input.vect
	string buf[9];
	string buffer;
	ifstream infile;
	infile.open(file_name.c_str());
	while(!infile.eof())
	{
		getline(infile, buffer);
		cutString(buffer, buf);
		if (buf[0].compare("POINT") == 0)
		{
			printf("Creating new point...\n");
			Point* forme = new Point(atoi(buf[1].c_str()), atoi(buf[2].c_str()), scale_factor);
			forme->setColor(atoi(buf[3].c_str()), atoi(buf[4].c_str()), atoi(buf[5].c_str()), atoi(buf[6].c_str()));
			newForme(forme);
		}
		else if(buf[0].compare("LIGNE") == 0)
		{
			printf("Creating new line...\n");
			Ligne* forme = new Ligne(atoi(buf[1].c_str()), atoi(buf[2].c_str()), atoi(buf[3].c_str()), atoi(buf[4].c_str()), scale_factor);
			forme->setColor(atoi(buf[5].c_str()), atoi(buf[6].c_str()), atoi(buf[7].c_str()), atoi(buf[8].c_str()));
			newForme(forme);
		}
		else if(buf[0].compare("RECTANGLE") == 0)
		{
			printf("Creating new rectangle...\n");
			Rectangle* forme = new Rectangle(atoi(buf[1].c_str()), atoi(buf[2].c_str()), atoi(buf[3].c_str()), atoi(buf[4].c_str()), scale_factor);
			forme->setColor(atoi(buf[5].c_str()), atoi(buf[6].c_str()), atoi(buf[7].c_str()), atoi(buf[8].c_str()));
			newForme(forme);
		}
		else if(buf[0].compare("CARRE") == 0)
		{
			printf("Creating new square...\n");
			Carre* forme = new Carre(atoi(buf[1].c_str()), atoi(buf[2].c_str()), atoi(buf[3].c_str()), scale_factor);
			forme->setColor(atoi(buf[4].c_str()), atoi(buf[5].c_str()), atoi(buf[6].c_str()), atoi(buf[7].c_str()));
			newForme(forme);
		}
		else if(buf[0].compare("CERCLE") == 0)
		{
			printf("Creating new circle...\n");
			Cercle* forme = new Cercle(atoi(buf[1].c_str()), atoi(buf[2].c_str()), atoi(buf[3].c_str()), scale_factor);
			forme->setColor(atoi(buf[4].c_str()), atoi(buf[5].c_str()), atoi(buf[6].c_str()), atoi(buf[7].c_str()));
			newForme(forme);
		}
		else if(buf[0].compare("RECTANGLE_S") == 0)
		{
			printf("Creating new rectangleS...\n");
			RectangleS* forme = new RectangleS(atoi(buf[1].c_str()), atoi(buf[2].c_str()), atoi(buf[3].c_str()), atoi(buf[4].c_str()), scale_factor);
			forme->setColor(atoi(buf[5].c_str()), atoi(buf[6].c_str()), atoi(buf[7].c_str()), atoi(buf[8].c_str()));
			newForme(forme);
		}
		else if(buf[0].compare("CARRE_S") == 0)
		{
			printf("Creating new carreS...\n");
			CarreS* forme = new CarreS(atoi(buf[1].c_str()), atoi(buf[2].c_str()), atoi(buf[3].c_str()), scale_factor);
			forme->setColor(atoi(buf[4].c_str()), atoi(buf[5].c_str()), atoi(buf[6].c_str()), atoi(buf[7].c_str()));
			newForme(forme);
		}
		else if(buf[0].compare("CERCLE_S") == 0)
		{
			printf("Creating new circleS...\n");
			CercleS* forme = new CercleS(atoi(buf[1].c_str()), atoi(buf[2].c_str()), atoi(buf[3].c_str()), scale_factor);
			forme->setColor(atoi(buf[4].c_str()), atoi(buf[5].c_str()), atoi(buf[6].c_str()), atoi(buf[7].c_str()));
			newForme(forme);
		}
	}
	printf("%u shapes loaded\n", queue.size());
}

void Image::cutString(string c, string* buf)
{
	int taille = c.size();
	int pos = 0;
	int old_pos = 0;
	int i = 0;
	int j = 0;
	while(j < 9)
	{
		pos = c.find_first_of(" {};", pos);
		if(c[pos] == ';')
			break;
		c.erase(pos,1);
		j++;
	}
	pos = 0;
	while(c[pos] != ';' && i < 9)
	{
		pos = c.find_first_of(":,;", old_pos + 1);
		buf[i].assign(c, old_pos, pos - old_pos);
		i++;
		old_pos = pos + 1;
	}
}



