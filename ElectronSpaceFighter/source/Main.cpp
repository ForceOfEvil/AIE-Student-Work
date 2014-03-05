//////////////////////////////////////////////////////////////////////////
//		@file				ElectronSpaceFighter
//		@details			A topdown shooter with electron style boss fights (not acctually)
//		@author				Derek Potter
//		@version			1.0
//		@date created		9/30/2013
//////////////////////////////////////////////////////////////////////////

#include "AIE.h"
#include "Functions.h"
#include <iostream>

using namespace std;

int iFrameCount;

//////////////////////////////////////////////////////////////////////////
//		Sets up the game and variables, then goes to the menu
//////////////////////////////////////////////////////////////////////////
void main(){

	Initialise(ciSCREEN_X, ciSCREEN_Y, false );

	//setting up game settings
	StartGame();

	//And Game is here
	do{

		iFrameCount++;

		ClearScreen();

		GameRunner();

	} while ( FrameworkUpdate() == false);


	Shutdown();

}