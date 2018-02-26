#ifndef _TIMER_CPP
#define _TIMER_CPP

#include "Timer.h"

CTimer::CTimer(CProcQueue *procQueue,ULONG uSec)
{
	m_getQueueTime = uSec;
	m_procQueue = procQueue;
}

CTimer::~CTimer()
{
}

void CTimer::SetProcQueue(CProcQueue *m_procQueue)
{
	m_procQueue = m_procQueue;
}

void CTimer::SetQueueTime(ULONG uTimeValue)
{
	m_getQueueTime = uTimeValue;
}

void CTimer::TimeOutProc()
{
	Time_Value timeNow = Time_Value::GetTimeofday();
	TimerList::iterator it = m_timerQueue.m_timerList.begin();
	TimerList::iterator temp = it;
	m_mutex.Lock();
	while (it != m_timerQueue.m_timerList.end())
	{
		temp = it;
		temp ++;
		if (it->m_timeValue < timeNow)
		{

			if (m_procQueue == NULL)
			{
				it->RunProc();
			}
			else
			{
				m_procQueue->AddToQueue(*it);
			}
			m_timerQueue.Erase(it);		
		}
		it = temp;
	}
	m_mutex.UnLock();
}

ULONG CTimer::Process()
{
	while(1)
	{
		TimeOutProc();
  		Sleep(m_getQueueTime);
	}
	return 0;
}

void CTimer::AddToQueue(CTimerSession timerSession)
{
	m_mutex.Lock();
	m_timerQueue.AddToQueue(timerSession);
	m_mutex.UnLock();
}

unsigned long CTimer::SetTimer(Time_Value timeValue,
					  long (*TimeOutProc)(void *),
					  void *param)
{
	
	m_timeSession.SetTimerQueue(timeValue,TimeOutProc,param);
	AddToQueue(m_timeSession);
	return m_timeSession.GetSessionID();
	
}

unsigned long  CTimer::SetTimer(UINT timeValue,
					  long (*TimeOutProc)(void *),
					  void *param)
{
	Time_Value timeNow = Time_Value::GetTimeofday();
	timeNow += timeValue;
	m_timeSession.SetTimerQueue(timeNow,TimeOutProc,param);
	AddToQueue(m_timeSession);
	return m_timeSession.GetSessionID();
}

bool CTimer::Erase(unsigned int timerID)
{
	TimerList::iterator it = m_timerQueue.m_timerList.begin();
	m_mutex.Lock();
	while (it != m_timerQueue.m_timerList.end())
	{
		if (it->GetSessionID() != timerID)
		{
			it++;
			continue;	
		}
		m_timerQueue.m_timerList.erase(it);
		break;
	}
	m_mutex.UnLock();
	if (it != m_timerQueue.m_timerList.end())
	{
		return true;
	}
	return false;
}  

#endif /*_TIMER_CPP*/