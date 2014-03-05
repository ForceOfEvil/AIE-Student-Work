//////////////////////////////////////////////////////////////////////////
//		@file			Potter - PlayerClass.h
//		@details		The Player Class
//		@author			Derek Potter
//		@date created	10/15/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _PLAYERCLASS_H_
#define _PLAYERCLASS_H_

#include "Sprite.h"
#include "Timer.h"
#include "Mathmatics.h"

class oPlayer : public oSprite
{

public:

	oPlayer();

	oVector2 pPosition;
	oVector2 pSpeed;
	oTimer ptFireRate;

	void oPlayer::Create(unsigned int a_uiSprite, float a_fPosX, float a_fPosY, float a_fSpeedX, float a_fSpeedY, int a_iWidth, int a_iHeight, unsigned long a_ulFireRate);
	void oPlayer::Draw();

	void oPlayer::IncreaseScore();
	int oPlayer::GetScore();
	
	~oPlayer();


private:

	int m_iScore;

};


#endif