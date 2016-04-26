using namespace std;

#include <stdio.h>
#include <stdlib.h>

#include "forme.h"
#include "image.h"

#define REF_WIDTH	640
#define REF_HEIGHT	480

int main(int argc, char* argv[])
{
	Image image(REF_WIDTH, REF_HEIGHT, 1.0f);
	/*
	Ligne ligne1(100, 200, 200, 100, image.getScale());
	Ligne ligne2(100, 100, 300, 300, image.getScale());
	ligne2.setColor(0, 255, 200, 100);
	Ligne ligne3(100, 250, 600, 250, image.getScale());
	ligne3.setColor(255, 0, 0, 100);
	Ligne ligne4(300, 50, 300, 400, image.getScale());
	ligne4.setColor(200, 0, 200, 100);
	Rectangle rectangle(40, 40, 560, 400, image.getScale());
	Point point(500, 400, image.getScale());
	Carre carre(50, 50, 100, image.getScale());
	Cercle cercle(640/2, 480/2, 100, image.getScale());
	RectangleS rectangleS(200, 100, 200, 20, image.getScale());
	rectangleS.setColor(255, 0, 0, 25);
	CarreS carreS(200, 150, 20, image.getScale());
	carreS.setColor(0, 255, 200, 25);
	CercleS cercleS(640/2 - 100, 480/2, 50, image.getScale());
	cercleS.setColor(0, 50, 255, 25);



	image.newForme(ligne1);
	image.newForme(ligne2);
	image.newForme(ligne3);
	image.newForme(ligne4);
	image.newForme(rectangle);
	image.newForme(point);
	image.newForme(carre);
	image.newForme(cercle);
	image.newForme(rectangleS);
	image.newForme(carreS);
	image.newForme(cercleS);
	*/
	image.readFile("input.vec");
	image.draw();
	image.output("output.bmp");

	return 0;
}
