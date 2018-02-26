#ifndef _PROC_QUEUE_H
#define _PROC_QUEUE_H

#include "AppThread.h"
#include "TimerQueue.h"

class CProcQueue : public CAppThread
{
public:
	CProcQueue(ULONG uSec = 100);
	~CProcQueue();
	virtual	ULONG Process();
	virtual void QueueProc();
	void SetQueueTime(ULONG uTimeValue /*∫¡√Î*/);
	virtual void AddToQueue(CTimerSession timerSession);
	CTimerQueue m_procQueue;
private:
	ULONG m_getQueueTime;
};

#endif /*_PROC_QUEUE_H*/