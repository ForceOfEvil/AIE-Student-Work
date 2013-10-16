#include "Objects.h"
#include "AIE.h"
#include <cstring>

int iKillPosition = -10;

oObjects::oObjects(){

}

void oObjects::a_Update(){

	pPosition.a_VectorAdd(pPosition, pSpeed);


}

void oObjects::a_Inisialize(unsigned int uiSetSprite, int iStartPosX, int iStartPosY, int iWide, int iTall){

	iWidth = iWide;
	iHeight= iTall;
	pPosition.a_SetVector(iStartPosX, iStartPosY);
	uiSprite = uiSetSprite;
	bAlive = 0;

}

void oObjects::a_Draw(){

	DrawSprite(uiSprite);

}

void oObjects::a_SetSprite(unsigned int uiNewSprite){

	uiSprite = uiNewSprite;

}

void oObjects::a_SetDimensions(int iX, int iY){

	iHeight = iX;
	iWidth = iY;

}

void oObjects::a_SetMovement(teMovementPatterns & rempMove){

	empMove = rempMove;

}

teMovementPatterns oObjects::a_GetMovement(){

	return empMove;

}

void oObjects::a_Kill(){

	bAlive = false;
	pPosition.a_SetVector(iKillPosition, iKillPosition);
	pSpeed.a_SetVector(0,0);

}

void oObjects::a_Create(float fPosX, float fPosY, float fSpeedX, float fSpeedY, unsigned int uiNewSprite){

	bAlive = true;
	pPosition.a_SetVector(fPosX, fPosY);
	pSpeed.a_SetVector(fSpeedX, fSpeedY);
	a_SetSprite(uiNewSprite);

}

oObjects::~oObjects(){

}