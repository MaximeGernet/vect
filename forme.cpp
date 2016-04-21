using namespace std;

#include <math.h>
#include <string.h>

#include "CImage/CImage.h"
#include "CImage/CPixel.h"

#include "forme.h"


Forme::Forme()
{
	shape_pixels = NULL;
	setColor(255, 255, 255, 100);
}


Forme::Forme(const Forme &source)
{
	source.copyAttrib(&x, &y, &width, &height, &r, &g, &b, &a);
	shape_pixels = new bool [width * height];
	source.copyShape(shape_pixels);
}


Forme::~Forme()
{
	if(shape_pixels != NULL)
		delete shape_pixels;
}

void Forme::setColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

void Forme::copyAttrib(int* _x, int* _y, int* _width, int* _height, unsigned char* _r, unsigned char* _g, unsigned char* _b, unsigned char* _a) const
{
	*_x = x;
	*_y = y;
	*_width = width;
	*_height = height;
	*_r = r;
	*_g = g;
	*_b = b;
	*_a = a;
}

void Forme::copyShape(bool* _shape_pixels) const
{
	memcpy(_shape_pixels, shape_pixels, sizeof(bool) * width * height);
}

int Forme::getXOrig()
{
	return x;
}

int Forme::getYOrig()
{
	return y;
}

int Forme::getXMax()
{
	return x + width - 1;
}

int Forme::getYMax()
{
	return y + height - 1;
}

void Forme::translate(int _x, int _y)
{
	x += _x;
	y += _y;
}

void Forme::draw(CImage* cimage, int _image_width, int _image_height)
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(x + j >= 0 && x + j < _image_width && y + i >= 0 && y + i < _image_height)
			{
				if(shape_pixels[i * width + j])
				{
					CPixel* cpixel = cimage->getPixel(x + j, y + i);
					unsigned char R, G, B;
					R = ((100 - a) * cpixel->Red() + a * r) / 100;
					G = ((100 - a) * cpixel->Green() + a * g) / 100;
					B = ((100 - a) * cpixel->Blue() + a * b) / 100;
					cpixel->RGB(R, G, B);
				}
			}
		}
	}
}

void Forme::drawLine(int _x1, int _y1, int _x2, int _y2)
{
	int x1, y1, x2, y2;
	int w, h;
	int ymin;

	if(_x1 > _x2)
	{
		x1 = _x2;
		y1 = _y2;
		x2 = _x1;
		y2 = _y1;
	}
	else
	{
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	}

	w = x2 - x1 + 1;

	if(y1 > y2)
	{
		ymin = y2;
		h = y1 - y2 + 1;
	}
	else
	{
		ymin = y1;
		h = y2 - y1 + 1;
	}

	float slope = (float)(y2 - y1)/(x2 - x1);

	if(slope < 1.0f && slope > -1.0f)
	{
		for(int i = 0; i < h; i++)
		{
			for(int j = 0; j < w; j++)
			{
				if((int)j*slope == i + ymin - y1)
					shape_pixels[(i + ymin) * width + j + x1] = 1;
				else
					shape_pixels[(i + ymin) * width + j + x1] = 0;
			}
		}
	}
	else
	{
		for(int i = 0; i < h; i++)
		{
			for(int j = 0; j < w; j++)
			{
				if(j == (int)(i + ymin - y1)/slope)
					shape_pixels[(i + ymin) * width + j + x1] = 1;
				else
					shape_pixels[(i + ymin) * width + j + x1] = 0;
			}
		}
	}
}


Point::Point(int _x, int _y, float _scale_factor)
{
	setDrawingArea(_x, _y, _scale_factor);
	draw();
}

Point::Point()
{

}

void Point::setDrawingArea(int _x, int _y, float _scale_factor)
{
	x = _x * _scale_factor;
	y = _y * _scale_factor;
	width = 1;
	height = 1;
	if(shape_pixels)
		delete shape_pixels;
	shape_pixels = new bool;
}

void Point::draw()
{
	shape_pixels[0] = 1;
}

Ligne::Ligne(int _x_orig, int _y_orig, int _x_end, int _y_end, float _scale_factor)
{
	setDrawingArea(_x_orig, _y_orig, _x_end, _y_end, _scale_factor);
	draw();
}

