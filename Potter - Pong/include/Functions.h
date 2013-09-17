//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Functions.h
//		@details		The functions (collision and vector math) for pong
//		@author			Derek Potter
//		@date created	9/16/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "AIE.h"


struct oVector;



struct oObjects;

struct oOptions;


void a_Initialize();
oVector a_VectorAdd(oVector & rfv, oVector & rfv2);
void a_UpdateObject(oObjects & rpObj);
void a_bPaddleCollision(oObjects & rpPaddleOne, oObjects & rpBall, oObjects & rpPaddleTwo);
int a_iTestScreenCollision(oObjects & rpObj);
void a_AI(oObjects & rpAI, oObjects & rpBall);
int a_iScore(oObjects & rpBall);
void a_UpDateGame();
void a_WinLose();
void a_End();
void a_DrawGame();

#endif