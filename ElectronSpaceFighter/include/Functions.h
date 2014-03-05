//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Functions.h
//		@details		The functions (collision and vector math) for ElectronSpaceFighter
//		@author			Derek Potter
//		@date created	9/30/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "Objects.h"
#include "PlayerClass.h"
#include "Timer.h"

void StartGame();
void Restarter();

void Menu();
void GameRunner();

void MovePlayer();

void StarMover();

int TestScreenCollision(oObjects & rpObj);

void UpDateGame();
void DrawGame();

bool FireBullet(oObjects & rpObj, bool bIsPlayer);

void MoveEnemy();
void SpawnEnemy();

void RotateEnemy(oObjects & rpObj);

void BulletCollision();

#endif