#include "Ships.h"
#include "AIE.h"



oShips::oShips(){

}

void oShips::a_Inisialize(unsigned int uiSprite, int iWide, int iTall, unsigned long ulPositions[10], bool bFireFromCenter){
	
	pfvPositions.pvFireOne.a_SetVector(ulPositions[2], ulPositions[3]);
	pfvPositions.pvFireTwo.a_SetVector(ulPositions[4], ulPositions[5]);
	pfvPositions.pvFireThree.a_SetVector(ulPositions[6], ulPositions[7]);
	pfvPositions.pvFireFour.a_SetVector(ulPositions[8], ulPositions[9]);

	poData.a_Inisialize(ulPositions[0], ulPositions[1], uiSprite, iWide, iTall);

	bCenterFire = bFireFromCenter;

	poData.a_SetSprite(uiSprite);

}

void oShips::a_Kill(){

	poData.a_Kill();

}

void oShips::Create(unsigned int uiSprite, int iWide, int iTall, float fPosX, float fPosY, float fSpeedX, float fSpeedY, oFourVectors pfvFirePositions, 
			oFiveTimers pftRateOfFire, oFiveTimers pftFireTimer, bool bFireFromCenter, unsigned long ulDestroyTime, oFiveMovements pfmBulletMoveStyles){

	poData.a_Create(fPosX,fPosY, fSpeedX, fSpeedY, uiSprite);

	pfvPositions = pfvFirePositions;

	pftTimeToFire = pftFireTimer;

	pftFireRate = pftRateOfFire;

	bCenterFire = bFireFromCenter;

	ptCanDestroy.a_Start(ulDestroyTime);

	pfmMoveStyle = pfmBulletMoveStyles;

}

oShips::~oShips(){


}