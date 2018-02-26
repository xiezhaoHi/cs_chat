// RegState.h: interface for the CRegState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGSTATE_H__AD6A4C49_32FC_4322_918E_42B459C0D270__INCLUDED_)
#define AFX_REGSTATE_H__AD6A4C49_32FC_4322_918E_42B459C0D270__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define KEEPLIFE 50

#include "StateBase.h"
#include "IOSocket.h"
#include "TimerSession.h"

class CRegState : public CStateBase  
{
public:
	CRegState();
	virtual ~CRegState();
	LONG Run(void *vParam = NULL);
	enum RegState{Begin = 0,KeepLift,Wait200,End};
	void SetRegState();
	LONG UnRegister();
protected:
	LONG AtBeginState(void *vParam);
	LONG AtKeepLiftState(void *vParam);
	LONG AtEndState(void *vParam);
	LONG AtWait200State(void *vParam);
private:
	unsigned long m_timerID;
	unsigned short m_count;
 	CSipMessage *m_sipMsg;
	bool m_isRegMsg;					//标识注册消息，注册为true,反注册为false
	char *m_sendReg;

};

#endif // !defined(AFX_REGSTATE_H__AD6A4C49_32FC_4322_918E_42B459C0D270__INCLUDED_)
