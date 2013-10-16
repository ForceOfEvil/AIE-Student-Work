//////////////////////////////////////////////////////////////////////////
//		@file				Functions.cpp
//		@details			The functions implementations
//		@author				Derek Potter
//		@version			1.0
//		@date last edited	10/8/2013
//////////////////////////////////////////////////////////////////////////

#include "AIE.h"
#include "Functions.h"
#include "Vector2D.h"
#include "Timer.h"
#include "Objects.h"
#include "Ships.h"
#include <math.h>
#include <iostream>

const int ciSCREEN_X = 1280;
const int ciSCREEN_Y = 780;

//Screen collision test returns
const int ciLeftCollision = 1;
const int ciRightCollision = 2;
const int ciTopCollision = 3;
const int ciBottomCollision = 4;

//star stuff
const int ciStarArraySize = 50;
const int ciStarStart = -10;
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
const int ciPlayerFirePositions[8] = {15,-10, -15,-10, 0,0, 0,0};
unsigned long ulPlayerFireRate[5] = {30, 30, 30, 30, 30};

//Enemy stuff
const int ciEnemySartPosition = -200;
const float cfSmallEnemyBasicSpeed = 3;
const float cfMediumEnemyBasicSpeed = 2;
const float cfLargeEnemyBasicSpeed = 1;
const int ciSmallEnemyDimensions = 20;
const int ciMediumEnemyDimensions = 50;
const int ciLargeEnemyDimensions = 70;

//bullet stuff
const float cfBulletSpeed = .6;
const int ciBulletDimensions = 10;
int iBulletReminder[20];

//array sizes ( /5 for player bullets)
const int ciArraySize = 500;
const int ciEnemyNumbers = 20;

// Timers and const for timers
oTimer ptLevelTimer;
oTimer ptSmallEnemySpawn;
oTimer ptSineTimer;
const unsigned long culSineTimerEnd = 62;
oTimer ptRadialFireTimer;
const unsigned long culRadialTimerEnd = 360;

//Other constants
const int ciNOne = -1;

//////////////////////////////////////////////////////////////////////////
//		Initializing all the objects and their settings, and game global variables
//////////////////////////////////////////////////////////////////////////
char * rcPlayerShip = "./images/Ship.png";
char * rcEnemyShips = "./images/EnemyShip.png";
char * rcStar = "./images/Star.png";
char * rcBacground = "./images/Background.png";
char * rcMenu = "./images/Menu.png";
char * rcLevelOne = "./images/LevelOne.png";

//player ship (contains an oObjects, oVectors, and oTimers)
oShips psPlayerOne;

//star array objects
oObjects poSmallStar[ciStarArraySize];
oObjects poMediumStar[ciStarArraySize];
oObjects poLargeStar[ciStarArraySize];

//bullet array objects
oObjects poEnemyBullets[ciArraySize];
oObjects poPlayerBullets[ciArraySize/5];

//enemy array ships (contains an oObjects, oVectors, and oTimers)
oShips psSmallEnemies[ciEnemyNumbers];
oShips psMediumEnemies[ciEnemyNumbers];
oShips psLargeEnemies[ciEnemyNumbers];

//The games state switch
void (*a_GameState)();


