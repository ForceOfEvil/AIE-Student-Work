//////////////////////////////////////////////////////////////////////////
//		@file				PongInvaders
//		@details			A pong game with space invaders
//		@author				Derek Potter
//		@version			1.0
//		@date last edited	9/23/2013
//////////////////////////////////////////////////////////////////////////

#include "AIE.h"
#include "Functions.h"
#include <string>
#include <iostream>
const int ciSCREEN_X = 1280;
const int ciSCREEN_Y = 780;

//////////////////////////////////////////////////////////////////////////
//		@breif			Used to keep track of positions and speed
//		@class			oVector
//////////////////////////////////////////////////////////////////////////
struct oVector{
	float fX;
	float fY;
};

//////////////////////////////////////////////////////////////////////////
//		@breif			Used to keep track of a bullets position, speed, and sprite
//		@class			oBullet
//////////////////////////////////////////////////////////////////////////
struct oBullet{

	oVector pPosition;
	oVector pSpeed;
	unsigned int uiSprite;
};

//////////////////////////////////////////////////////////////////////////
//		@breif			Used to keep track of an objects position, speed, size, sprite, and score
//		@class			oObjects
//////////////////////////////////////////////////////////////////////////
struct oObjects{
	oVector pPosition;
	oVector pSpeed;
	int iSprite;
	int iWidth;
	int iHeight;
	int iScore;
	bool bHasFired;
	oBullet pBullet;
};

//////////////////////////////////////////////////////////////////////////
//		@breif			Used to keep track of an invaders position, speed, sprite, and bullets
//		@class			oInvader
//////////////////////////////////////////////////////////////////////////
struct oInvader{
	
	oVector pPosition;
	oVector pSpeed;
	bool bIsDestroyed;
	bool bHasFired;
	oBullet pBullet;
	unsigned int uiSprite;

};

//////////////////////////////////////////////////////////////////////////
//		@breif			Just an easy way to change player speed, and the win score
//		@class			oOptions
//////////////////////////////////////////////////////////////////////////
struct oOptions{

	oVector pSpeed;
	int iWinScore;
};

//////////////////////////////////////////////////////////////////////////
//		Adds two vectors together
//////////////////////////////////////////////////////////////////////////
oVector a_VectorAdd(oVector & rfv, oVector & rfv2){
	oVector result = {rfv.fX + rfv2.fX, rfv.fY + rfv2.fY};
	return result;
}

//////////////////////////////////////////////////////////////////////////
//		Initializing all the objects and their settings, and game global variables
//////////////////////////////////////////////////////////////////////////
unsigned int uiBackgroundImage = -1;
unsigned int uiMenueSprite = -1;
unsigned int uiMenuControlsSprite = -1;

int iInvaderDeadCount = 0;

//		{pPosition.fX, pPosition.fY, pSpeed.fX, pSpeed.fY, iSprite, iWidth, iHeight, iScore, bHasFired, pBullet}
oObjects pPlayerOne = {1180, 350, 0, 0, -1, 25, 100, 0, 0, 0};
oObjects pPlayerTwo = {100, 350, 0, 0, -1, 25, 100, 0, 0, 0};
oObjects pBall = {550, 50, 1.23, 1.23, -1, 50, 50, 0, 0, 0};
//		{pSpeed.fX, pSpeed.fY, iWinScore}
oOptions pOptions = {1, 1, 53};

// The invaders
oInvader pInvader[5][10];

