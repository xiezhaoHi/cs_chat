// RegStateMac.h: interface for the CRegStateMac class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGSTATEMAC_H__6C7FB3AA_F8C1_4C9F_A2FB_D3462841B768__INCLUDED_)
#define AFX_REGSTATEMAC_H__6C7FB3AA_F8C1_4C9F_A2FB_D3462841B768__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StateBase.h"
#include "SipMessage.h"
#include "src\SocketStream.h"

class CRegStateMac : public CStateBase  
{
public:
	CRegStateMac();
	virtual ~CRegStateMac();
	LONG Run(void *vParam = NULL);
	enum RegState{Begin = 0,Registed,End};
	LONG InviteState(void *vParam = NULL);
protected:
	LONG AtBeginState(void *vParam);
	LONG AtRegistedState(void *vParam);
	LONG AtEndState(void *vParam);
	bool CheckUserInfo(char *pInfo);

private:
	int StrToSipMsgT(char *tMsg);
	unsigned short m_count;
	CSipMessage *m_sipMsg;
	CSocketStream *m_socket;
	osip_message_t *m_sipMsg_t;
	char m_callID[33];
	char m_sendMsg[BUFSIZ];
	unsigned long m_timerID;
};

#endif // !defined(AFX_REGSTATEMAC_H__6C7FB3AA_F8C1_4C9F_A2FB_D3462841B768__INCLUDED_)
