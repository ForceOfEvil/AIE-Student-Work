//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Vector2D.h
//		@details		The vector and its functions
//		@author			Derek Potter
//		@date created	9/30/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

class oVector
{

public:

	oVector();
	float oVector::a_fGetVectorX();
	float oVector::a_fGetVectorY();
	void oVector::a_SetVector(float fXB, float fYB);
	void oVector::a_VectorAdd(oVector & rpPos, oVector & rpSpeed);
	~oVector();

private:

	float fX;
	float fY;

};

#endif