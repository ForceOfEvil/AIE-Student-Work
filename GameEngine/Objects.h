#ifndef _OBJECTS_H_
#define _OBJECTS_H_

//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Objects.h
//		@details		The Objects Class
//		@author			Derek Potter
//		@date created	2/19/2014
//////////////////////////////////////////////////////////////////////////

#include "Physics.h"

class oObject{

public:

	oObject();
	~oObject();
	oObject(const char* a_pTexture, int a_iWidth, int a_iHeight, oVector4 a_v4Color,GLFWwindow*);
	
	void PhysicsSetup(oVector4 a_v4Acceleration, oVector3 a_v3Position, oVector2 a_v2SurfaceArea, oVector2 a_v2DampingForce, float a_fMass);

	void Draw();
	void UpdatePosition();

	oPhysics m_pPhysics;

};

#endif