//////////////////////////////////////////////////////////////////////////
//		Sets up the main variables
//////////////////////////////////////////////////////////////////////////
void a_Initializer(){
	pPlayerOne.pBullet.pPosition.fX = 649;
	pPlayerOne.pBullet.pPosition.fY = -25;
	pPlayerOne.pBullet.pSpeed.fX = 0;
	pPlayerOne.pBullet.pSpeed.fY = 0;
	//Load Sprites
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 10; j++){
			pInvader[i][j].uiSprite = CreateSprite("./images/Ship.png", 25, 25, true);
			pInvader[i][j].pBullet.uiSprite = CreateSprite("./images/Bullet.png", 8, 8, true);
		}
	}

	uiMenueSprite = CreateSprite( "./images/Menu.png", 800, 600, true);
	uiMenuControlsSprite = CreateSprite( "./images/MenuControls.png", 800, 600, true);
	uiBackgroundImage = CreateSprite( "./images/Background.png", ciSCREEN_X, ciSCREEN_Y, true);
	pPlayerOne.iSprite = CreateSprite( "./images/PlayerOnePaddle.png", pPlayerOne.iWidth, pPlayerOne.iHeight, true);
	pPlayerOne.pBullet.uiSprite = CreateSprite("./images/Bullet.png", 8, 8, true);
	pPlayerTwo.iSprite = CreateSprite( "./images/PlayerTwoPaddle.png", pPlayerTwo.iWidth, pPlayerTwo.iHeight, true);
	pBall.iSprite = CreateSprite( "./images/Ball.png", pBall.iWidth, pBall.iHeight, true);
	MoveSprite(uiBackgroundImage, ciSCREEN_X>>1, ciSCREEN_Y>>1);
	DrawSprite(uiBackgroundImage);
}

//////////////////////////////////////////////////////////////////////////
//		Updates an objects position
//////////////////////////////////////////////////////////////////////////
void a_UpdateObject(oObjects & rpObj) {
	rpObj.pPosition = a_VectorAdd(rpObj.pPosition, rpObj.pSpeed);
}

//////////////////////////////////////////////////////////////////////////
//		Does all the collision checking between tha ball and paddles
//////////////////////////////////////////////////////////////////////////
void a_PaddleCollision(oObjects & rpPaddleOne, oObjects & rpBall, oObjects & rpPaddleTwo){

	//causes the balls y vector to change with its x to prevent a case were the player could stay in one spot
	int iChangeUp = rand()%10;

	//do the change up  20% of the time
	if(iChangeUp > 8)
		iChangeUp = 2;
	else
		iChangeUp = 0;

	// Player one's collision
	if((rpBall.pPosition.fY + rpBall.iHeight / 2 > rpPaddleOne.pPosition.fY - rpPaddleOne.iHeight / 2) && 
		(rpBall.pPosition.fY - rpBall.iHeight / 2 < rpPaddleOne.pPosition.fY + rpPaddleOne.iHeight / 2) &&
		(rpBall.pPosition.fX + rpBall.iWidth / 2 > rpPaddleOne.pPosition.fX - rpPaddleOne.iWidth / 2) && 
		(rpBall.pPosition.fX - rpBall.iWidth / 2 < rpPaddleOne.pPosition.fX + rpPaddleOne.iWidth / 2) && 
		(rpBall.pSpeed.fX > 0)){
				rpBall.pSpeed.fX *= -1;
				rpBall.pSpeed.fY *= 1 - iChangeUp;
	}

	// Player two's collision
	if((rpBall.pPosition.fY + rpBall.iHeight / 2 > rpPaddleTwo.pPosition.fY - rpPaddleTwo.iHeight / 2) && 
		(rpBall.pPosition.fY - rpBall.iHeight / 2 < rpPaddleTwo.pPosition.fY + rpPaddleTwo.iHeight / 2) &&
		(rpBall.pPosition.fX + rpBall.iWidth / 2 > rpPaddleTwo.pPosition.fX - rpPaddleTwo.iWidth / 2) && 
		(rpBall.pPosition.fX - rpBall.iWidth / 2 < rpPaddleTwo.pPosition.fX + rpPaddleTwo.iWidth / 2) && 
		(rpBall.pSpeed.fX < 0)){
				rpBall.pSpeed.fX *= -1;
				rpBall.pSpeed.fY *= 1 - iChangeUp;
	}
}

