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
	Forme(const Forme &);
	~Forme();
    void setColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);
    void copyAttrib(int* _x, int* _y, int* _width, int* _height, unsigned char* _r, unsigned char* _g, unsigned char* _b, unsigned char* _a) const;
    void copyShape(bool* _shape_pixels) const;
    int getXOrig();
    int getYOrig();
    int getXMax();
    int getYMax();
    void translate(int _x, int _y);
    void draw(CImage* cimage, int _image_width, int _image_height);
};


class Point : public Forme
{
public:
	Point(int _x, int _y, float _scale_factor = 1.0f);
	Point();
	void setDrawingArea(int _x, int _y, float _scale_factor = 1.0f);
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
	Ligne(int _x_orig, int _y_orig, int _x_end, int _y_end, float _scale_factor = 1.0f);
	Ligne();
	void setDrawingArea(int _x_orig, int _y_orig, int _x_end, int _y_end, float _scale_factor = 1.0f);
	void draw();
};


class Rectangle : public Forme
{
public:
	Rectangle(int _x, int _y, int _w, int _h, float _scale_factor = 1.0f);
	Rectangle();
	void setDrawingArea(int _x, int _y, int _w, int _h, float _scale_factor = 1.0f);
	void draw();
};

class RectangleS : public Rectangle
{
public:
	RectangleS(int _x, int _y, int _w, int _h, float _scale_factor = 1.0f);
	RectangleS();
	void draw();
};

class Carre : public Rectangle
{
public:
	Carre(int _x, int _y, int _w, float _scale_factor = 1.0f);
	Carre();
};

class CarreS : public RectangleS
{
public:
	CarreS(int _x, int _y, int _w, float _scale_factor = 1.0f);
	CarreS();
};

class Cercle : public Forme
{
protected:
	int x_center;
	int y_center;
	int radius;

public:
	Cercle(int _x, int _y, int _radius, float _scale_factor = 1.0f);
	Cercle();
	void setDrawingArea(int _x, int _y, int _radius, float _scale_factor = 1.0f);
	void draw();
};

class CercleS : public Cercle
{
public:
	CercleS(int _x, int _y, int _radius, float _scale_factor = 1.0f);
	CercleS();
	void draw();
};

int dist(int x1, int y1, int x2, int y2);

#endif
