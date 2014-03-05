//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Sprite.h
//		@details		The Sprite Class
//		@author			Derek Potter
//		@date created	10/15/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Mathmatics.h"
#include "Globals.h"

class oSprite
{

public:

	oSprite();

	oVector2 pPosition;
	oVector2 pSpeed;

	virtual void oSprite::Create(float a_fPosX, float a_fPosY, float a_fSpeedX, float a_fSpeedY, int a_iWidth, int a_iHeight);

	virtual void oSprite::Draw() = 0;

	void oSprite::SetSprite(unsigned int a_uiSprite);
	unsigned int oSprite::GetSprite();

	void oSprite::SetAlive(bool a_bAlive);
	bool oSprite::GetAlive();

	void oSprite::SetDimensions(int a_iWidth, int a_iHeight);
	int oSprite::GetWidth();
	int oSprite::GetHeight();

	bool oSprite::TestScreenCollision(int a_TestSide);
	bool oSprite::TestCollision(oSprite & rpSprite);

	void oSprite::Kill();
	
	~oSprite();


private:

	unsigned int m_uiSprite;
	int m_iWidth;
	int m_iHeight;
	bool m_bAlive;

};


#endif