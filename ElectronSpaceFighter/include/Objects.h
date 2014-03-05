//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Objects.h
//		@details		The Objects Class
//		@author			Derek Potter
//		@date created	10/15/2013
//////////////////////////////////////////////////////////////////////////

#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "Timer.h"
#include "Mathmatics.h"

class oObjects
{

public:

	oObjects();

	oVector2 pPosition;
	oVector2 pSpeed;
	oTimer ptFireRate;
	oTimer ptTimeToFire;
	oTimer ptDestroyTime;

	void oObjects::Inisialize(unsigned int a_uiSprite, float a_fStartPosX, float a_fStartPosY, int a_iWidth, int a_iHeight, bool a_bAlive);
	void oObjects::Draw(bool a_bIsPlayer, bool a_bIsStar);

	void oObjects::SetSprite(unsigned int a_uiSprite);
	unsigned int oObjects::GetSprite();

	bool oObjects::GetAlive();

	void oObjects::IncreaseScore();
	int oObjects::GetScore();

	void oObjects::SetDimensions(int a_iWidth, int a_iHeight);
	int oObjects::GetWidth();
	int oObjects::GetHeight();

	int oObjects::TestScreenCollision();
	bool oObjects::TestCollision(oObjects & rpObj);

	void oObjects::Kill();

	void oObjects::Create(unsigned int a_uiSprite, float a_fPosX, float a_fPosY, float a_fSpeedX, float a_fSpeedY, int a_iWidth, int a_iHeight, unsigned long a_ulFireRate);
	
	~oObjects();


private:

	unsigned int m_uiSprite;
	int m_iWidth;
	int m_iHeight;
	bool m_bAlive;
	int m_iScore;


};


#endif