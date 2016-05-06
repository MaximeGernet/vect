using namespace std;

#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include <vector>
#include <queue>

#include "CImage/CImage.h"
#include "CImage/CBitmap.h"


class comparaison
{
public:
	bool operator() (const Forme* lhs, const Forme* rhs) const
	{
		return (lhs->getPriority() > rhs->getPriority());
	}
};

/*
bool comparaison() (const Forme& lhs, const Forme& rhs) const
{
	if(lhs.priority < rhs.priority)
		return true;
	else
		return false;
}
*/


class Image
{
private:
	CImage* cimage;
	CBitmap cbitmap;

	priority_queue<Forme*, vector<Forme*>, comparaison> queue;

	float scale_factor;
	int ref_width;	// image width
	int ref_height;	// image height

	unsigned char background_r;
	unsigned char background_g;
	unsigned char background_b;

public:
	Image(int _width, int _height, float _scale_factor = 1.0f);
	~Image();
	void setBackgroundColor(unsigned char _r, unsigned char _g, unsigned char _b);
	void setScaleFactor(float _scale_factor);
	void fit();

	float getScale();

	void newForme(Forme* _forme);
	void scale(float _scale_factor);
	void translate(int _x, int _y);
	void draw();
	void output(string _output_file);

	void readFile(string file_name);
	void cutString(string c, string* buf);
};









#endif
