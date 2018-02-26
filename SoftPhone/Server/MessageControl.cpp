// MessageControl.cpp: implementation of the CMessageControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"
#include "MessageControl.h"
#include "SipMessage.h"
#include "RegStateMac.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessageControl::CMessageControl()
{
	m_msgQueue = new CMsgQueue;
}

CMessageControl::~CMessageControl()
{
	if (m_msgQueue != NULL)
	{
		delete m_msgQueue;
		m_msgQueue = NULL;
	}
}

ULONG CMessageControl::Process()
{
	CMessage *tMsg = new CMessage;
	char *tSipStr = new char[BUFFER_SIZE];
	CRegStateMac *reg;
	while (!m_stopFlag)
	{	
		if (m_msgQueue->IsEmpty())
		{
			Sleep(100);
			continue;	
		}
		memset(tMsg,0,sizeof(CMessage));
		tMsg = m_msgQueue->GetMsg();
		switch(tMsg->m_msgType)
		{
		case REGISTER_MSG:
 			memset(tSipStr,'\0',BUFFER_SIZE);
			tSipStr = (char*)tMsg->m_lparam;
			::PostThreadMessage(g_stateMacManager.GetThreadID(),REGISTER_SYS,
				(WPARAM)tSipStr,NULL);
			break;
		case INVITE_MSG:
			memset(tSipStr,'\0',BUFFER_SIZE);
			tSipStr = (char*)tMsg->m_lparam;
			reg = new CRegStateMac;
			reg->InviteState(tSipStr);
// 			::PostThreadMessage(g_stateMacManager.GetThreadID(),REGISTER_SYS,
// 				(WPARAM)tSipStr,NULL);
			delete reg;
			break;
		default:
		    break;
		}
		Sleep(100);
	}
	delete tMsg;
	delete []tSipStr;
	return 0;
}

CMsgQueue* CMessageControl::GetMessageQueue()
{
	return m_msgQueue;
}