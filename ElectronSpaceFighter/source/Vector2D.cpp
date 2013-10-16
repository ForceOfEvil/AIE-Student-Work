#include "Vector2D.h"



oVector::oVector(){

	fX = 0;
	fY = 0;

}

float oVector::a_fGetVectorX(){

	return fX;

}

float oVector::a_fGetVectorY(){

	return fY;

}

void oVector::a_SetVector(float fXB, float fYB){

	fX = fXB;
	fY = fYB;

}

void oVector::a_VectorAdd(oVector & rpPos, oVector & rpSpeed){

	rpPos.a_SetVector(rpSpeed.a_fGetVectorX(), rpSpeed.a_fGetVectorY()); 

}

oVector::~oVector(){

	//Gru

}