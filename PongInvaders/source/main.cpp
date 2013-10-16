//////////////////////////////////////////////////////////////////////////
//		@file			PongInvaders
//		@details		A pong game with space invaders
//		@author			Derek Potter
//		@version		1.0
//		@date created	9/11/2013
//		@date finished	9/23/2013
//////////////////////////////////////////////////////////////////////////


#include "AIE.h"
#include "Functions.h"
#include <string>
#include <iostream>


const int ciSCREEN_X = 1280;
const int ciSCREEN_Y = 780;

int iFrameCount;

//////////////////////////////////////////////////////////////////////////
//		Sets up the game and variables, then goes to the menu
//////////////////////////////////////////////////////////////////////////
void main(){

	std::cout << "Welcome to Pong Invaders,\nthe game where you play pong and space invaders at the same time.\n\n" <<
		"Up and down move the paddle, while space fires your bullet.\n(you have to wait for the bullet to hit an enemy or the wall to fire again)\n\n" <<
		"Any time a bullet hits your paddle or the ball hits the right side of the screenPlayer2's score increases by one.\n\n" <<
		"Destroying an alien, or getting the ball to hit the left side of the screen\nincreases your score by one.\n\nDestroying aliens makes them angry, watch out!\n\n" <<
		"The first to 53 wins!\n\nDo you have what it takes?\n\n";
	system("PAUSE");

	Initialise(ciSCREEN_X, ciSCREEN_Y, false );

	//setting up game settings
	a_Initializer();
	//Invader setup
	a_SetUpInvaders();
	//And Game is here
	do{

		iFrameCount++;

		ClearScreen();

		a_UpDateGame();

		a_DrawGame();


	} while ( FrameworkUpdate() == false);


	Shutdown();

}