//////////////////////////////////////////////////////////////////////////
//		Sets up the main variables
//////////////////////////////////////////////////////////////////////////
void a_Initializer(){

	a_GameState = &a_Menu;

	//player stuff
	// is dead is true when it is dead
	psPlayerOne.a_Inisialize(CreateSprite(rcPlayerShip, ciPlayerWidth, ciPlayerHeight), ciPlayerWidth, ciPlayerHeight, , false);
	ciSCREEN_X>>1, ciPlayerStartY, rcPlayerShip, ciPlayerWidth, ciPlayerHeight
	psPlayerOne.poData.pPosition.a_SetVector(ciSCREEN_X>>1, ciPlayerStartY);
	psPlayerOne.poData.pSpeed.a_SetVector(0,0);
	psPlayerOne.pvFirePositionOne.a_SetVector(ciPlayerFirePositions[0], ciPlayerFirePositions[1]);
	psPlayerOne.pvFirePositionTwo.a_SetVector(ciPlayerFirePositions[2], ciPlayerFirePositions[3]);
	psPlayerOne.pvFirePositionThree.a_SetVector(ciPlayerFirePositions[4], ciPlayerFirePositions[5]);
	psPlayerOne.pvFirePositionFour.a_SetVector(ciPlayerFirePositions[6], ciPlayerFirePositions[7]);
	psPlayerOne.bCenterFire = false;
	psPlayerOne.ptFireRateCenter.a_Start(ulPlayerFireRate[0]); 
	psPlayerOne.ptFireRateOne.a_Start(ulPlayerFireRate[1]); 
	psPlayerOne.ptFireRateTwo.a_Start(ulPlayerFireRate[2]);
	psPlayerOne.ptFireRateThree.a_Start(ulPlayerFireRate[3]);
	psPlayerOne.ptFireRateFour.a_Start(ulPlayerFireRate[4]); 
	psPlayerOne.poData.iSprite = CreateSprite( "./images/Ship.png", psPlayerOne.poData.iWidth, psPlayerOne.poData.iHeight, true);
	
	//EnemySetUp
	for(int i = 0; i < ciEnemyNumbers; i++){

		//Small Enemies (Fodder enemies)
		psSmallEnemies[i].poData.bIsDead = 1;
		psSmallEnemies[i].poData.iHeight = ciSmallEnemyDimensions;
		psSmallEnemies[i].poData.iWidth = ciSmallEnemyDimensions;
		psSmallEnemies[i].poData.iSprite = CreateSprite( "./images/EnemyShip.png", psSmallEnemies[i].poData.iWidth, psSmallEnemies[i].poData.iHeight);
		psSmallEnemies[i].poData.pPosition.a_SetVector(ciEnemySartPosition,ciEnemySartPosition);
		psSmallEnemies[i].poData.pSpeed.a_SetVector(0,0);
		psSmallEnemies[i].pvStartPosition.a_SetVector(0,0);
		psSmallEnemies[i].bCenterFire = 0;

		//Medium Enemies (Attack Enemies)
		psMediumEnemies[i].poData.bIsDead = 1;
		psMediumEnemies[i].poData.iHeight = ciMediumEnemyDimensions;
		psMediumEnemies[i].poData.iWidth = ciMediumEnemyDimensions;
		psMediumEnemies[i].poData.iSprite = CreateSprite( "./images/EnemyShip.png", psMediumEnemies[i].poData.iWidth, psMediumEnemies[i].poData.iHeight);
		psMediumEnemies[i].poData.pPosition.a_SetVector(ciEnemySartPosition,ciEnemySartPosition);
		psMediumEnemies[i].poData.pSpeed.a_SetVector(0,0);
		psMediumEnemies[i].pvStartPosition.a_SetVector(0,0);
		psMediumEnemies[i].bCenterFire = 0;

		//Large Enemies (Destroyer enemies)
		psLargeEnemies[i].poData.bIsDead = 1;
		psLargeEnemies[i].poData.iHeight = ciLargeEnemyDimensions;
		psLargeEnemies[i].poData.iWidth = ciLargeEnemyDimensions;
		psLargeEnemies[i].poData.iSprite = CreateSprite( "./images/EnemyShip.png", psLargeEnemies[i].poData.iWidth, psLargeEnemies[i].poData.iHeight);
		psLargeEnemies[i].poData.pPosition.a_SetVector(ciEnemySartPosition,ciEnemySartPosition);
		psLargeEnemies[i].poData.pSpeed.a_SetVector(0,0);
		psLargeEnemies[i].pvStartPosition.a_SetVector(0,0);
		psLargeEnemies[i].bCenterFire = 0;

	}

	//bullet initialising
	for(int i = 0; i < ciArraySize; i++){

		uiBulletSpriteOne = CreateSprite("./images/Star.png", ciBulletDimensions, ciBulletDimensions, true);
		poEnemyBullets[i].bIsDead = 1;
		poEnemyBullets[i].iHeight = ciBulletDimensions;
		poEnemyBullets[i].iWidth = ciBulletDimensions;
		poEnemyBullets[i].iSprite = uiBulletSpriteOne;
		poEnemyBullets[i].pSpeed.a_SetVector(0,0);

		uiBulletSpriteOne = CreateSprite("./images/Star.png", ciBulletDimensions, ciBulletDimensions, true);
		poPlayerBullets[i/5].bIsDead = 1;
		poPlayerBullets[i/5].iHeight = ciBulletDimensions;
		poPlayerBullets[i/5].iWidth = ciBulletDimensions;
		poPlayerBullets[i/5].iSprite = uiBulletSpriteOne;
		poPlayerBullets[i/5].pSpeed.a_SetVector(0,0);
	}

	//setting up the stars
	for(int i = 0; i < ciStarArraySize; i++){

		poSmallStar[i].iHeight = ciSmallStarDimensions;
		poSmallStar[i].iWidth = ciSmallStarDimensions;
		poSmallStar[i].pSpeed.a_SetVector(0,0);
		poSmallStar[i].pPosition.a_SetVector(ciStarStart, ciStarStart);
		poSmallStar[i].iSprite = CreateSprite( "./images/Star.png", poSmallStar[i].iWidth, poSmallStar[i].iHeight, true);

		poMediumStar[i].iHeight = ciMediumStarDimensions;
		poMediumStar[i].iWidth = ciMediumStarDimensions;
		poMediumStar[i].pSpeed.a_SetVector(0,0);
		poMediumStar[i].pPosition.a_SetVector(ciStarStart, ciStarStart);
		poMediumStar[i].iSprite = CreateSprite( "./images/Star.png", poMediumStar[i].iWidth, poMediumStar[i].iHeight, true);

		poLargeStar[i].iHeight = ciLargeStarDimensions;
		poLargeStar[i].iWidth = ciLargeStarDimensions;
		poLargeStar[i].pSpeed.a_SetVector(0,0);
		poLargeStar[i].pPosition.a_SetVector(ciStarStart, ciStarStart);
		poLargeStar[i].iSprite = CreateSprite( "./images/Star.png", poLargeStar[i].iWidth, poLargeStar[i].iHeight, true);


	}
	
	ptSineTimer.a_Start(culSineTimerEnd);

	//creating the rest of the sprites
	MoveSprite(uiBackgroundImage, ciSCREEN_X>>1, ciSCREEN_Y>>1);
	MoveSprite(uiMenuImage, ciSCREEN_X>>1, ciSCREEN_Y>>1);
	MoveSprite(uiLevelBackground, ciSCREEN_X>>1, ciSCREEN_Y>>1);
	DrawSprite(uiBackgroundImage);
}

