//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Functions.h
//		@details		The functions (collision and vector math) for ElectronSpaceFighter
//		@author			Derek Potter
//		@date created	9/30/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "Objects.h"
#include "Timer.h"

//////////////////////////////////////////////////////////////////////////
//		@breif			Keeps track of a ships info, such as an oObjects, its start position
//						its rate of fire, when it should fire, and when it should leave
//		@class			oShips
//////////////////////////////////////////////////////////////////////////
struct oShips{

	oObjects poData;

	//the positions where bullets come from, and the ships starting position
	oFiveVectors pfvPositions;

	//makes sure the enemy does not fire until it is were it needs to be
	oFiveTimers pftTimeToFire;

	//fire rate
	oFiveTimers pftFireRate;

	//So the enemy isn't deleted before it gets of screen and so it knows when to leave the screen
	oTimer ptCanDestroy;

	//used to check if the ship fires from the center or just its fire positions
	bool bCenterFire;

	//Movement patterns for bullets based on where it fire from
	teMovementPatterns empCenterMove;
	teMovementPatterns empPosOneMove;
	teMovementPatterns empPosTwoMove;
	teMovementPatterns empPosThreeMove;
	teMovementPatterns empPosFourMove;

};

void a_Initializer();

void a_Menu();
void a_GameRunner();

void a_MovePlayer();

void a_StarMover();

int a_iTestScreenCollision(oObjects & rpObj);

void a_WinLose();
void a_UpDateGame();
void a_DrawGame();

void a_FireBullet(oShips & rpObj, oVector & rpPositionOne, oVector & rpPositionTwo, oVector & rpPositionThree, oVector & rpPositionFour, bool bIsPlayer);
void a_MoveBullets();

void a_MoveEnemy();
void a_SpawnEnemy();


#endif