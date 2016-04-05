#include "./Image/CLigne.h"
#include "./Image/CPixel.h"
#include "./Image/CImage.h"


class Forme
{
protected:
	CPixel *pixel;
	int transparence;

	int x;
	int y;
	int width;
	int height;
	short red;
	short green;
	short blue;
	 bool *a;

public:
	Forme();
	~Forme();
    void Display(CImage* newImage);
};

class Point : Forme
{
private:

public:
	Point();
	~Point();

};


class Ligne : Forme
{
private:

	int x_end;
	int y_end;
public:
	Ligne(x_org, y_org, x_end, y end);
	~Ligne();
};

class Rectangle : Forme
{
private:
	int length;
	int width;
public:
	Rectangle();
	~Rectangle();
};
