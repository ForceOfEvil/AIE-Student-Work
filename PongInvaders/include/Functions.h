//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Functions.h
//		@details		The functions (collision and vector math) for pong
//		@author			Derek Potter
//		@date created	9/16/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

struct oVector;

struct oObjects;

struct oOptions;

struct oBullet;
struct oInvader;

bool a_bInvaderAttack(oInvader & rpInv);
void a_SetUpInvaders();
void a_MoveInvader();
void a_MoveBullet();
int a_iInvaderScreenCollision(oInvader & rpInv);
int a_iBulletsScreenCollision(oBullet & rpBul);
void a_UpdateInvader(oInvader & rpInv);
void a_UpdateBullet(oBullet & rpBul);
bool a_bBulletToPaddleCollision(oObjects & rpPaddle, oBullet & rpBul);
bool a_bBulletToInvaderCollision(oBullet & rpBul, oInvader & rpInv); 
void a_Initializer();
oVector a_VectorAdd(oVector & rfv, oVector & rfv2);
void a_UpdateObject(oObjects & rpObj);
void a_PaddleCollision(oObjects & rpPaddleOne, oObjects & rpBall, oObjects & rpPaddleTwo);
int a_iTestScreenCollision(oObjects & rpObj);
void a_AI(oObjects & rpAI, oObjects & rpBall);
void a_MovePlayerBullet();
int a_iScore(oObjects & rpBall);
void a_UpDateGame();
void a_WinLose();
void a_DrawGame();

#endif