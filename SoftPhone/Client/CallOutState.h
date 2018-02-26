// CallOutState.h: interface for the CCallOutState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALLOUTSTATE_H__0993B08E_C3DA_469E_9151_7800BEDF59D2__INCLUDED_)
#define AFX_CALLOUTSTATE_H__0993B08E_C3DA_469E_9151_7800BEDF59D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StateBase.h"
#include "SipMessage.h"
#include "src\SocketStream.h"



class CCallOutState : public CStateBase  
{
public:
	CCallOutState();
	virtual ~CCallOutState();
	LONG Run(void *vParam = NULL);
	enum RegState{Begin = 0,Connecting,Wait302,Wait180,Wait200,Cancel,Bye,End};
	enum Msg200{FromClient,FromCancel,FromBye};
	static void OnStateChange();
	LONG OnRecv200Msg(void *vParam);
	LONG OnRecv180_100Msg(void *vParam);
	LONG OnRecv302Msg(void *vParam);
	LONG OnRecvByeMsg(void *vParam);
protected:
	LONG AtBeginState(void *vParam);
	LONG AtWait302State(void *vParam);
	LONG AtWait180State(void *vParam);
	LONG AtWait200State(void *vParam);
	LONG AtCancelState(void *vParam);
	LONG AtByeState(void *vParam);
	LONG AtEndState(void *vparam);
	LONG SendAck(void *vParam);
private:
	int StrToSipMsgT(char *tMsg);
	CSipMessage *m_sipMsg;
	char m_callID[33];
	Msg200 m_msg200Flag;
	unsigned long m_timerID;
	unsigned short m_count;
	char *m_sendReg;
	osip_message_t *m_sipMsg_t;
	char *m_remoteName;
};

#endif // !defined(AFX_CALLOUTSTATE_H__0993B08E_C3DA_469E_9151_7800BEDF59D2__INCLUDED_)
