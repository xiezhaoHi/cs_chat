#ifndef _MESSAGEQUEUE_CPP
#define _MESSAGEQUEUE_CPP

#include "MessageQueue.h"

CMessage::CMessage()
{

}

CMessage::CMessage(unsigned long msgType,void * lparam,void * wparam)
{
	m_msgType = msgType;
	m_lparam = lparam;
	m_wparam = wparam;
}

CMessage::~CMessage()
{
//	delete m_lparam;
//	delete m_wparam;
}
//////////////////////////////////////////////////////////////////////////

CMsgQueue::CMsgQueue()
{
	m_msgPoint = new CMessage;
}

CMsgQueue::~CMsgQueue()
{
	delete m_msgPoint;
}

bool CMsgQueue::AddMsg(CMessage *msg)
{
	m_mutex.Lock();
	m_msgQueue.push(msg);
	m_mutex.UnLock();
	return true;
}

bool CMsgQueue::IsEmpty()
{
	return m_msgQueue.empty();
}

CMessage *CMsgQueue::GetMsg()
{
	m_mutex.Lock();
	CMessage *tMsg;
	if (m_msgQueue.empty())
	{
		return NULL;
	}
	tMsg = m_msgQueue.front();
	memcpy(m_msgPoint,tMsg,sizeof(CMessage));
	m_msgQueue.pop();
	delete tMsg;
	m_mutex.UnLock();
	return m_msgPoint;
}

IMsgQueueControl::IMsgQueueControl(CMsgQueue *msgQueue /* = NULL */)
{

	m_msgQueue = m_msgQueue;
}

#endif /*_MESSAGEQUEUE_CPP*/