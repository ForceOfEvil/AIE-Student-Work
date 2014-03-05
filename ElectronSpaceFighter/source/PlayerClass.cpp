//////////////////////////////////////////////////////////////////////////
//		@file				Objects.cpp
//		@details			Objects class implementation
//		@author				Derek Potter
//		@version			1.0
//		@date last edited	10/30/2013
//////////////////////////////////////////////////////////////////////////
#include "PlayerClass.h"
#include "AIE.h"
#include <cstring>

//////////////////////////////////////////////////////////////////////////
//		The constructor, blank because more options are needed to inisialise objects
//////////////////////////////////////////////////////////////////////////
oPlayer::oPlayer(){
	m_iScore = 0;
}

//////////////////////////////////////////////////////////////////////////
//		Fully creates an object
//////////////////////////////////////////////////////////////////////////
void oPlayer::Create(unsigned int a_uiSprite, float a_fPosX, float a_fPosY, float a_fSpeedX, float a_fSpeedY, int a_iWidth, int a_iHeight, unsigned long a_ulFireRate){

	SetAlive(true);
	SetDimensions(a_iWidth, a_iHeight);
	pPosition.SetVector(a_fPosX, a_fPosY);
	pSpeed.SetVector(a_fSpeedX, a_fSpeedY);
	ptFireRate.Start(a_ulFireRate);
	SetSprite(a_uiSprite);
	m_iScore = 0;

}

//////////////////////////////////////////////////////////////////////////
//		moves an object, draws an object, and tests if it has collided with the screen and kills it
//////////////////////////////////////////////////////////////////////////
void oPlayer::Draw(){

	if(GetAlive()){
	pPosition += pSpeed;
	MoveSprite(GetSprite(), pPosition.GetVectorX(), pPosition.GetVectorY());
	DrawSprite(GetSprite());
	}

}

//////////////////////////////////////////////////////////////////////////
//		increases the score
//////////////////////////////////////////////////////////////////////////
void oPlayer::IncreaseScore(){

	m_iScore++;

}

//////////////////////////////////////////////////////////////////////////
//		returns the score
//////////////////////////////////////////////////////////////////////////
int oPlayer::GetScore(){
	
	return m_iScore;

}

//////////////////////////////////////////////////////////////////////////
//		Destructor
//////////////////////////////////////////////////////////////////////////
oPlayer::~oPlayer(){
	//Science!
}