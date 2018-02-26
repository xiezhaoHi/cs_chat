//////////////////////////////////////////////////////////////////////////
//�ļ���:Timer.h
//��  ��:�Գ�ʱ��Ϣ���д���
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
	CTimer(CProcQueue *procQueue = NULL,/*��Ϣ����ָ��*/
		   ULONG uSec = 100 /*����������ʱ�䣬��λ����*/);
	virtual ~CTimer();
	void SetProcQueue(CProcQueue *m_procQueue); /*������Ϣ����ָ��*/
	void SetQueueTime(ULONG uTimeValue/*����*/);
	virtual unsigned long SetTimer(Time_Value timeValue,
						  long (*TimeOutProc)(void *),
						  void *param);
	virtual unsigned long SetTimer(UINT timeValue,
						  long (*TimeOutProc)(void *),
						  void *param);
	bool Erase(unsigned int timerID);
protected:
	virtual void AddToQueue(CTimerSession timerSession);/*��ӵ���ʱ������*/
	virtual	ULONG Process();	/*����������*/
	virtual void TimeOutProc();	/*�ж��Ƿ�ʱ*/
	CTimerQueue m_timerQueue;	/*��ʱ������*/
	ULONG m_getQueueTime;		/*����������ʱ�䣬��λ����*/
	CProcQueue *m_procQueue;	/*��Ϣ����ָ��*/
	CTimerSession m_timeSession;
//	CAppMutex m_mutex;
};

#endif//_TIMER_H