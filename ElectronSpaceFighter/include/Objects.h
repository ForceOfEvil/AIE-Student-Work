//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Objects.h
//		@details		The Objects Class
//		@author			Derek Potter
//		@date created	10/15/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "Vector2D.h"

typedef enum teMovementPatterns
{

	//Type One (used by small and smaller medium enemies)
	DiagionalIntro = 1,
	QuickSineY = 2,
	QuickSineX = 3,
	StayInFront = 4,

	//Type Two (used by medium and large enemies)
	BackIntroAndFlip = 5,
	//Down, Stay, Shoot, then go
	DSSG = 6,
	GetInFront = 7,
	SideApperence = 8,

	//Boss MoveTypes
	FloatAround = 9,
	TargetPlayer = 10,
	MoveToSpot = 11,
	AngryMove = 12,

	//Bullet Movement Types

	//Straight Shots (ammount of bullets per shot)
	StraightOne = 13,
	StraightTwo = 14,
	StraightThree = 15,
	StraightFour = 16,

	//Sine Shots (sine amplitude)
	SineShotSmall = 17,
	SineShotMid = 18,
	SineShotLarge = 19,

	//Circle Shots
	CircleSparse = 20,
	CircleHoled = 21,
	CircleTight = 22

};

class oObjects
{

public:

	oObjects();
	oVector pPosition;
	oVector pSpeed;
	void oObjects::a_Update();
	void oObjects::a_Inisialize(unsigned int uiSetSprite, int iStartPosX, int iStartPosY, int iWide, int iTall);
	void oObjects::a_Draw();
	void oObjects::a_SetSprite(unsigned int uiNewSprite);
	void oObjects::a_SetDimensions(int iX, int iY);
	void oObjects::a_SetMovement(teMovementPatterns & rempMove);
	teMovementPatterns oObjects::a_GetMovement();
	void oObjects::a_Kill();
	void oObjects::a_Create(float fPosX, float fPosY, float fSpeedX, float fSpeedY, unsigned int uiNewSprite);
	~oObjects();


private:

	unsigned int uiSprite;
	int iWidth;
	int iHeight;
	bool bAlive;
	teMovementPatterns empMove;

};


#endif