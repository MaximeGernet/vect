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
	int priority;

    void drawLine(int _x1, int _y1, int _x2, int _y2);

public:
	static int high_priority;
	static int low_priority;

	Forme();
	//Forme(const Forme &);
	virtual ~Forme();
    void setColor(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 100);
    int getXMin();
    int getYMin();
    int getXMax();
    int getYMax();
    int getPriority() const;
    void translate(int _x, int _y);
    void colorPixel(CImage* _cimage, int _x, int _y, int _image_width, int _image_height);
    virtual void draw(CImage* _cimage, int _image_width, int _image_height);
    virtual void set();
    virtual void scale();
};


class Point : public Forme
{
public:
	Point(int _x, int _y, float _scale_factor = 1.0f);
	Point();
	void set(int _x, int _y, float _scale_factor = 1.0f);
	void draw(CImage* _cimage, int _image_width, int _image_height);
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
	void set(int _x_orig, int _y_orig, int _x_end, int _y_end, float _scale_factor = 1.0f);
	void draw(CImage* _cimage, int _image_width, int _image_height);
};


class Rectangle : public Forme
{
public:
	Rectangle(int _x, int _y, int _w, int _h, float _scale_factor = 1.0f);
	Rectangle();
	void set(int _x, int _y, int _w, int _h, float _scale_factor = 1.0f);
	void draw(CImage* _cimage, int _image_width, int _image_height);
};

class RectangleS : public Rectangle
{
public:
	RectangleS(int _x, int _y, int _w, int _h, float _scale_factor = 1.0f);
	RectangleS();
	void draw(CImage* _cimage, int _image_width, int _image_height);
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
	void set(int _x, int _y, int _radius, float _scale_factor = 1.0f);
	void draw(CImage* _cimage, int _image_width, int _image_height);
};

class CercleS : public Cercle
{
public:
	CercleS(int _x, int _y, int _radius, float _scale_factor = 1.0f);
	CercleS();
	void draw(CImage* _cimage, int _image_width, int _image_height);
};

int dist(int x1, int y1, int x2, int y2);

#endif
