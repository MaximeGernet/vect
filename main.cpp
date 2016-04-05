#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	Image image(640, 480);	
	Forme forme;
	
	image.newForme(&forme);
	image.draw();
	image.output();
}