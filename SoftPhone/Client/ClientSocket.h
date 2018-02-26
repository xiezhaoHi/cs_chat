// ClientSocket.h: interface for the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTSOCKET_H__EAB1FC5E_B7A1_4A63_994F_51966AA05423__INCLUDED_)
#define AFX_CLIENTSOCKET_H__EAB1FC5E_B7A1_4A63_994F_51966AA05423__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRC\AppThread.h"

class CClientSocket : public CAppThread  
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	void SetMsgQueue(CMsgQueue *msgQueue);
	CSocketStream* GetSocketStream();
	ULONG Process();
	CSocketStream* GetSockStream();
protected:
	CSocketStream *m_socket;
	CSocketBase m_sockBase;
	CMsgQueue *m_msgQueue;

};

#endif // !defined(AFX_CLIENTSOCKET_H__EAB1FC5E_B7A1_4A63_994F_51966AA05423__INCLUDED_)
