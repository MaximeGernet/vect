using namespace std;

#ifndef FORME_H_
#define FORME_H_

#include "CImage/CImage.h"

class Forme
{
protected:
	int x;
	int y;
	int width;
	int height;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
	bool* shape_pixels;

    void drawLine(int _x1, int _y1, int _x2, int _y2);

public:
	Forme();
	~Forme();
    void setColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);
    void draw(CImage* cimage);
};


class Point : public Forme
{
public:
	Point(int _x, int _y);
	void draw();
};

class Ligne : public Forme
{
private:
	int x_orig;
	int y_orig;
	int x_end;
	int y_end;

public:
	Ligne(int _x_orig, int _y_orig, int _x_end, int _y_end);
	void setDrawingArea(int _x_orig, int _y_orig, int _x_end, int _y_end);
	void draw();
};


class Rectangle : public Forme
{
public:
	Rectangle(int _x, int _y, int _w, int _h);
	Rectangle();
	void setDrawingArea(int _x, int _y, int _w, int _h);
	void draw();
};

class Carre : public Rectangle
{
public:
	Carre(int _x, int _y, int _w);
};

#endif
