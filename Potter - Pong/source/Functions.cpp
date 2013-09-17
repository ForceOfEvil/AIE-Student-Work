#include "Functions.h"
#include <string>

const int ciSCREEN_X = 1280;
const int ciSCREEN_Y = 780;

struct oVector{
	float fX;
	float fY;
};

//////////////////////////////////////////////////////////////////////////
//		@breif			Used to keep track of a objects position, speed, size, sprite, and score
//		@class			oObjects
//////////////////////////////////////////////////////////////////////////
struct oObjects{
	oVector pPosition;
	oVector pSpeed;
	int iSprite;
	int iWidth;
	int iHeight;
	int iScore;
	int iGamesWon;
	bool bIsGameWinner;
	bool bIsOverAllWinner;
};

//////////////////////////////////////////////////////////////////////////
//		@breif			Keeps track of options the player inputs, such as the number of games
//						to be played (best out of x), and how fast the game moves (based on AILevel)
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


//		{pPosition.fX, pPosition.fY, pSpeed.fX, pSpeed.fY, iSprite, iWidth, iHeight, iScore, iGamesWon, bIsGameWinner, bIsOverAllWinner}
oObjects pPlayerOne = {1180, 350, 0, 0, -1, 25, 100, 0, 0, 0, 0};
oObjects pPlayerTwo = {100, 350, 0, 0, -1, 25, 100, 0, 0, 0, 0};
oObjects pBall = {550 + rand()%250, 50 + rand()%200, 1.23, 1.23, -1, 50, 50, 0, 0, 0, 0};
//		{pSpeed.fX, pSpeed.fY, iWinScore}
oOptions pOptions = {1, 1, 3};


//////////////////////////////////////////////////////////////////////////
//		Sets up the main variables
//////////////////////////////////////////////////////////////////////////
void a_Initialize(){

	//Load Sprites
	uiBackgroundImage = CreateSprite( "./images/Background.png", ciSCREEN_X, ciSCREEN_Y, true);
	pPlayerOne.iSprite = CreateSprite( "./images/PlayerOnePaddle.png", pPlayerOne.iWidth, pPlayerOne.iHeight, true);
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
void a_bPaddleCollision(oObjects & rpPaddleOne, oObjects & rpBall, oObjects & rpPaddleTwo){

	int iChangeUp = rand()%10;

	if(iChangeUp > 5)
		iChangeUp = 2;
	else
		iChangeUp = 0;

	if((rpBall.pPosition.fY + rpBall.iHeight / 2 > rpPaddleOne.pPosition.fY - rpPaddleOne.iHeight / 2) && 
		(rpBall.pPosition.fY - rpBall.iHeight / 2 < rpPaddleOne.pPosition.fY + rpPaddleOne.iHeight / 2) &&
		(rpBall.pPosition.fX + rpBall.iWidth / 2 > rpPaddleOne.pPosition.fX - rpPaddleOne.iWidth / 2) && 
		(rpBall.pPosition.fX - rpBall.iWidth / 2 < rpPaddleOne.pPosition.fX + rpPaddleOne.iWidth / 2) && 
		(rpBall.pSpeed.fX > 0)){
				rpBall.pSpeed.fX *= -1;
				rpBall.pSpeed.fY *= 1 - iChangeUp;
	}
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
	float fAIRandom = rand()%40/100;
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

		if(rpBall.pPosition.fY > rpAI.pPosition.fY)
			rpAI.pSpeed.fY = pOptions.pSpeed.fY + fAIRandom;
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
	a_WinLose();
	switch(a_iTestScreenCollision(pBall)){
	case 1:
	case 2:
		pBall.pSpeed.fX *= -1;
		break;
	case 3:
	case 4:
		pBall.pSpeed.fY *= -1;
	}
	a_bPaddleCollision(pPlayerOne, pBall, pPlayerTwo);

	a_UpdateObject(pBall);
	a_AI(pPlayerTwo, pBall);
	a_UpdateObject(pPlayerTwo);

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

	switch(a_iScore(pBall)){
	case 1:
		pPlayerTwo.iScore++;
		break;
	case 2:
		pPlayerOne.iScore++;
		break;
	}

	MoveSprite(pPlayerOne.iSprite, pPlayerOne.pPosition.fX, pPlayerOne.pPosition.fY);
	MoveSprite(pBall.iSprite, pBall.pPosition.fX, pBall.pPosition.fY);
	MoveSprite(pPlayerTwo.iSprite, pPlayerTwo.pPosition.fX, pPlayerTwo.pPosition.fY);
}

//////////////////////////////////////////////////////////////////////////
//		Checks to see if a player has won or lost both individual games, and the overall (best of x)  
//////////////////////////////////////////////////////////////////////////
void a_WinLose(){

	if(pPlayerOne.iScore == pOptions.iWinScore){
		DrawString("You Win!", 640, 470, (0,0,0,255));
		pPlayerOne.iScore = 0;
		pPlayerTwo.iScore = 0;

	}
	if(pPlayerTwo.iScore == pOptions.iWinScore){
		DrawString("You Lose!", 640, 470, (0,0,0,255));
		pPlayerOne.iScore = 0;
		pPlayerTwo.iScore = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
//		Ends each game and tells the player they won or lost, 
//		and if they want to try again at end of all games
//////////////////////////////////////////////////////////////////////////
void a_End(){


}

//////////////////////////////////////////////////////////////////////////
//		Draws the game sprites  
//////////////////////////////////////////////////////////////////////////
void a_DrawGame(){
	char cPrintScore[20] = {'\n'};
	sprintf_s(cPrintScore, "Player 1:  %d", pPlayerOne.iScore);
	DrawString(cPrintScore, 1000, 50, SColour(0,0,0,255));
	sprintf_s(cPrintScore, "Player 2:  %d", pPlayerTwo.iScore);
	DrawString(cPrintScore, 200, 50, SColour(0xff,0x00,0x00,0xff));
	DrawSprite(uiBackgroundImage);
	DrawSprite(pPlayerOne.iSprite);
	DrawSprite(pPlayerTwo.iSprite);
	DrawSprite(pBall.iSprite);
}