// CallInState.h: interface for the CCallInState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALLINSTATE_H__674C9425_4B3F_488F_97E7_91D16DD8C498__INCLUDED_)
#define AFX_CALLINSTATE_H__674C9425_4B3F_488F_97E7_91D16DD8C498__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StateBase.h"
#include "SipMessage.h"
#include "src\SocketStream.h"

/*enum StateMac{REGISER = 1,CALLOUT,CALLIN,MSG200,MSG302,MSG400};*/
#define  WAVEBUF 8196
class CCallInState : public CStateBase  
{
public:
	CCallInState();
	virtual ~CCallInState();
	LONG Run(void *vParam = NULL);
	LONG AtEndState(void *vparam);
	enum RegState{Begin = 0,Connecting,WaitACK,Wait200,
		RecvBye,Ringing,RecvCancel,Bye,Cancel,End};
	LONG OnRecvAck(void *vParam);
protected:
	LONG AtBeginState(void *vParam);
	LONG AtWaitACKState(void *vParam);
	LONG AtRingingState(void *vParam);
	LONG AtRecvCancelState(void *vParam);
	LONG AtWait200State(void *vParam);
	LONG AtRectByeState(void *vParam);
	LONG AtByeState(void *vParam);
	LONG AtCancenState(void *vParam);
private:
	int StrToSipMsgT(char *tMsg);
	unsigned short m_count;
	CSipMessage *m_sipMsg;
	CSocketStream *m_socket;
	osip_message_t *m_sipMsg_t;
	char m_callID[33];
	char m_sendMsg[BUFSIZ];
	unsigned long m_timerID;
//	CWaveOut *m_wave_out;
};

#endif // !defined(AFX_CALLINSTATE_H__674C9425_4B3F_488F_97E7_91D16DD8C498__INCLUDED_)
