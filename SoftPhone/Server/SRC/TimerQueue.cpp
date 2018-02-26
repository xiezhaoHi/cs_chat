#ifndef _TIMER_QUEUE_CPP
#define _TIMER_QUEUE_CPP


#include "TimerQueue.h"

CTimerQueue::CTimerQueue()
{

}

CTimerQueue::~CTimerQueue()
{

}

void CTimerQueue::AddToQueue(CTimerSession timerSession)
{
	m_mutex.Lock();
	m_timerList.push_back(timerSession);
	m_timerList.sort();
	m_mutex.UnLock();
}

void CTimerQueue::Erase(TimerList::iterator it)
{
	m_mutex.Lock();
	m_timerList.erase(it);
	m_mutex.UnLock();
}

#endif