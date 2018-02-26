//////////////////////////////////////////////////////////////////////////
//�ļ���:TimerQueue.h
//��  ��:��ʱ�������࣬��Ӽ�ʱ������
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
	virtual void AddToQueue(CTimerSession timerSession);//��Ӽ�ʱ���Ự������
	virtual void Erase(TimerList::iterator it);
	TimerList m_timerList;		//��ʱ���Ự������
private:
	CAppMutex m_mutex;
};

#endif //_TIMER_QUEUE_H