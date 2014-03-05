//////////////////////////////////////////////////////////////////////////
//		@file				Functions.cpp
//		@details			The functions implementations
//		@author				Derek Potter
//		@version			1.0
//		@date last edited	10/30/2013
//////////////////////////////////////////////////////////////////////////

#include "AIE.h"
#include "Functions.h"
#include "Globals.h"
#include "OtherGlobals.h"
#include <math.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////
//		The games state switch
//////////////////////////////////////////////////////////////////////////
void (*GameState)();

//////////////////////////////////////////////////////////////////////////
//		Sets a_GameStae to the menu, and runs the initializer (needed so restart works correctally)
//////////////////////////////////////////////////////////////////////////
void StartGame(){

	GameState = &Menu;

	//player creation
	pPlayer.Create(CreateSprite(rcPlayerShip, ciPlayerWidth, ciPlayerHeight), ciSCREEN_X>>1, ciPlayerStartY, 0,0, ciPlayerWidth, ciPlayerHeight, ulPlayerFireRate);

	//EnemySetUp
	for(int i = 0; i < ciEnemyNumbers; i++){

		//Small Enemies (Fodder enemies)
		poSmallEnemies[i].Inisialize(CreateSprite(rcEnemyShips, ciSmallEnemyDimensions, ciSmallEnemyDimensions, true), ciSmallEnemyDimensions, 
										ciSmallEnemyDimensions, ciStartPos, ciStartPos, false);

		//The time before the enemies sart to fire
		poSmallEnemies[i].ptTimeToFire.Start(ulEnemyFireRate);

		//Medium Enemies (Attack Enemies)
		poMediumEnemies[i].Inisialize(CreateSprite(rcEnemyShips, ciMediumEnemyDimensions, ciMediumEnemyDimensions, true), ciMediumEnemyDimensions, 
										ciMediumEnemyDimensions, ciStartPos, ciStartPos, false);

		//Large Enemies (Destroyer enemies)
		poLargeEnemies[i].Inisialize(CreateSprite(rcEnemyShips, ciLargeEnemyDimensions, ciLargeEnemyDimensions, true), ciLargeEnemyDimensions, 
										ciLargeEnemyDimensions, ciStartPos, ciStartPos, false);

	}

	//bullet initialising
	for(int i = 0; i < ciArraySize; i++){

		poEnemyBullets[i].Inisialize(CreateSprite(rcStar, ciBulletDimensions, ciBulletDimensions, true), ciStartPos, ciStartPos, ciBulletDimensions,
										ciBulletDimensions, false);

		poPlayerBullets[i].Inisialize(CreateSprite(rcStar, ciBulletDimensions, ciBulletDimensions, true), ciStartPos, ciStartPos, ciBulletDimensions,
										ciBulletDimensions, false);
	}

	//setting up the stars
	for(int i = 0; i < ciStarArraySize; i++){

		poSmallStar[i].Inisialize(CreateSprite(rcStar, ciSmallStarDimensions, ciSmallStarDimensions, true), ciStartPos, ciStartPos, ciSmallStarDimensions,
									ciSmallStarDimensions, false);

		poMediumStar[i].Inisialize(CreateSprite(rcStar, ciMediumStarDimensions, ciMediumStarDimensions, true), ciStartPos, ciStartPos, ciMediumStarDimensions,
									ciMediumStarDimensions, false);

		poLargeStar[i].Inisialize(CreateSprite(rcStar, ciLargeStarDimensions, ciLargeStarDimensions, true), ciStartPos, ciStartPos, ciLargeStarDimensions,
									ciLargeStarDimensions, false);


	}
	
	//The spawn timer
	ptSmallEnemySpawn.Start(20);

	//creating the rest of the sprites

	uiMenu = CreateSprite(rcMenu, ciSCREEN_X>>1, ciSCREEN_Y>>1, true);

	poBackground.Inisialize(CreateSprite(rcBackground, ciSCREEN_X, ciSCREEN_Y, true), ciSCREEN_X>>1, ciSCREEN_Y>>1, ciSCREEN_X, ciSCREEN_Y, true);
	poMenu.Inisialize(uiMenu, ciSCREEN_X>>1, ciSCREEN_Y>>1, ciSCREEN_X>>1, ciSCREEN_Y>>1, true);
	poMenu.Draw(false, false);
	poLevel.Inisialize(CreateSprite(rcLevelOne, ciSCREEN_X, ciSCREEN_Y, true), ciSCREEN_X>>1, ciSCREEN_Y>>1, ciSCREEN_X, ciSCREEN_Y, true);
	poLevel.Draw(false, false);

	uiControls = CreateSprite(rcControls, ciSCREEN_X>>1, ciSCREEN_Y>>1, true);
	uiGameOver = CreateSprite(rcGameOver, ciSCREEN_X>>1, ciSCREEN_Y>>1, true); 
	uiGameMenu = CreateSprite(rcGameMenu, ciSCREEN_X>>1, ciSCREEN_Y>>1, true);
}