Ligne::Ligne()
{

}

void Ligne::setDrawingArea(int _x_orig, int _y_orig, int _x_end, int _y_end, float _scale_factor)
{
	if(_x_orig < _x_end)
	{
		x_orig = _x_orig;
		y_orig = _y_orig;
		x_end = _x_end;
		y_end = _y_end;
	}
	else
	{
		x_orig = _x_end;
		y_orig = _y_end;
		x_end = _x_orig;
		y_end = _y_orig;
	}
	x_orig *= _scale_factor;
	y_orig *= _scale_factor;
	x_end *= _scale_factor;
	y_end *= _scale_factor;

	x = x_orig;
	width = x_end - x_orig + 1;

	if(y_orig < y_end)
	{
		y = y_orig;
		height = y_end - y_orig + 1;
	}
	else
	{
		y = y_end;
		height = y_orig - y_end + 1;
	}

	if(shape_pixels != NULL)
		delete shape_pixels;
	shape_pixels = new bool [width * height];
}

void Ligne::draw()
{
	drawLine(0, y_orig - y, width - 1, y_end - y);
}

Rectangle::Rectangle(int _x, int _y, int _w, int _h, float _scale_factor)
{
	setDrawingArea(_x, _y, _w, _h, _scale_factor);
	draw();
}

Rectangle::Rectangle()
{

}

void Rectangle::setDrawingArea(int _x, int _y, int _w, int _h, float _scale_factor)
{
	x = _x * _scale_factor;
	y = _y * _scale_factor;
	width = _w * _scale_factor;
	height = _h * _scale_factor;

	if(shape_pixels != NULL)
		delete shape_pixels;
	shape_pixels = new bool [width * height];
}

void Rectangle::draw()
{
	drawLine(0, 0, width - 1, 0);
	drawLine(width - 1, 0, width - 1, height - 1);
	drawLine(width - 1, height - 1, 0, height - 1);
	drawLine(0, height - 1, 0, 0);
}

RectangleS::RectangleS(int _x, int _y, int _w, int _h, float _scale_factor)
{
	setDrawingArea(_x, _y, _w, _h, _scale_factor);
	draw();
}

RectangleS::RectangleS()
{

}

void RectangleS::draw()
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			shape_pixels[i * width + j] = 1;
		}
	}
}

Carre::Carre(int _x, int _y, int _w, float _scale_factor)
{
	setDrawingArea(_x, _y, _w, _w, _scale_factor);
	draw();
}

Carre::Carre()
{

}

CarreS::CarreS(int _x, int _y, int _w, float _scale_factor)
{
	setDrawingArea(_x, _y, _w, _w, _scale_factor);
	draw();
}

CarreS::CarreS()
{

}

Cercle::Cercle(int _x, int _y, int _radius, float _scale_factor)
{
	setDrawingArea(_x, _y, _radius, _scale_factor);
	draw();
}

Cercle::Cercle()
{

}

void Cercle::setDrawingArea(int _x, int _y, int _radius, float _scale_factor)
{
	radius = _radius * _scale_factor;
	x_center = _x * _scale_factor;
	y_center = _y * _scale_factor;

	x = x_center - radius;
	y = y_center - radius;
	width = 2 * radius + 2;
	height = 2 * radius + 2;

	if(shape_pixels != NULL)
		delete shape_pixels;
	shape_pixels = new bool [width * height];
}

void Cercle::draw()
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(dist(x_center, y_center, x + j, y + i) == radius)
				shape_pixels[width * i + j] = 1;
			else
				shape_pixels[width * i + j] = 0;
		}
	}
}

CercleS::CercleS(int _x, int _y, int _radius, float _scale_factor)
{
	setDrawingArea(_x, _y, _radius, _scale_factor);
	draw();
}

CercleS::CercleS()
{

}

void CercleS::draw()
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(dist(x_center, y_center, x + j, y + i) <= radius)
				shape_pixels[width * i + j] = 1;
			else
				shape_pixels[width * i + j] = 0;
		}
	}
}

int dist(int x1, int y1, int x2, int y2)
{
	return (int)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
