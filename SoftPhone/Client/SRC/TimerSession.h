//////////////////////////////////////////////////////////////////////////
//�ļ���:TimerQueue.h
//��  ��:��ʱ���Ự��
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
							   void *param);		//��ʼ���Ự��
	bool operator == (const CTimerSession &tv2);
	bool operator >	 (const CTimerSession &tv2);
	bool operator <  (const CTimerSession &tv2);
	bool operator != (const CTimerSession &tv2);
	bool operator >= (const CTimerSession &tv2);
	bool operator <= (const CTimerSession &tv2);
	void RunProc();								//ִ�к���
	Time_Value m_timeValue;						//ʱ��
	unsigned long GetSessionID();
private:
	void *m_param;								//��������
 	long (*m_TimeOutProc)(void *);				//����ָ��
	unsigned long m_count;
};

#endif