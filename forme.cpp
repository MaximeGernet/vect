#include "forme.h"



Forme::Forme()
{
	;
}

Forme::~Forme()
{
	;
}

void Forme::Display(CImage* newImage)
{
    CPixel* newPixel ;
    for(int i = 0; i < (width - x); i++)
	{
        for(int j = 0; j < (length - y); j++)
		{
			if 
			newPixel = newImage->getPixel(x + i, y + j);
            newPixel->RGB(red, green, blue);
		}
    }
}

Point::Point()
{
 	a = new bool[1];
 	a = 1;
}

Point::~Point()
{
	delete a;			
}

Ligne::Ligne(x_org, y_org, x_end, y_end)
{
	if (x_org < x_end)
		width = x_end - x_org;
	else
		width = x_org - x_end;

	if (y_org < y_end)
		height = y_end - y_org;
	else
		height = y_org - y_end;

	a = new bool[width*height];
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			if (i == j *(float)height/width)
				a[i*width + j] = true;
			else
				a[i*width + j] = false;
		}
	}
}

Ligne::~Ligne(){
	delete a;
}