//////////////////////////////////////////////////////////////////////////
//		The Menu
//////////////////////////////////////////////////////////////////////////
void a_Menu(){

	a_DrawGame();

	//DrawSprite(uiBackgroundImage);
	DrawSprite(uiMenuImage);

	if(IsKeyDown(KEY_ENTER))
		a_GameState = &a_UpDateGame;

	if(IsKeyDown(KEY_BACKSPACE))
		a_GameState = &a_UpDateGame;

	if(IsKeyDown(KEY_ESC)){
		Shutdown();
		exit(1);
	}



}

//////////////////////////////////////////////////////////////////////////
//		Runs the a_GameState which controls the games state
//////////////////////////////////////////////////////////////////////////
void a_GameRunner(){

	a_GameState();

}

//////////////////////////////////////////////////////////////////////////
//		Moves the player
//////////////////////////////////////////////////////////////////////////
void a_MovePlayer(){

	if(IsKeyDown(KEY_RSHIFT))
		a_GameState = &a_Menu;

	else{

		if(IsKeyDown(KEY_LEFT) && a_iTestScreenCollision(psPlayerOne.poData) != ciLeftCollision && !IsKeyDown(KEY_RIGHT)){

			psPlayerOne.poData.pSpeed.a_SetVector(cfPlayerSpeed *  ciNOne, psPlayerOne.poData.pSpeed.a_fGetVectorY());

		}

		else if(IsKeyDown(KEY_RIGHT) && a_iTestScreenCollision(psPlayerOne.poData) != ciRightCollision && !IsKeyDown(KEY_LEFT)){

			psPlayerOne.poData.pSpeed.a_SetVector(cfPlayerSpeed, psPlayerOne.poData.pSpeed.a_fGetVectorY());
		}
		else
			psPlayerOne.poData.pSpeed.a_SetVector(0, psPlayerOne.poData.pSpeed.a_fGetVectorY());


		if(IsKeyDown(KEY_UP) && a_iTestScreenCollision(psPlayerOne.poData) != ciTopCollision && !((psPlayerOne.poData.pPosition.a_fGetVectorY() - psPlayerOne.poData.iHeight / 2) < 0) && !IsKeyDown(KEY_DOWN)){

			psPlayerOne.poData.pSpeed.a_SetVector(psPlayerOne.poData.pSpeed.a_fGetVectorX(), cfPlayerSpeed * ciNOne);
		}

		else if(IsKeyDown(KEY_DOWN) && a_iTestScreenCollision(psPlayerOne.poData) != ciBottomCollision && !((psPlayerOne.poData.pPosition.a_fGetVectorY() + psPlayerOne.poData.iHeight / 2) > ciSCREEN_Y) && !IsKeyDown(KEY_UP)){

			psPlayerOne.poData.pSpeed.a_SetVector(psPlayerOne.poData.pSpeed.a_fGetVectorX(), cfPlayerSpeed);
		}

		else
			psPlayerOne.poData.pSpeed.a_SetVector(psPlayerOne.poData.pSpeed.a_fGetVectorX(), 0);

		if(IsKeyDown(KEY_SPACE) && (psPlayerOne.ptFireRateCenter.a_bStop() || psPlayerOne.ptFireRateOne.a_bStop() || 
			psPlayerOne.ptFireRateTwo.a_bStop() || psPlayerOne.ptFireRateThree.a_bStop() || psPlayerOne.ptFireRateFour.a_bStop())){
			a_FireBullet(psPlayerOne, psPlayerOne.pvFirePositionOne, psPlayerOne.pvFirePositionTwo, psPlayerOne.pvFirePositionThree, psPlayerOne.pvFirePositionFour, true);
		}

	}

}

