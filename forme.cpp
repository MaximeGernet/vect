using namespace std;

#include <math.h>
#include <string.h>

#include "CImage/CImage.h"
#include "CImage/CPixel.h"

#include "forme.h"


Forme::Forme()
{
	setColor(255, 255, 255, 100);
	priority = high_priority;
	high_priority++;
}

/*
Forme::Forme(const Forme &source)
{

}
*/


Forme::~Forme()
{

}


void Forme::setColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

int Forme::getXMin()
{
	return x;
}

int Forme::getYMin()
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

int Forme::getPriority() const
{
	return priority;
}

void Forme::translate(int _x, int _y)
{
	x += _x;
	y += _y;
}

void Forme::colorPixel(CImage* _cimage, int _x, int _y, int _image_width, int _image_height)
{
	if(_x >= 0 && _x < _image_width && _y >= 0 && _y < _image_height)
	{
		CPixel* cpixel = _cimage->getPixel(_x, _y);
		unsigned char R, G, B;
		R = ((100 - a) * cpixel->Red() + a * r) / 100;
		G = ((100 - a) * cpixel->Green() + a * g) / 100;
		B = ((100 - a) * cpixel->Blue() + a * b) / 100;
		cpixel->RGB(R, G, B);
	}
}

void Forme::draw(CImage* _cimage, int _image_width, int _image_height)
{

};

void Forme::set()
{

}

void Forme::scale()
{

}


Point::Point(int _x, int _y, float _scale_factor)
{
	set(_x, _y, _scale_factor);
}

Point::Point()
{

}

void Point::set(int _x, int _y, float _scale_factor)
{
	x = _x * _scale_factor;
	y = _y * _scale_factor;
	width = 1;
	height = 1;
}

void Point::draw(CImage* _cimage, int _image_width, int _image_height)
{
	colorPixel(_cimage, x, y, _image_width, _image_height);
}

Ligne::Ligne(int _x_orig, int _y_orig, int _x_end, int _y_end, float _scale_factor)
{
	set(_x_orig, _y_orig, _x_end, _y_end, _scale_factor);
}

Ligne::Ligne()
{

}

void Ligne::set(int _x_orig, int _y_orig, int _x_end, int _y_end, float _scale_factor)
{
	x_orig = _x_orig * _scale_factor;
	y_orig = _y_orig * _scale_factor;
	x_end = _x_end * _scale_factor;
	y_end = _y_end * _scale_factor;

	if(x_orig < x_end)
	{
		x = x_orig;
		width = x_end - x_orig + 1;
	}
	else
	{
		x = x_end;
		width = x_orig - x_end + 1;
	}

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
}

void Ligne::draw(CImage* _cimage, int _image_width, int _image_height)
{
	int x1, y1, x2, y2;

	if(x_orig > x_end)
	{
		x1 = x_end;
		y1 = y_end;
		x2 = x_orig;
		y2 = y_orig;
	}
	else
	{
		x1 = x_orig;
		y1 = y_orig;
		x2 = x_end;
		y2 = y_end;
	}

	float slope = (float)(y2 - y1)/(x2 - x1);

	if(slope < 1.0f && slope > -1.0f)
	{
		for(int i = x1; i <= x2; i++)
		{
			colorPixel(_cimage, i, y1 + slope * (i - x1), _image_width, _image_height);
		}
	}
	else
	{
		if(y1 < y2)
		{
			for(int i = y1; i <= y2; i++)
			{
				colorPixel(_cimage, x1 + (i - y1) / slope, i, _image_width, _image_height);
			}
		}
		else
		{
			for(int i = y2; i <= y1; i++)
			{
				colorPixel(_cimage, x2 + (i - y2) / slope, i, _image_width, _image_height);
			}
		}
	}
}

Rectangle::Rectangle(int _x, int _y, int _w, int _h, float _scale_factor)
{
	set(_x, _y, _w, _h, _scale_factor);
}

Rectangle::Rectangle()
{

}

void Rectangle::set(int _x, int _y, int _w, int _h, float _scale_factor)
{
	x = _x * _scale_factor;
	y = _y * _scale_factor;
	width = _w * _scale_factor;
	height = _h * _scale_factor;
}

void Rectangle::draw(CImage* _cimage, int _image_width, int _image_height)
{
	for(int i = 0; i < width; i++)
	{
		colorPixel(_cimage, x + i, y, _image_width, _image_height);
	}

	for(int i = 0; i < width; i++)
	{
		colorPixel(_cimage, x + i, y + height - 1, _image_width, _image_height);
	}

	for(int i = 0; i < height; i++)
	{
		colorPixel(_cimage, x, y + i, _image_width, _image_height);
	}

	for(int i = 0; i < height; i++)
	{
		colorPixel(_cimage, x + width - 1, y + i, _image_width, _image_height);
	}
}

RectangleS::RectangleS(int _x, int _y, int _w, int _h, float _scale_factor)
{
	set(_x, _y, _w, _h, _scale_factor);
}

RectangleS::RectangleS()
{

}

void RectangleS::draw(CImage* _cimage, int _image_width, int _image_height)
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			colorPixel(_cimage, x + j, y + i, _image_width, _image_height);
		}
	}
}

Carre::Carre(int _x, int _y, int _w, float _scale_factor)
{
	set(_x, _y, _w, _w, _scale_factor);
}

Carre::Carre()
{

}

CarreS::CarreS(int _x, int _y, int _w, float _scale_factor)
{
	set(_x, _y, _w, _w, _scale_factor);
}

CarreS::CarreS()
{

}

Cercle::Cercle(int _x, int _y, int _radius, float _scale_factor)
{
	set(_x, _y, _radius, _scale_factor);
}

Cercle::Cercle()
{

}

void Cercle::set(int _x, int _y, int _radius, float _scale_factor)
{
	radius = _radius * _scale_factor;
	x_center = _x * _scale_factor;
	y_center = _y * _scale_factor;

	x = x_center - radius;
	y = y_center - radius;
	width = 2 * radius + 2;
	height = 2 * radius + 2;
}

void Cercle::draw(CImage* _cimage, int _image_width, int _image_height)
{
	CPixel* cpixel;
	unsigned char R, G, B;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(dist(x_center, y_center, x + j, y + i) == radius)
			{
				colorPixel(_cimage, x + j, y + i, _image_width, _image_height);
			}
		}
	}
}

CercleS::CercleS(int _x, int _y, int _radius, float _scale_factor)
{
	set(_x, _y, _radius, _scale_factor);
}

CercleS::CercleS()
{

}

void CercleS::draw(CImage* _cimage, int _image_width, int _image_height)
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if(dist(x_center, y_center, x + j, y + i) <= radius)
			{
				colorPixel(_cimage, x + j, y + i, _image_width, _image_height);
			}
		}
	}
}

int dist(int x1, int y1, int x2, int y2)
{
	return (int)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
