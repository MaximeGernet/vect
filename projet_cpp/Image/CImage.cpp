/*
 *  CImage.cpp
 *  P_Bitmap
 *
 *  Created by Le Gal on 24/10/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "CImage.h"

CImage::CImage(int hauteur, int largeur){
	taille = hauteur;
	liste = new CLigne*[taille];
	for(int i=0; i<taille; i++){
		liste[i] = new CLigne(largeur);
	}
}

CImage::~CImage(){
	for(int i=0; i<taille; i++)
		delete liste[i];
	delete liste;
}

int CImage::size(){
	return taille;
}

CLigne* CImage::getLigne(int position){
	if( (position >= taille) ){
		cout << "CImage::getLigne => trying to access " << position << " but the line has only " << taille << " data" << endl;
	}
	return (position < taille)?liste[position]:NULL;
}

CPixel* CImage::getPixel(int posX, int posY){
	CLigne* ligne =  getLigne( posY );
	if( ligne == NULL){
		cout << "CImage::getPixel => trying to access (" << posX << ", " << posY << ") but the line has only " << taille << " data" << endl;
		return NULL;
	}
	return ligne->getPixel(posX);
}
