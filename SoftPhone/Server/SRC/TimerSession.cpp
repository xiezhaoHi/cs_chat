#ifndef _TIMER_SESSION_CPP
#define _TIMER_SESSION_CPP

#include "TimerSession.h"

CTimerSession::CTimerSession()
{
	m_timeValue = Time_Value::zero;
	m_TimeOutProc = NULL;
	m_param = NULL;
	m_count = ++TimeSessionID;
}

CTimerSession::~CTimerSession()
{

}

bool CTimerSession::operator == (const CTimerSession &tv2)
{
	return m_timeValue == tv2.m_timeValue;
}

bool CTimerSession::operator > (const CTimerSession &tv2)
{
	return m_timeValue > tv2.m_timeValue;
}

bool CTimerSession::operator < (const CTimerSession &tv2)
{
	return m_timeValue < tv2.m_timeValue;
}

bool CTimerSession::operator != (const CTimerSession &tv2)
{
	return m_timeValue != tv2.m_timeValue;
}

bool CTimerSession::operator >= (const CTimerSession &tv2)
{
	return m_timeValue >= tv2.m_timeValue;
}

bool CTimerSession::operator <= (const CTimerSession &tv2)
{
	return m_timeValue <= tv2.m_timeValue;
}


void CTimerSession::SetTimerQueue(Time_Value timeValue,
								  long (*TimeOutProc)(void *),
								  void *param)
{
	m_timeValue = timeValue;
	m_TimeOutProc = TimeOutProc;
	m_param = param;
}

void CTimerSession::RunProc()
{
	m_TimeOutProc(m_param);
}

unsigned long CTimerSession::GetSessionID()
{
	return m_count;
}
#endif /*_TIMER_SESSION_CPP*/