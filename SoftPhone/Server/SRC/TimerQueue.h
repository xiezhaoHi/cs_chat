//////////////////////////////////////////////////////////////////////////
//文件名:TimerQueue.h
//作  用:计时器队列类，添加计时器队列
//
//////////////////////////////////////////////////////////////////////////


#ifndef _TIMER_QUEUE_H
#define _TIMER_QUEUE_H

#include "TimerSession.h"
#include "AppMutex.h"
#include <list>

using namespace std;
typedef list<CTimerSession> TimerList;
class CTimerQueue
{
public:
	CTimerQueue();
	~CTimerQueue();
	virtual void AddToQueue(CTimerSession timerSession);//添加计时器会话到队列
	virtual void Erase(TimerList::iterator it);
	TimerList m_timerList;		//计时器会话到队列
private:
	CAppMutex m_mutex;
};

#endif //_TIMER_QUEUE_H