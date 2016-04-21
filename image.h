using namespace std;

#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include <vector>

#include "CImage/CImage.h"
#include "CImage/CBitmap.h"

/*
class comparaison
{
public:
	bool operator() (const Forme& lhs, const Form& rhs) const
	{
		return (lhs>rhs);
	}
};
*/
/*
bool comparaison() (const Forme& lhs, const Form& rhs) const
{
	return lhs.priority < rhs.priority;
}
*/

class Image
{
private:
	CImage* cimage;
	CBitmap cbitmap;

	//priority_queue<Forme, vector<Forme>, comparaison> queue;
	vector<Forme*> list;

	float scale_factor;
	int ref_width;
	int ref_height;

	unsigned char background_r;
	unsigned char background_g;
	unsigned char background_b;

public:
	Image(int _width, int _height, float _scale_factor = 1.0f);
	~Image();
	void setBackgroundColor(unsigned char _r, unsigned char _g, unsigned char _b);
	void setScaleFactor(float _scale_factor);

	float scale();

	void newForme(Forme* _forme);
	void draw();
	void output(string _output_file);
};









#endif
