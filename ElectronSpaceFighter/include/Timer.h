//////////////////////////////////////////////////////////////////////////
//		@file			Potter - Timer.h
//		@details		The timer for bullet firing, enemy spawning, and level length
//		@author			Derek Potter
//		@date created	10/7/2013
//////////////////////////////////////////////////////////////////////////
#pragma once

#ifndef _TIMER_H_
#define _TIMER_H_

class oTimer
{
public:
	oTimer();
	void a_Start(unsigned long ulRunTime);
	bool a_bStop();
	void a_Reset();
	unsigned long a_ulGetTime();
	void a_Running();
	~oTimer();

private:
	bool bRunning;
	unsigned long ulTime;
	unsigned long ulEndTime;
};





#endif