//////////////////////////////////////////////////////////////////////////
//		Sets up the main variables
//////////////////////////////////////////////////////////////////////////
void Restarter(){

	//player creation
	pPlayer.Create(pPlayer.GetSprite(), ciSCREEN_X>>1, ciPlayerStartY, 0,0, ciPlayerWidth, ciPlayerHeight, ulPlayerFireRate);

	//EnemySetUp
	for(int i = 0; i < ciEnemyNumbers; i++){

		//Small Enemies (Fodder enemies)
		poSmallEnemies[i].Inisialize(poSmallEnemies[i].GetSprite(), ciSmallEnemyDimensions, 
										ciSmallEnemyDimensions, ciStartPos, ciStartPos, false);

		//poSmallEnemies[i].ptFireRate.a_Start(ulPlayerFireRate);
		poSmallEnemies[i].ptTimeToFire.Start(ulEnemyFireRate);

		//Medium Enemies (Attack Enemies)
		poMediumEnemies[i].Inisialize(poMediumEnemies[i].GetSprite(), ciMediumEnemyDimensions, 
										ciMediumEnemyDimensions, ciStartPos, ciStartPos, false);

		//Large Enemies (Destroyer enemies)
		poLargeEnemies[i].Inisialize(poLargeEnemies[i].GetSprite(), ciLargeEnemyDimensions, 
										ciLargeEnemyDimensions, ciStartPos, ciStartPos, false);

	}

	//bullet initialising
	for(int i = 0; i < ciArraySize; i++){

		poEnemyBullets[i].Inisialize(poEnemyBullets[i].GetSprite(), ciStartPos, ciStartPos, ciBulletDimensions,
										ciBulletDimensions, false);

		poPlayerBullets[i].Inisialize(poPlayerBullets[i].GetSprite(), ciStartPos, ciStartPos, ciBulletDimensions,
										ciBulletDimensions, false);
	}

	//setting up the stars
	for(int i = 0; i < ciStarArraySize; i++){

		poSmallStar[i].Inisialize(poSmallStar[i].GetSprite(), ciStartPos, ciStartPos, ciSmallStarDimensions,
									ciSmallStarDimensions, false);

		poMediumStar[i].Inisialize(poMediumStar[i].GetSprite(), ciStartPos, ciStartPos, ciMediumStarDimensions,
									ciMediumStarDimensions, false);

		poLargeStar[i].Inisialize(poLargeStar[i].GetSprite(), ciStartPos, ciStartPos, ciLargeStarDimensions,
									ciLargeStarDimensions, false);


	}
	
	//reseting the spawn timer
	ptSmallEnemySpawn.Reset();


}

