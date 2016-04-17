using namespace std;

#include <stdio.h>
#include <stdlib.h>

#include "forme.h"
#include "image.h"

int main(int argc, char* argv[])
{
	Image image(640, 480);	

	Ligne ligne1(100, 200, 200, 100);
	Ligne ligne2(100, 100, 300, 300);
	ligne2.setColor(0, 255, 200, 255);
	Ligne ligne3(100, 250, 600, 250);
	ligne3.setColor(255, 0, 0, 255);
	Ligne ligne4(300, 50, 300, 400);
	ligne4.setColor(200, 0, 200, 255);
	Rectangle rectangle(40, 40, 560, 400);
	Point point(500, 400);
	Carre carre(50, 50, 100);

	image.newForme(&ligne1);
	image.newForme(&ligne2);
	image.newForme(&ligne3);
	image.newForme(&ligne4);
	image.newForme(&rectangle);
	image.newForme(&point);
	image.newForme(&carre);

	image.draw();
	image.output("output.bmp");

	return 0;
}
