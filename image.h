using namespace std;

#ifndef IMAGE_H_
#define IMAGE_H_

#include "CImage/CImage.h"

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
	string output_file;
	string input_file;

	//priority_queue<Forme, vector<Forme>, comparaison> queue;
	vector<Forme> list;

	float scale_factor;
	int ref_width;
	int ref_height;

public:
	Image(int _width, int _height);
	~Image();
	void newForme(Forme* _forme);
	void draw();
	void output();
};









#endif