//////////////////////////////////////////////////////////////////////////
//		The Menu
//////////////////////////////////////////////////////////////////////////
void Menu(){

	//drawing the background, level background, and menu
	poBackground.Draw(false, false);
	poLevel.Draw(false, false);
	poMenu.Draw(false, false);

	//starts/resumes the game
	if(IsKeyDown(KEY_ENTER) && poMenu.GetSprite() != uiControls && poMenu.GetSprite() != uiGameOver){

		GameState = &UpDateGame;
		poMenu.SetSprite(uiGameMenu);

	}

	//restarts th game
	if(IsKeyDown(KEY_BACKSPACE) && poMenu.GetSprite() != uiControls && poMenu.GetSprite() != uiMenu){

		Restarter();
		GameState = &UpDateGame;

		if(poMenu.GetSprite() == uiGameOver)
			poMenu.SetSprite(uiGameMenu);

	}

	//goes to the controls screen from the games main menu
	if(IsKeyDown(KEY_LSHIFT) && poMenu.GetSprite() == uiMenu){
		poMenu.SetSprite(uiControls);
	}

	//goes from the controls back to the main menu
	if(IsKeyDown(KEY_LCTRL) && poMenu.GetSprite() == uiControls){
		poMenu.SetSprite(uiMenu);
	}
}

//////////////////////////////////////////////////////////////////////////
//		Runs the a_GameState which controls the games state
//////////////////////////////////////////////////////////////////////////
void GameRunner(){

		//shuts down the game
	if(IsKeyDown(KEY_ESC)){
		Shutdown();
		exit(1);
	}

	GameState();

}

//////////////////////////////////////////////////////////////////////////
//		Moves the player
//////////////////////////////////////////////////////////////////////////
void MovePlayer(){

			pPlayer.ptFireRate.Running();
	
	//Goes to the menu
	if(IsKeyDown(KEY_RSHIFT))
		GameState = &Menu;

	//or moves the player
	else{

		//Moves the player left
		if(IsKeyDown(KEY_LEFT) && pPlayer.TestScreenCollision(ciLeftCollision) && !IsKeyDown(KEY_RIGHT)){

			pPlayer.pSpeed.SetVector(cfPlayerSpeed * ciNOne, pPlayer.pSpeed.GetVectorY());

		}
		
		//Moves the player right
		else if(IsKeyDown(KEY_RIGHT) && !pPlayer.TestScreenCollision(ciRightCollision) && !IsKeyDown(KEY_LEFT)){

			pPlayer.pSpeed.SetVector(cfPlayerSpeed, pPlayer.pSpeed.GetVectorY());
		}

		//stops the player moving right or left if not moving left or right
		else
			pPlayer.pSpeed.SetVector(0, pPlayer.pSpeed.GetVectorY());

		//moves the player up
		if(IsKeyDown(KEY_UP) && pPlayer.TestScreenCollision(ciTopCollision) && !IsKeyDown(KEY_DOWN)){

			pPlayer.pSpeed.SetVector(pPlayer.pSpeed.GetVectorX(), cfPlayerSpeed * ciNOne);
		}

		//moves the player down
		else if(IsKeyDown(KEY_DOWN) && !pPlayer.TestScreenCollision(ciBottomCollision) && !IsKeyDown(KEY_UP)){

			pPlayer.pSpeed.SetVector(pPlayer.pSpeed.GetVectorX(), cfPlayerSpeed);
		}

		//stops the player from moving up or down if not moving up or down
		else
			pPlayer.pSpeed.SetVector(pPlayer.pSpeed.GetVectorX(), 0);

		//Fires the bullets
		if(IsKeyDown(KEY_SPACE) && pPlayer.ptFireRate.Stop()){

			pPlayer.TestScreenCollision(ciLeftCollision);//FireBullet(poPlayerOne, true);

		}

	}

}

