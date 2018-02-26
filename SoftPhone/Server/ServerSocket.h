// ReadSocket.h: interface for the CReadSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READSOCKET_H__C341C856_B79B_49DB_B96C_5152C5D9FE99__INCLUDED_)
#define AFX_READSOCKET_H__C341C856_B79B_49DB_B96C_5152C5D9FE99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRC\AppThread.h"

class CServerSocket : public CAppThread  
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	void SetMsgQueue(CMsgQueue *msgQueue);
	CSocketStream* GetSockStream();
	ULONG Process();
protected:
	CSocketStream *m_socket;
	CSocketBase m_sockBase;
	CMsgQueue *m_msgQueue;
};

#endif // !defined(AFX_READSOCKET_H__C341C856_B79B_49DB_B96C_5152C5D9FE99__INCLUDED_)