//////////////////////////////////////////////////////////////////////////
//		Tests to see if an object is colliding with screen, 1 is left, 2 is right, 3 is up, 4 bottom
//////////////////////////////////////////////////////////////////////////
int a_iTestScreenCollision(oObjects & rpObj){

	// 1 is left, 2 is right, 3 is up, 4 bottom
	if((rpObj.pPosition.fX - (rpObj.iWidth / 2) ) < 0)
		return 1;
	if((rpObj.pPosition.fX + (rpObj.iWidth / 2)) > ciSCREEN_X)
		return 2;
	if((rpObj.pPosition.fY - (rpObj.iHeight / 2)) < 0)
		return 3;
	if((rpObj.pPosition.fY + (rpObj.iHeight / 2)) > (ciSCREEN_Y - rpObj.pSpeed.fY))
		return 4;
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//		The AI
//////////////////////////////////////////////////////////////////////////
void a_AI(oObjects & rpAI, oObjects & rpBall){
	//randomizing the ai sped
	float fAIRandom = (rand()%40)/100;

	//stop the ai from continually moving
		rpAI.pSpeed.fY = 0;

		// if the ball is on the right
	 if(rpBall.pPosition.fX > 720){
		 //and the ball is at the bottom half of the screen, move to bottom third
		if(rpBall.pPosition.fY < 360 && rpAI.pPosition.fY < 510 && a_iTestScreenCollision(rpAI) != 4){

			rpAI.pSpeed.fY = pOptions.pSpeed.fY + fAIRandom;

		}
		// or the upper third if above
		if(rpBall.pPosition.fY >= 360 && rpAI.pPosition.fY > 180 && a_iTestScreenCollision(rpAI) != 3){

			rpAI.pSpeed.fY = (pOptions.pSpeed.fY  + fAIRandom)* -1;

		}

	}
	 //otherwise move up if the balls above, and down if its below
	else if(rpBall.pPosition.fX <= 720 && rpBall.pSpeed.fX < 0){

		// move down
		if(rpBall.pPosition.fY > rpAI.pPosition.fY)
			rpAI.pSpeed.fY = pOptions.pSpeed.fY + fAIRandom;

		// move up
		if(rpBall.pPosition.fY < rpAI.pPosition.fY)
			rpAI.pSpeed.fY = (pOptions.pSpeed.fY + fAIRandom) * -1;
	}


}

//////////////////////////////////////////////////////////////////////////
//		Updates the score, 1 for player one, 2 for player two
//////////////////////////////////////////////////////////////////////////
int a_iScore(oObjects & rpBall){
	if(a_iTestScreenCollision(rpBall) == 2)
		return 1;
	if(a_iTestScreenCollision(rpBall) == 1)
		return 2;
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//		Updates and runs the game
//////////////////////////////////////////////////////////////////////////
void a_UpDateGame(){

	//see if someone has wo/lost
	a_WinLose();

	//test if ball hit screen
	switch(a_iTestScreenCollision(pBall)){
	case 1:
	case 2:
		pBall.pSpeed.fX *= -1;
		break;
	case 3:
	case 4:
		pBall.pSpeed.fY *= -1;
	}

	//collision test
	a_PaddleCollision(pPlayerOne, pBall, pPlayerTwo);

	//update the balls position
	a_UpdateObject(pBall);

	//call the Ai so they move
	a_AI(pPlayerTwo, pBall);

	//now update the ai
	a_UpdateObject(pPlayerTwo);

	a_MoveInvader();
	a_MoveBullet();
	// Allows the player to move up
	if (IsKeyDown(KEY_UP) && a_iTestScreenCollision(pPlayerOne) != 3){

		pPlayerOne.pSpeed.fY = pOptions.pSpeed.fY * -1;

	}
	//and down
	else if (IsKeyDown(KEY_DOWN)&& a_iTestScreenCollision(pPlayerOne) != 4){

		pPlayerOne.pSpeed.fY = pOptions.pSpeed.fY;
	}
	// stops the players paddle if neither key is pressed
	else
		pPlayerOne.pSpeed.fY = 0;

	a_UpdateObject(pPlayerOne);
	a_MovePlayerBullet();
	//Score checking
	switch(a_iScore(pBall)){
	case 1:
		pPlayerTwo.iScore++;
		break;
	case 2:
		pPlayerOne.iScore++;
		break;
	}

	//Move all the sprites
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 10; j++){
			//Update and move the invader and bullet sprites
			a_UpdateInvader(pInvader[i][j]);
			a_UpdateBullet(pInvader[i][j].pBullet);
			MoveSprite(pInvader[i][j].uiSprite, pInvader[i][j].pPosition.fX, pInvader[i][j].pPosition.fY);
			MoveSprite(pInvader[i][j].pBullet.uiSprite, pInvader[i][j].pBullet.pPosition.fX, pInvader[i][j].pBullet.pPosition.fY);
		}
	}
	a_UpdateBullet(pPlayerOne.pBullet);
	MoveSprite(pPlayerOne.pBullet.uiSprite, pPlayerOne.pBullet.pPosition.fX, pPlayerOne.pBullet.pPosition.fY);
	MoveSprite(pPlayerOne.iSprite, pPlayerOne.pPosition.fX, pPlayerOne.pPosition.fY);
	MoveSprite(pBall.iSprite, pBall.pPosition.fX, pBall.pPosition.fY);
	MoveSprite(pPlayerTwo.iSprite, pPlayerTwo.pPosition.fX, pPlayerTwo.pPosition.fY);
}

