//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Pong
//		@details		A pong game
//		@author			Derek Potter
//		@version		1.0
//		@date created	9/11/2013
//////////////////////////////////////////////////////////////////////////



#define _USE_MATH_DEFINES

#include "AIE.h"
#include "Functions.h"
#include <string>
#include <cmath>
#include <assert.h>
#include <crtdbg.h>
#include <ctime>
#include <iostream>


const int ciSCREEN_X = 1280;
const int ciSCREEN_Y = 780;

int iFrameCount;

//////////////////////////////////////////////////////////////////////////
//		Sets up the game and variables, then goes to the menu
//////////////////////////////////////////////////////////////////////////
void main(){
	
	Initialise(ciSCREEN_X, ciSCREEN_Y, false );
	a_Initialize();
	//And Game is here
	do{
		iFrameCount++;

		ClearScreen();

		a_UpDateGame();

		a_DrawGame();

	} while ( FrameworkUpdate() == false);



	Shutdown();

}