#ifndef _MESSAGEQUEUE_H
#define _MESSAGEQUEUE_H

#include <queue>
#include "AppMutex.h"
#include "AppThread.h"

class CMessage
{
public:
	CMessage();
	CMessage(unsigned long msgType,void * lparam,void * wparam);
	~CMessage();
	unsigned long m_msgType;
	void *m_lparam;
	void *m_wparam;
};

typedef std::queue<CMessage*> MSGQueue;

class CMsgQueue
{
public:
	CMsgQueue();
	~CMsgQueue();
	CMessage* GetMsg();
	bool IsEmpty();
	bool AddMsg(CMessage *msg);
protected:
	MSGQueue m_msgQueue;
	CAppMutex m_mutex;
	CMessage *m_msgPoint;
};

class IMsgQueueControl:public CAppThread
{
public:
	IMsgQueueControl(CMsgQueue *msgQueue = NULL);
protected:
	CMsgQueue *m_msgQueue;
};

#endif /*_MESSAGEQUEUE_CPP*/