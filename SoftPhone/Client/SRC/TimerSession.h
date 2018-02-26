//////////////////////////////////////////////////////////////////////////
//文件名:TimerQueue.h
//作  用:计时器会话类
//
//////////////////////////////////////////////////////////////////////////
#ifndef _TIMER_SESSION_H
#define _TIMER_SESSION_H

#include "Time_Value.h"
static unsigned long TimeSessionID = 0;

class CTimerSession
{
public:
	CTimerSession();
	virtual ~CTimerSession();
	virtual void SetTimerQueue(Time_Value timeValue,
							   long (*TimeOutProc)(void *),
							   void *param);		//初始化会话类
	bool operator == (const CTimerSession &tv2);
	bool operator >	 (const CTimerSession &tv2);
	bool operator <  (const CTimerSession &tv2);
	bool operator != (const CTimerSession &tv2);
	bool operator >= (const CTimerSession &tv2);
	bool operator <= (const CTimerSession &tv2);
	void RunProc();								//执行函数
	Time_Value m_timeValue;						//时间
	unsigned long GetSessionID();
private:
	void *m_param;								//函数参数
 	long (*m_TimeOutProc)(void *);				//函数指针
	unsigned long m_count;
};

#endif