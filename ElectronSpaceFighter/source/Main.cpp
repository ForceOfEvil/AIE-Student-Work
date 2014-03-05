//////////////////////////////////////////////////////////////////////////
//		@file				ElectronSpaceFighter
//		@details			A topdown shooter with electron style boss fights
//		@author				Derek Potter
//		@version			1.0
//		@date created	9/30/2013
//////////////////////////////////////////////////////////////////////////

#include "AIE.h"
#include "Functions.h"
#include <iostream>

using namespace std;

const int ciSCREEN_X = 1280;
const int ciSCREEN_Y = 780;

int iFrameCount;

//////////////////////////////////////////////////////////////////////////
//		Sets up the game and variables, then goes to the menu
//////////////////////////////////////////////////////////////////////////
void main(){

	Initialise(ciSCREEN_X, ciSCREEN_Y, false );

	//setting up game settings
	a_Initializer();

	//And Game is here
	do{

		iFrameCount++;

		ClearScreen();

		a_GameRunner();

	} while ( FrameworkUpdate() == false);


	Shutdown();

}