//////////////////////////////////////////////////////////////////////////
//		Moves the Stars
//////////////////////////////////////////////////////////////////////////
void a_StarMover(){

	for(int i = 0; i < ciStarArraySize; i++){

		if(poSmallStar[i].pSpeed.a_fGetVectorY() == 0){

			poSmallStar[i].pPosition.a_SetVector(rand()% ciSCREEN_X , ciStarStart - rand() % ciStarYSpread);
			poSmallStar[i].pSpeed.a_SetVector(0, cfStarSpeed);

		}
		
		if(a_iTestScreenCollision(poSmallStar[i]) == ciBottomCollision){

			poSmallStar[i].pPosition.a_SetVector(poSmallStar[i].pPosition.a_fGetVectorX(), ciStarStart);
			poSmallStar[i].pSpeed.a_SetVector(0,0);

		}
		
		if(poMediumStar[i].pSpeed.a_fGetVectorY() == 0){

			poMediumStar[i].pPosition.a_SetVector(rand()% ciSCREEN_X , ciStarStart - rand() % ciStarYSpread);
			poMediumStar[i].pSpeed.a_SetVector(0, cfStarSpeed * 2);

		}
		
		if(a_iTestScreenCollision(poMediumStar[i]) == ciBottomCollision){

			poMediumStar[i].pPosition.a_SetVector(poMediumStar[i].pPosition.a_fGetVectorX(), ciStarStart);
			poMediumStar[i].pSpeed.a_SetVector(0,0);

		}

		if(poLargeStar[i].pSpeed.a_fGetVectorY() == 0){

			poLargeStar[i].pPosition.a_SetVector(rand()% ciSCREEN_X , ciStarStart - rand() % ciStarYSpread);
			poLargeStar[i].pSpeed.a_SetVector(0, cfStarSpeed * 4);

		}
		
		if(a_iTestScreenCollision(poLargeStar[i]) == ciBottomCollision){

			poLargeStar[i].pPosition.a_SetVector(poLargeStar[i].pPosition.a_fGetVectorX(), ciStarStart);
			poLargeStar[i].pSpeed.a_SetVector(0,0);

		}


		a_UpdateObject(poSmallStar[i]);
		MoveSprite(poSmallStar[i].iSprite, poSmallStar[i].pPosition.a_fGetVectorX(), poSmallStar[i].pPosition.a_fGetVectorY());

		a_UpdateObject(poMediumStar[i]);
		MoveSprite(poMediumStar[i].iSprite, poMediumStar[i].pPosition.a_fGetVectorX(), poMediumStar[i].pPosition.a_fGetVectorY());

		a_UpdateObject(poLargeStar[i]);
		MoveSprite(poLargeStar[i].iSprite, poLargeStar[i].pPosition.a_fGetVectorX(), poLargeStar[i].pPosition.a_fGetVectorY());

	}

}

