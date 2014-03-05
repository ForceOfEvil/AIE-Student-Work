#ifndef _PHYSICS_H_
#define _PHYSICS_H_

//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Physics.h
//		@details		Physics functions
//		@author			Derek Potter
//		@date created	2/10/2014
//////////////////////////////////////////////////////////////////////////

#include "Sprite.h"

const float cfGravity = -.001f;

class oPhysics
{

public:

	oPhysics();
	~oPhysics();

	void RunTopDown(bool a_bLeft, bool a_bRight, bool a_bUp, bool a_bDown);

	void RunSideScroll(bool a_bLeft, bool a_bRight, bool a_bJump);

	int ScreenCollision();

	void Input(bool a_bTopDown);

	oSprite pSprite;

	oVector2 m_v2Velocity;

	oVector2 m_v2SurfaceArea;

	oVector2 m_v2DampingForce;

	oVector4 m_v4Acceleration;

	bool m_bOnGround;

	float m_fMass;

};

#endif