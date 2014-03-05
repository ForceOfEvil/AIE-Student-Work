//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Globals.h
//		@details		global variables (just to clean up functions.cpp)
//		@author			Derek Potter
//		@date created	10/16/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _OTHERGLOBALS_H_
#define _OTHERGLOBALS_H_

#include "Mathmatics.h"
#include "Timer.h"
#include "Objects.h"

//star stuff
const int ciStarArraySize = 30;
const int ciStarYSpread = 1000;
const float cfStarSpeed = .5;
const int ciSmallStarDimensions = 3;
const int ciMediumStarDimensions = 4;
const int ciLargeStarDimensions = 5;

//Player stuff
const float cfPlayerSpeed = 2;
const int ciPlayerHeight = 50;
const int ciPlayerWidth = 50;
const int ciPlayerStartY = 700;
int iPlayerFirePositions[4] = {15,-5, -15,-5};
unsigned long ulPlayerFireRate = 30;
unsigned long ulNullTimeToFire = 0;
//oFiveMovements pfmPlayerShipDefaultMovements;

//Enemy stuff
const int ciEnemyStartPosition = -200;

const float cfSmallEnemyBasicSpeed = .1;
const float cfMediumEnemyBasicSpeed = .5;
const float cfLargeEnemyBasicSpeed = .25;

const int ciSmallEnemyDimensions = 30;
const int ciMediumEnemyDimensions = 50;
const int ciLargeEnemyDimensions = 70;

int iSmallEnemyFirePosOne[4] = {5,0, -5,0};

unsigned long ulEnemyFireRate = 100;
unsigned long ulTimeToFireSmallEnemies = 500;
unsigned long ulSmallEnemyDestroyTime = 400;

const int ciEnemyNumbers = 5;

//bullet stuff
const int ciArraySize = 1000;
const float cfBulletSpeed = 5;
const int ciBulletDimensions = 10;
int iBulletReminder[20];

// Timers and const for timers
oTimer ptLevelTimer;
oTimer ptSmallEnemySpawn;
const unsigned long culSineTimerEnd = 62;
oTimer ptRadialFireTimer;
const unsigned long culRadialTimerEnd = 360;

//////////////////////////////////////////////////////////////////////////
//		Initializing all the objects and their settings, and game global variables
//////////////////////////////////////////////////////////////////////////
char * rcPlayerShip = "./images/Ship.png";
char * rcEnemyShips = "./images/EnemyShip.png";
char * rcStar = "./images/Star.png";
char * rcBackground = "./images/Background.png";
char * rcMenu = "./images/MainMenu.png";
char * rcControls = "./images/Controls.png";
char * rcGameOver = "./images/GameOver.png";
char * rcGameMenu = "./images/Menu.png";
char * rcLevelOne = "./images/LevelOne.png";

unsigned int uiControls = -1;
unsigned int uiGameOver = -1;
unsigned int uiGameMenu = -1;
unsigned int uiMenu = -1;

//player ship (contains an oObjects, oVectors, and oTimers)
oPlayer pPlayer;

//star array objects
oObjects poSmallStar[ciStarArraySize];
oObjects poMediumStar[ciStarArraySize];
oObjects poLargeStar[ciStarArraySize];

//bullet array objects
oObjects poEnemyBullets[ciArraySize];
oObjects poPlayerBullets[ciArraySize];

//enemy array ships (contains an oObjects, oVectors, and oTimers)
oObjects poSmallEnemies[ciEnemyNumbers];
oObjects poMediumEnemies[ciEnemyNumbers];
oObjects poLargeEnemies[ciEnemyNumbers];

//Background, Menu, and other misc objects
oObjects poBackground;
oObjects poLevel;
oObjects poMenu;

#endif