//////////////////////////////////////////////////////////////////////////
//		Moves the Stars
//////////////////////////////////////////////////////////////////////////
void StarMover(){

	for(int i = 0; i < ciStarArraySize; i++){

		//if the stars are not moving, put them in a random position above the screen, and make them move down
		if(poSmallStar[i].pSpeed.GetVectorY() == 0){

			poSmallStar[i].Create(poSmallStar[i].GetSprite(), rand()% ciSCREEN_X , ciStartPos - rand() % ciStarYSpread, 0, cfStarSpeed, ciSmallStarDimensions, ciSmallStarDimensions, 0);

		}
		
		if(poMediumStar[i].pSpeed.GetVectorY() == 0){

			poMediumStar[i].Create(poMediumStar[i].GetSprite(), rand()% ciSCREEN_X , ciStartPos - rand() % ciStarYSpread, 0, cfStarSpeed * 2, ciMediumStarDimensions, ciMediumStarDimensions, 0);

		}

		if(poLargeStar[i].pSpeed.GetVectorY() == 0){

			poLargeStar[i].Create(poLargeStar[i].GetSprite(), rand()% ciSCREEN_X , ciStartPos - rand() % ciStarYSpread, 0, cfStarSpeed * 4, ciLargeStarDimensions, ciLargeStarDimensions, 0);


		}

	}
	
}

//////////////////////////////////////////////////////////////////////////
//		Where the game happens
//////////////////////////////////////////////////////////////////////////
void UpDateGame(){

	MovePlayer();

	StarMover();

	//Spawns an enemy if the timer reaches its end time
	ptSmallEnemySpawn.Running();
	if(ptSmallEnemySpawn.Stop()){

		SpawnEnemy();

	}

	MoveEnemy();

	BulletCollision();

	DrawGame();

}

//////////////////////////////////////////////////////////////////////////
//		Draws the game sprites  
//////////////////////////////////////////////////////////////////////////
void DrawGame(){

	//drawing the background and the level background
	poBackground.Draw(false, false);
	poLevel.Draw(false, false);

	//drawing the stars
	for(int i = 0; i < ciStarArraySize; i++){

		poSmallStar[i].Draw(false, true);
		poMediumStar[i].Draw(false, true);
		poLargeStar[i].Draw(false, true);

	}

	//drawing the enemies
	for(int i = 0; i < ciEnemyNumbers; i++){

		poSmallEnemies[i].Draw(false, true);

	}

	//drawing the bullets
	for(int i = 0; i < ciArraySize; i++){

		poPlayerBullets[i].Draw(false, false);
		poEnemyBullets[i].Draw(false, false);

	}

	//the player
	pPlayer.Draw();

	//drawing the score
	char cPrintScore[20] = {'\n'};
	sprintf_s(cPrintScore, "Score:  %d", pPlayer.GetScore());
	DrawString(cPrintScore, 1000, 50, SColour(0,0,0,255));

}

