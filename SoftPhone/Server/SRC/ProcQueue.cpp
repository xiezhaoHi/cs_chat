#ifndef _PROC_QUEUE_CPP
#define _PROC_QUEUE_CPP

#include "ProcQueue.h"

CProcQueue::CProcQueue(ULONG uSec)
{
	m_getQueueTime = uSec;
}

CProcQueue::~CProcQueue()
{

}

void CProcQueue::SetQueueTime(ULONG uTimeValue)
{
	m_getQueueTime = uTimeValue;
}

void CProcQueue::QueueProc()
{
	TimerList::iterator it = m_procQueue.m_timerList.begin();
	TimerList::iterator temp = it;
	while (it != m_procQueue.m_timerList.end())
	{
		temp = it;
		temp ++;
		it->RunProc();
		m_procQueue.m_timerList.erase(it);
		it = temp;
	}
}

ULONG CProcQueue::Process()
{
	while(1)
	{
		QueueProc();
		Sleep(m_getQueueTime);
	}
	return 0;
}

void CProcQueue::AddToQueue(CTimerSession timerSession)
{
	m_procQueue.AddToQueue(timerSession);
}

#endif /*_PROC_QUEUE_CPP*/