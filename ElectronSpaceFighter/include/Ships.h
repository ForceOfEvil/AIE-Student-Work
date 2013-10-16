//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Ships.h
//		@details		The Ships Class
//		@author			Derek Potter
//		@date created	10/15/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _SHIPS_H_
#define _SHIPS_H_

#include "Vector2D.h"
#include "Timer.h"
#include "Objects.h"

struct oFiveTimers{

	oTimer ptCenter;
	oTimer ptOne;
	oTimer ptTwo;
	oTimer ptThree;
	oTimer ptFour;

};

struct oFourVectors{

	oVector pvFireOne;
	oVector pvFireTwo;
	oVector pvFireThree;
	oVector pvFireFour;

};

struct oFiveMovements{

	teMovementPatterns empCenterMove;
	teMovementPatterns empPosOneMove;
	teMovementPatterns empPosTwoMove;
	teMovementPatterns empPosThreeMove;
	teMovementPatterns empPosFourMove;
};

class oShips
{
public:

	oObjects poData;

	//the positions where bullets come from, and the ships starting position
	oFourVectors pfvPositions;

	//makes sure the enemy does not fire until it is were it needs to be
	oFiveTimers pftTimeToFire;

	//fire rate
	oFiveTimers pftFireRate;

	//So the enemy isn't deleted before it gets of screen and so it knows when to leave the screen
	oTimer ptCanDestroy;

	oFiveMovements pfmMoveStyle;

	//used to check if the ship fires from the center or just its fire positions
	bool bCenterFire;

	oShips();
	void oShips::a_Inisialize(unsigned int uiSprite, int iWide, int iTall, unsigned long ulPositions[10], bool bFireFromCenter);
	void oShips::a_Kill();
	void oShips::Create(unsigned int uiSprite, int iWide, int iTall, float fPosX, float fPosY, float fSpeedX, float fSpeedY, oFourVectors pfvFirePositions, 
				oFiveTimers pftRateOfFire, oFiveTimers pftFireTimer, bool bFireFromCenter, unsigned long ulDestroyTime, oFiveMovements pfmBulletMoveStyles);
	~oShips();

};


#endif