//////////////////////////////////////////////////////////////////////////
//文件名:Timer.h
//作  用:对超时消息进行处理
//
//////////////////////////////////////////////////////////////////////////
#ifndef _TIMER_H
#define _TIMER_H

#include "AppThread.h"
#include "TimerQueue.h"
#include "ProcQueue.h"
#include "AppMutex.h"

typedef list<CTimerSession> TimerList;

class CTimer : public CAppThread
{
public:
	CTimer(CProcQueue *procQueue = NULL,/*消息队列指针*/
		   ULONG uSec = 100 /*函数处理间隔时间，单位毫秒*/);
	virtual ~CTimer();
	void SetProcQueue(CProcQueue *m_procQueue); /*设置消息队列指针*/
	void SetQueueTime(ULONG uTimeValue/*毫秒*/);
	virtual unsigned long SetTimer(Time_Value timeValue,
						  long (*TimeOutProc)(void *),
						  void *param);
	virtual unsigned long SetTimer(UINT timeValue,
						  long (*TimeOutProc)(void *),
						  void *param);
	bool Erase(unsigned int timerID);
protected:
	virtual void AddToQueue(CTimerSession timerSession);/*添加到计时器队列*/
	virtual	ULONG Process();	/*处理主函数*/
	virtual void TimeOutProc();	/*判断是否超时*/
	CTimerQueue m_timerQueue;	/*计时器队列*/
	ULONG m_getQueueTime;		/*函数处理间隔时间，单位毫秒*/
	CProcQueue *m_procQueue;	/*消息队列指针*/
	CTimerSession m_timeSession;
//	CAppMutex m_mutex;
};

#endif//_TIMER_H