//////////////////////////////////////////////////////////////////////////
//		Tests to see if an object is colliding with screen, 1 is left, 2 is right, 3 is up, 4 bottom
//////////////////////////////////////////////////////////////////////////
int a_iTestScreenCollision(oObjects & rpObj){

	// 1 is left, 2 is right, 3 is up, 4 bottom
	if((rpObj.pPosition.a_fGetVectorX() - (rpObj.iWidth / 2) ) < 0)
		return ciLeftCollision;
	if((rpObj.pPosition.a_fGetVectorX() + (rpObj.iWidth / 2)) > ciSCREEN_X)
		return ciRightCollision;
	if((rpObj.pPosition.a_fGetVectorY() - (rpObj.iHeight / 2)) < 0)
		return ciTopCollision;
	if((rpObj.pPosition.a_fGetVectorY() + (rpObj.iHeight / 2)) > (ciSCREEN_Y - rpObj.pSpeed.a_fGetVectorY()))
		return ciBottomCollision;
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//		Where the game happens
//////////////////////////////////////////////////////////////////////////
void a_UpDateGame(){

	a_MovePlayer();

	a_StarMover();
	
	ptSineTimer.a_Running();

	if(ptSineTimer.a_bStop())
		ptSineTimer.a_Reset();

	a_MoveBullets();

	a_UpdateObject(psPlayerOne.poData);
	MoveSprite(psPlayerOne.poData.iSprite, psPlayerOne.poData.pPosition.a_fGetVectorX(), psPlayerOne.poData.pPosition.a_fGetVectorY());

	psPlayerOne.ptFireRateCenter.a_Running();
	psPlayerOne.ptFireRateCenter.a_bStop();

	psPlayerOne.ptFireRateOne.a_Running();
	psPlayerOne.ptFireRateOne.a_bStop();

	psPlayerOne.ptFireRateTwo.a_Running();
	psPlayerOne.ptFireRateTwo.a_bStop();

	psPlayerOne.ptFireRateThree.a_Running();
	psPlayerOne.ptFireRateThree.a_bStop();

	psPlayerOne.ptFireRateFour.a_Running();
	psPlayerOne.ptFireRateFour.a_bStop();

	a_DrawGame();

}

//////////////////////////////////////////////////////////////////////////
//		Draws the game sprites  
//////////////////////////////////////////////////////////////////////////
void a_DrawGame(){

	DrawSprite(uiBackgroundImage);
	DrawSprite(uiLevelBackground);

	for(int i = 0; i < ciStarArraySize; i++){

		DrawSprite(poSmallStar[i].iSprite);
		DrawSprite(poMediumStar[i].iSprite);
		DrawSprite(poLargeStar[i].iSprite);

	}

	for(int i = 0; i < 100; i++){

		if(!poPlayerBullets[i].bIsDead){
			DrawSprite(poPlayerBullets[i].iSprite);
		}

	}

	DrawSprite(psPlayerOne.poData.iSprite);
}

//////////////////////////////////////////////////////////////////////////
//		fires a bullet
//////////////////////////////////////////////////////////////////////////
void a_FireBullet(oShips & rpObj, oVector & rpPositionOne, oVector & rpPositionTwo, oVector & rpPositionThree, oVector & rpPositionFour, bool bIsPlayer){

	int iArrayCounter = 0;

	//first we check to see if the fire positions are valid and make sure eah spot fires once(0,0 is not valid
	//as the center is already a fire spot)
	bool bFireOne = !(rpPositionOne.a_fGetVectorX() == 0 && rpPositionOne.a_fGetVectorY() == 0);
	bool bFireTwo = !(rpPositionTwo.a_fGetVectorX() == 0 && rpPositionTwo.a_fGetVectorY() == 0);
	bool bFireThree = !(rpPositionThree.a_fGetVectorX() == 0 && rpPositionThree.a_fGetVectorY() == 0);
	bool bFireFour = !(rpPositionFour.a_fGetVectorX() == 0 && rpPositionFour.a_fGetVectorY() == 0);
	bool bCenterFire = rpObj.bCenterFire;

	// for firing more then one bullet
	int iFireCounter = 0;

	for(int i = 0; i < ciArraySize; i++){
		
		if(!bIsPlayer){

			if(poEnemyBullets[i].bIsDead){

				poEnemyBullets[i].bIsDead = 0;
				poEnemyBullets[i].pPosition.a_SetVector(rpObj.poData.pPosition.a_fGetVectorX(), rpObj.poData.pPosition.a_fGetVectorY());
				poEnemyBullets[i].pSpeed.a_SetVector(0, cfBulletSpeed * -1);

			}

		}

		else{

			if(poPlayerBullets[i/5].bIsDead && bCenterFire && rpObj.ptFireRateCenter.a_bStop()){

				rpObj.ptFireRateCenter.a_Reset();
				poPlayerBullets[i/5].bIsDead = 0;
				bCenterFire = false;
				poPlayerBullets[i/5].pPosition.a_SetVector(rpObj.poData.pPosition.a_fGetVectorX(), rpObj.poData.pPosition.a_fGetVectorY());
				poPlayerBullets[i/5].pSpeed.a_SetVector(0, cfBulletSpeed * -1);

			}

			if(poPlayerBullets[i/5].bIsDead && bFireOne && rpObj.ptFireRateOne.a_bStop()){

				rpObj.ptFireRateOne.a_Reset();
				poPlayerBullets[i/5].bIsDead = 0;
				bFireOne = false;
				poPlayerBullets[i/5].empMove = CircleSparse;
				
				poPlayerBullets[i/5].pPosition.a_SetVector(rpObj.poData.pPosition.a_fGetVectorX() + rpObj.pvFirePositionOne.a_fGetVectorX(),
					rpObj.poData.pPosition.a_fGetVectorY() + rpObj.pvFirePositionOne.a_fGetVectorY());
				poPlayerBullets[i/5].pSpeed.a_SetVector(0, cfBulletSpeed * -1);

			}

			if(poPlayerBullets[i/5].bIsDead && bFireTwo && rpObj.ptFireRateTwo.a_bStop()){
					
				rpObj.ptFireRateTwo.a_Reset();
				poPlayerBullets[i/5].bIsDead = 0;
				bFireTwo = false;
				poPlayerBullets[i/5].empMove = SineShotMid;
				poPlayerBullets[i/5].pPosition.a_SetVector(rpObj.poData.pPosition.a_fGetVectorX() + rpObj.pvFirePositionTwo.a_fGetVectorX(),
					rpObj.poData.pPosition.a_fGetVectorY() + rpObj.pvFirePositionTwo.a_fGetVectorY());
				poPlayerBullets[i/5].pSpeed.a_SetVector(0, cfBulletSpeed * -1);

			}

			if(poPlayerBullets[i/5].bIsDead && bFireThree && rpObj.ptFireRateThree.a_bStop()){

				rpObj.ptFireRateThree.a_Reset();
				poPlayerBullets[i/5].bIsDead = 0;
				bFireThree = false;
				poPlayerBullets[i/5].pPosition.a_SetVector(rpObj.poData.pPosition.a_fGetVectorX() + rpObj.pvFirePositionThree.a_fGetVectorX(), 
					rpObj.poData.pPosition.a_fGetVectorY() + rpObj.pvFirePositionThree.a_fGetVectorY());
				poPlayerBullets[i/5].pSpeed.a_SetVector(0, cfBulletSpeed * -1);

			}

			if(poPlayerBullets[i/5].bIsDead && bFireFour && rpObj.ptFireRateFour.a_bStop()){

				rpObj.ptFireRateFour.a_Reset();
				poPlayerBullets[i/5].bIsDead = 0;
				bFireFour = false;
				poPlayerBullets[i/5].pPosition.a_SetVector(rpObj.poData.pPosition.a_fGetVectorX() + rpObj.pvFirePositionFour.a_fGetVectorX(), 
					rpObj.poData.pPosition.a_fGetVectorY() + rpObj.pvFirePositionFour.a_fGetVectorY());
				poPlayerBullets[i/5].pSpeed.a_SetVector(0, cfBulletSpeed * -1);

			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//		moves the bullets, and destroys them  
//////////////////////////////////////////////////////////////////////////
void a_MoveBullets(){

	long double ldSineWave = ptSineTimer.a_ulGetTime() / 10;

	for(int i = 0; i < ciArraySize; i++){

		if(!poPlayerBullets[i/5].bIsDead){
			if(poPlayerBullets[i/5].empMove == SineShotMid){
				poPlayerBullets[i/5].pPosition.a_SetVector(poPlayerBullets[i/5].pPosition.a_fGetVectorX() + sin(ldSineWave), poPlayerBullets[i/5].pPosition.a_fGetVectorY());
			}
			a_UpdateObject(poPlayerBullets[i/5]);
			MoveSprite(poPlayerBullets[i/5].iSprite, poPlayerBullets[i/5].pPosition.a_fGetVectorX(), poPlayerBullets[i/5].pPosition.a_fGetVectorY());
		}

		if(a_iTestScreenCollision(poPlayerBullets[i/5]) != 0 && !poPlayerBullets[i].bIsDead){

			poPlayerBullets[i/5].bIsDead = 1;
			poPlayerBullets[i/5].pSpeed.a_SetVector(0,0);
		}
	}


}

//////////////////////////////////////////////////////////////////////////
//		moves the enemies according to their movement type, and destroys them  
//////////////////////////////////////////////////////////////////////////
void a_MoveEnemy(){


}

//////////////////////////////////////////////////////////////////////////
//		spawns enemies in various ways, gives them their type, and thier sprite  
//////////////////////////////////////////////////////////////////////////
void a_SpawnEnemy(){



}
