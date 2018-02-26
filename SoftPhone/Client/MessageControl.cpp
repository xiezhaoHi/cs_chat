// MessageControl.cpp: implementation of the CMessageControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "MessageControl.h"
#include "CallInState.h"

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
	char *hello = new char[BUFFER_SIZE];
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
		case RegistMsg:
			::PostThreadMessage(g_stateManager.GetThreadID(),RegistMsg,
				(WPARAM)tMsg->m_wparam,NULL);
			break;
		case MSG200:
			hello = (char *)tMsg->m_lparam;
			::PostThreadMessage(g_stateManager.GetThreadID(),MSG200_SYS,
				(WPARAM)hello,NULL);
			break;
		case MSG400:
			hello = (char *)tMsg->m_lparam;
			::PostThreadMessage(g_stateManager.GetThreadID(),MSG400_SYS,
				(WPARAM)hello,NULL);
			break;
		case INVITE_SRV:
			::PostThreadMessage(g_stateManager.GetThreadID(),INVITE_SRV,
				(WPARAM)tMsg->m_wparam,NULL);
			break;
		case MSG302:
			hello = (char *)tMsg->m_lparam;
			::PostThreadMessage(g_stateManager.GetThreadID(),MSG302_SYS,
				(WPARAM)hello,NULL);
			break;
		case MSG180:
			hello = (char *)tMsg->m_lparam;
			::PostThreadMessage(g_stateManager.GetThreadID(),MSG180_SYS,
				(WPARAM)hello,NULL);
			break;
		case CALLIN:
			hello = (char *)tMsg->m_lparam;
			::PostThreadMessage(g_stateManager.GetThreadID(),CALLIN_SYS,
				(WPARAM)hello,NULL);
			break;
		case LISTEN_SYS:
			if (NULL != g_stateManager.GetCallInState())
			{
				g_stateManager.GetCallInState()->SetState(CCallInState::WaitACK);
			}
			break;
		case CANCEL_SYS:
			::PostThreadMessage(g_stateManager.GetThreadID(),CANCEL_SYS,NULL,NULL);
			break;
		case CMD487_RCV:
			::PostThreadMessage(g_stateManager.GetThreadID(),CMD487_RCV,NULL,NULL);
			break;
		default:
		    break;
		}
	}
	delete tMsg;
	delete []hello;
	return 0;
}

CMsgQueue* CMessageControl::GetMessageQueue()
{
	return m_msgQueue;
}