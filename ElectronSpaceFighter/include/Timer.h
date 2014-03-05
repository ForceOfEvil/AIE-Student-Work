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
	void Start(unsigned long a_ulEndTime);
	bool Stop();
	void Reset();
	unsigned long GetTime();
	void Running();
	~oTimer();

private:
	bool m_bRunning;
	unsigned long m_ulTime;
	unsigned long m_ulEndTime;
};





#endif