//////////////////////////////////////////////////////////////////////////
//		Checks to see if a player has won or lost both individual games, and the overall (best of x)  
//////////////////////////////////////////////////////////////////////////
void a_WinLose(){

	if(pPlayerOne.iScore == pOptions.iWinScore){
		pPlayerOne.iScore = 0;
		pPlayerTwo.iScore = 0;
		Shutdown();
		system("CLS");
		std::cout << "You Win!\n";
		system("PAUSE");
		exit(1);

	}
	if(pPlayerTwo.iScore == pOptions.iWinScore){
		DrawString("You Lose!", 640, 470, (0,0,0,255));
		pPlayerOne.iScore = 0;
		pPlayerTwo.iScore = 0;
		Shutdown();
		system("CLS");
		std::cout << "You Lose!\n\n";
		system("PAUSE");
		exit(1);
	}
}

//////////////////////////////////////////////////////////////////////////
//		Draws the game sprites  
//////////////////////////////////////////////////////////////////////////
void a_DrawGame(){
	//Draw the score
	char cPrintScore[20] = {'\n'};
	sprintf_s(cPrintScore, "Player 1:  %d", pPlayerOne.iScore);
	DrawString(cPrintScore, 1000, 50, SColour(0,0,0,255));
	sprintf_s(cPrintScore, "Player 2:  %d", pPlayerTwo.iScore);
	DrawString(cPrintScore, 200, 50, SColour(0xff,0x00,0x00,0xff));
	//Background ball, and player sprites
	DrawSprite(uiBackgroundImage);
	DrawSprite(pPlayerOne.iSprite);
	DrawSprite(pPlayerTwo.iSprite);
	DrawSprite(pBall.iSprite);
	DrawSprite(pPlayerOne.pBullet.uiSprite);

	//Invader Sprites
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 10; j++){
			DrawSprite(pInvader[i][j].uiSprite);
			DrawSprite(pInvader[i][j].pBullet.uiSprite);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//		Allows the invaders to attack, and makes sure they don't 
//		have their bullet on screen
//////////////////////////////////////////////////////////////////////////
bool a_bInvaderAttack(oInvader & prInv){

	int iAttack = rand()%50000/(iInvaderDeadCount + (iInvaderDeadCount < 1));

	if(prInv.bHasFired == 0 && iAttack == 100){

		prInv.bHasFired = 1;
		return 1;


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//		Puts data into the invaders variables 
//////////////////////////////////////////////////////////////////////////
void a_SetUpInvaders(){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 10; j++){

			//form the ranks
			pInvader[i][j].pPosition.fX = 300 + (i * 60);
			pInvader[i][j].pPosition.fY = 70 + (j * 70);
			//Starting speed
			pInvader[i][j].pSpeed.fX = 0;
			pInvader[i][j].pSpeed.fY = -.05;
			pInvader[i][j].bHasFired = 0;
			pInvader[i][j].bIsDestroyed = 0;
			// a y position above the screen, so they don't show up
			pInvader[i][j].pBullet.pPosition.fX = ciSCREEN_X / 2;
			pInvader[i][j].pBullet.pPosition.fY = - 25;
			pInvader[i][j].pBullet.pSpeed.fX = 0;
			pInvader[i][j].pBullet.pSpeed.fY = 0;
		}
	}

}

//////////////////////////////////////////////////////////////////////////
//		controls the movement of the Invaders 
//////////////////////////////////////////////////////////////////////////
void a_MoveInvader(){

	//Move the invaders down
	bool bMoveDown = 0;

	//move the invaders up
	bool bMoveUp = 0;

	for(int i = 0; i < 5; i++){

		bMoveUp = 0;
		bMoveDown = 0;

		for(int j = 0; j < 10; j++){

			if(a_iInvaderScreenCollision(pInvader[i][j]) == 3 && pInvader[i][j].bIsDestroyed == 0)
				bMoveDown = 1;

			if(a_iInvaderScreenCollision(pInvader[i][j]) == 4 && pInvader[i][j].bIsDestroyed == 0)
				bMoveUp = 1;

		}
		for(int j = 0; j < 10; j++){

			if(bMoveDown == 1)
				pInvader[i][j].pSpeed.fY *= -1;

			if(bMoveUp == 1)
				pInvader[i][j].pSpeed.fY *= -1;
		}
	}

}

//////////////////////////////////////////////////////////////////////////
//		controls the Bullets of the invaders
//////////////////////////////////////////////////////////////////////////
void a_MoveBullet(){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 10; j++){
			if(a_bInvaderAttack(pInvader[i][j])){
				//move bullet and give it speed
				pInvader[i][j].pBullet.pSpeed.fX = 1;
				pInvader[i][j].pBullet.pPosition.fX = pInvader[i][j].pPosition.fX;
				pInvader[i][j].pBullet.pPosition.fY = pInvader[i][j].pPosition.fY;
			}

			if(a_iBulletsScreenCollision(pInvader[i][j].pBullet) == 2){
				pInvader[i][j].pBullet.pSpeed.fX = 0;
				//make sure its off screen
				pInvader[i][j].pBullet.pPosition.fY = ciSCREEN_Y - 25;
				pInvader[i][j].pBullet.pPosition.fX = ciSCREEN_X / 2 + 15;
				pInvader[i][j].bHasFired = 0;
			}

			if(a_bBulletToPaddleCollision(pPlayerOne, pInvader[i][j].pBullet)){
				pInvader[i][j].pBullet.pSpeed.fX = 0;
				//make sure its off screen
				pInvader[i][j].pBullet.pPosition.fY = ciSCREEN_Y - 25;
				pInvader[i][j].pBullet.pPosition.fX = ciSCREEN_X / 2 + 15;
				pPlayerTwo.iScore++;
				pInvader[i][j].bHasFired = 0;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//		Updates the invaders position
//////////////////////////////////////////////////////////////////////////
void a_UpdateInvader(oInvader & rpInv){
	rpInv.pPosition = a_VectorAdd(rpInv.pPosition, rpInv.pSpeed);
}

//////////////////////////////////////////////////////////////////////////
//		Updates the bullets position  
//////////////////////////////////////////////////////////////////////////
void a_UpdateBullet(oBullet & rpBul){
	rpBul.pPosition = a_VectorAdd(rpBul.pPosition, rpBul.pSpeed);
}

//////////////////////////////////////////////////////////////////////////
//		the invaders screen collision 
//////////////////////////////////////////////////////////////////////////
int a_iInvaderScreenCollision(oInvader & rpInv){

		// 1 is left, 2 is right, 3 is up, 4 bottom
	if((rpInv.pPosition.fX - (25 / 2)) < 0)
		return 1;
	if((rpInv.pPosition.fX + (25 / 2)) > ciSCREEN_X)
		return 2;
	if((rpInv.pPosition.fY - (25 / 2)) < 0)
		return 3;
	if((rpInv.pPosition.fY + (25 / 2)) > (ciSCREEN_Y - rpInv.pSpeed.fY))
		return 4;
	
	return 0;

}

//////////////////////////////////////////////////////////////////////////
//		the Bullets screen collision 
//////////////////////////////////////////////////////////////////////////
int a_iBulletsScreenCollision(oBullet & rpBul){

		// 1 is left, 2 is right, 3 is up, 4 bottom
	if((rpBul.pPosition.fX - (25 / 2)) < 0)
		return 1;
	if((rpBul.pPosition.fX + (25 / 2)) > ciSCREEN_X)
		return 2;
	if((rpBul.pPosition.fY - (25 / 2)) < 0)
		return 3;
	if((rpBul.pPosition.fY + (25 / 2)) > (ciSCREEN_Y - rpBul.pSpeed.fY))
		return 4;
	
	return 0;

}

//////////////////////////////////////////////////////////////////////////
//		the Bullet to paddle collision 
//////////////////////////////////////////////////////////////////////////
bool a_bBulletToPaddleCollision(oObjects & rpPaddle, oBullet & rpBul){

	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 10; j++){

	// Player one's collision (4 is the bullets height & width / 2)
			if((rpBul.pPosition.fY +  4 > rpPaddle.pPosition.fY - rpPaddle.iHeight / 2) && 
				(rpBul.pPosition.fY - 4 < rpPaddle.pPosition.fY + rpPaddle.iHeight / 2) &&
				(rpBul.pPosition.fX + 4 > rpPaddle.pPosition.fX - rpPaddle.iWidth / 2) && 
				(rpBul.pPosition.fX - 4 < rpPaddle.pPosition.fX + rpPaddle.iWidth / 2)){
					return 1;
			}
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//		Allows the player to fire and controls the bullet 
//////////////////////////////////////////////////////////////////////////
void a_MovePlayerBullet(){

	if(pPlayerOne.bHasFired == 0 && IsKeyDown(KEY_SPACE)){
				//move bullet and give it speed
				pPlayerOne.pBullet.pSpeed.fX = -1;
				pPlayerOne.pBullet.pPosition.fX = pPlayerOne.pPosition.fX;
				pPlayerOne.pBullet.pPosition.fY = pPlayerOne.pPosition.fY;
				pPlayerOne.bHasFired = 1;

	}
	if(a_iBulletsScreenCollision(pPlayerOne.pBullet) == 1){
		pPlayerOne.pBullet.pSpeed.fX = 0;
		//make sure its off screen
		pPlayerOne.pBullet.pPosition.fY = ciSCREEN_Y - 25;
		pPlayerOne.pBullet.pPosition.fX = ciSCREEN_X / 2 + 15;
		pPlayerOne.bHasFired = 0;
	}
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 10; j++){
			if(a_bBulletToInvaderCollision(pPlayerOne.pBullet, pInvader[i][j])){
				pPlayerOne.pBullet.pSpeed.fX = 0;
				//make sure its off screen
				pPlayerOne.pBullet.pPosition.fY = ciSCREEN_Y - 25;
				pPlayerOne.pBullet.pPosition.fX = ciSCREEN_X / 2 + 15;
				pPlayerOne.iScore++;
				pPlayerOne.bHasFired = 0;
				pInvader[i][j].pPosition.fX = -100;
				pInvader[i][j].pPosition.fY = -100;
				pInvader[i][j].bHasFired = 1;
				pInvader[i][j].pSpeed.fY = 0;
				iInvaderDeadCount++;
			}
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////
//		Players bullet to invaders collision
//////////////////////////////////////////////////////////////////////////
bool a_bBulletToInvaderCollision(oBullet & rpBul, oInvader & rpInv){
	
		for(int i = 0; i < 5; i++){
		for(int j = 0; j < 10; j++){

	// Player one's bullet collision with invader (4 is the bullets height & width / 2 and 25 is the invader height and width)
			if((rpBul.pPosition.fY +  4 > rpInv.pPosition.fY - 25 / 2) && 
				(rpBul.pPosition.fY - 4 < rpInv.pPosition.fY + 25 / 2) &&
				(rpBul.pPosition.fX + 4 > rpInv.pPosition.fX - 25 / 2) && 
				(rpBul.pPosition.fX - 4 < rpInv.pPosition.fX + 25 / 2)){
					return 1;
			}
		}
	}
	return 0;
}