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
	Cercle cercle(640/2, 480/2, 100);

	RectangleS rectangleS(200, 100, 200, 20);
	CarreS carreS(200, 150, 20);
	CercleS cercleS(640/2, 480/2, 50);

	image.newForme(&ligne1);
	image.newForme(&ligne2);
	image.newForme(&ligne3);
	image.newForme(&ligne4);
	image.newForme(&rectangle);
	image.newForme(&point);
	image.newForme(&carre);
	image.newForme(&cercle);
	image.newForme(&rectangleS);
	image.newForme(&carreS);
	image.newForme(&cercleS);

	image.draw();
	image.output("output.bmp");

	return 0;
}