//////////////////////////////////////////////////////////////////////////
//		fires a bullet, desen't need to be a bool but its a fail safe to keep multiple bullets from firing
//////////////////////////////////////////////////////////////////////////
bool FireBullet(oObjects & rpObj, bool bIsPlayer){

	for(int i = 0; i < ciArraySize; i++){
		
		//if it is not the player firing, then use enemy bullets
		if(!bIsPlayer){

			if(!poEnemyBullets[i].GetAlive() && rpObj.ptFireRate.Stop()){

				rpObj.ptFireRate.Reset();

				//fires two based of of the firing positions
				poEnemyBullets[i].Create(poEnemyBullets[i].GetSprite(), rpObj.pPosition.GetVectorX() + iSmallEnemyFirePosOne[0],
												rpObj.pPosition.GetVectorY() + iSmallEnemyFirePosOne[1], 0, cfBulletSpeed, ciBulletDimensions, ciBulletDimensions, 0);

				poEnemyBullets[i+1].Create(poEnemyBullets[i+1].GetSprite(), rpObj.pPosition.GetVectorX() + iSmallEnemyFirePosOne[2],
												rpObj.pPosition.GetVectorY() + iSmallEnemyFirePosOne[3], 0, cfBulletSpeed, ciBulletDimensions, ciBulletDimensions, 0);

				return 0;
			}

		}

		//otherwise fire the player bullets
		else{

			if(!poPlayerBullets[i].GetAlive()&& rpObj.ptFireRate.Stop()){

				rpObj.ptFireRate.Reset();
				
				//fires two based on players fire positions
				poPlayerBullets[i].Create(poPlayerBullets[i].GetSprite(), rpObj.pPosition.GetVectorX() + iPlayerFirePositions[0],
												rpObj.pPosition.GetVectorY() + iPlayerFirePositions[1], 0, cfBulletSpeed * -1, ciBulletDimensions, ciBulletDimensions, 0);

				poPlayerBullets[i+1].Create(poPlayerBullets[i+1].GetSprite(), rpObj.pPosition.GetVectorX() + iPlayerFirePositions[2],
												rpObj.pPosition.GetVectorY() + iPlayerFirePositions[3], 0, cfBulletSpeed * -1, ciBulletDimensions, ciBulletDimensions, 0);
				return 0;
			}

		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//		moves the enemies according to their movement type, and destroys them  
//////////////////////////////////////////////////////////////////////////
void MoveEnemy(){

	for(int i = 0; i < ciEnemyNumbers; i++){

		if(poSmallEnemies[i].GetAlive()){

			RotateEnemy(poSmallEnemies[i]);

			//destroy time is unused
			poSmallEnemies[i].ptDestroyTime.Running();
			poSmallEnemies[i].ptDestroyTime.Stop();

			poSmallEnemies[i].ptTimeToFire.Running();
			poSmallEnemies[i].ptFireRate.Running();

			if(poSmallEnemies[i].ptTimeToFire.Stop() && poSmallEnemies[i].ptFireRate.Stop()){

				//FireBullet(poSmallEnemies[i], false);

			}
		}

	}


}

//////////////////////////////////////////////////////////////////////////
//		spawns enemies and resets spawn timer  
//////////////////////////////////////////////////////////////////////////
void SpawnEnemy(){

	//making sure only one enemy is spawned
	bool bEnemySpawned = false;

	for(int i = 0; i < ciEnemyNumbers; i++){

		if(bEnemySpawned == false && !poSmallEnemies[i].GetAlive()){

			/*poSmallEnemies[i].Create(poSmallEnemies[i].GetSprite(), rand() % ciSCREEN_X, 0 - rand()% ciSCREEN_Y + ciEnemyStartPosition, 0, 
										cfSmallEnemyBasicSpeed, ciSmallEnemyDimensions, ciSmallEnemyDimensions, ulEnemyFireRate);*/

			poSmallEnemies[i].Create(poSmallEnemies[i].GetSprite(), rand() % ciSCREEN_X, 390, 0, 
										0, ciSmallEnemyDimensions, ciSmallEnemyDimensions, ulEnemyFireRate);

			bEnemySpawned = true;

			ptSmallEnemySpawn.Reset();

		}

	}

}

void RotateEnemy(oObjects & rpObj){

	RotateSprite(rpObj.GetSprite(), rpObj.pPosition.GetAngle(pPlayer.pPosition));

}

//////////////////////////////////////////////////////////////////////////
//		Checks for collision between players and enemies bullets
//////////////////////////////////////////////////////////////////////////
void BulletCollision(){

	for(int i = 0; i < ciArraySize; i++){

		if(poPlayerBullets[i].GetAlive()){

			for(int j = 0; j < ciEnemyNumbers; j++){

				//check if an enemy has been hit by a player bullet, and kill it and increase score if true
				if(poSmallEnemies[j].GetAlive() && poPlayerBullets[i].GetAlive() && poSmallEnemies[j].TestCollision(poPlayerBullets[i])){

					poSmallEnemies[j].Kill();
					poPlayerBullets[i].Kill();
					pPlayer.IncreaseScore();

				}

			}

		}

		//check if an enemy bullet has hit the player, and kill it and go to the game over screen if true
		/*if(poEnemyBullets[i].GetAlive() && poEnemyBullets[i].TestCollision(pPlayer)){
			
			poEnemyBullets[i].Kill();
			pPlayer.Kill();
			poMenu.SetSprite(uiGameOver);
			GameState = &Menu;

		}*/

	}

}