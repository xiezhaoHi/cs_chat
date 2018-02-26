// StateMacManager.cpp: implementation of the CStateMacManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "StateMacManager.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStateMacManager::CStateMacManager()
{

}

CStateMacManager::~CStateMacManager()
{
	if(NULL != m_pRegState) 
		delete m_pRegState;
	if(NULL != m_callOut) 
		delete m_callOut;
	if(NULL != m_callIn) 
		delete m_callIn;
}

bool CStateMacManager::CreateStateMac(CStateBase *pState)
{
 	return true;
}

bool CStateMacManager::ReleaseStateMac(string callID)
{
	return false;
}

bool CStateMacManager::FindStateMac(string callID)
{
	return true;
}

CStateBase* CStateMacManager::GetStateMac(string callID)
{
	return NULL;
}

ULONG CStateMacManager::Process()
{
	MSG msg = {0};
	while (::GetMessage(&msg, 0, 0, 0))
	{
		switch(msg.message)
		{
		case RegistMsg:
			if (m_pRegState == NULL)
			{
				m_pRegState = new CRegState;
			}
			m_pRegState->Run((void *)msg.wParam);
			break;
		case MSG200_SYS:
			
			if (m_callIn != NULL)
			{
				m_callIn->AtEndState((void *)msg.wParam);
				break;
			}
			if (m_callOut != NULL)
			{
				m_callOut->OnRecv200Msg((void *)msg.wParam);
				break;
			}

			if (m_pRegState != NULL)
			{
				m_pRegState->SetRegState();
				break;
			}
			//////////////////////////////////////////////////////////////////////////
			//主叫状态 
			//////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////
			//被叫状态
			//////////////////////////////////////////////////////////////////////////
			break;
		case MSG400_SYS:
			break;

		case MSG180_SYS:
			if (m_callOut == NULL)
			{
				break;
			}
			m_callOut->OnRecv180_100Msg((void *)msg.wParam);
			break;
		case MSG302_SYS:
			if (m_callOut == NULL)
			{
				break;
			}
			m_callOut->OnRecv302Msg((void *)msg.wParam);
			break;
		case STATECHANGE:
			
			if ((StateMac)msg.wParam == REGISER)
			{
				if (m_pRegState == NULL)
				{
					break;
				}
				m_pRegState->Run((void *)msg.wParam);
			}
			else if((StateMac)msg.wParam == CALLOUT)
			{
				if (m_callOut == NULL)
				{
					break;
				}
				m_callOut->Run((void *)msg.wParam);
			}
			else if ((StateMac)msg.wParam == CALLIN)
			{
				if (m_callIn == NULL)
				{
					break;
				}
				m_callIn->Run((void *)msg.wParam);
			}
			break;
		case KillMe:
			if ((StateMac)msg.wParam == REGISER)
			{
				if (m_pRegState == NULL)
				{
					break;
				}
				delete m_pRegState;
				m_pRegState = NULL;
			}
			else if((StateMac)msg.wParam == CALLOUT)
			{
				if (m_callOut == NULL)
				{
					break;
				}
				delete m_callOut;
				m_callOut = NULL;
			}
			else if ((StateMac)msg.wParam == CALLIN)
			{
				if (m_callIn == NULL)
				{
					break;
				}
				delete m_callIn;
				m_callIn = NULL;
			}
			break;
		case INVITE_SRV:
			if (m_callOut != NULL)
			{
				delete m_callOut;
				m_callOut = NULL;
			}
			m_callOut = new CCallOutState;
			m_callOut->Run((void *)msg.wParam);
			break;
		case CALLIN_SYS:
			
			if (m_callIn != NULL)
			{
				break;
			}
			m_callIn = new CCallInState;
			m_callIn->Run((void *)msg.wParam);
			break;
		case CANCEL_SYS:
			if (m_callOut != NULL)
			{
				if (m_callOut->GetState() == CCallOutState::Connecting)
				{
					m_callOut->SetState(CCallOutState::Bye);
				}
				else if (m_callOut->GetState()==CCallOutState::Wait180 ||
					m_callOut->GetState()==CCallOutState::Wait200)
				{
					m_callOut->SetState(CCallOutState::Cancel);
				}
				m_callOut->Run(NULL);
			}
// 			else if (m_callIn != NULL && m_callIn->GetState() == CCallInState::Ringing)
// 			{
// 				m_callIn->SetState(CCallInState::Cancel);
// 				m_callIn->Run(NULL);
// 			}
			break;
		case LISTEN_SYS:
			AfxMessageBox("LSN");
			if (m_callIn != NULL)
			{
				m_callIn->SetState(CCallInState::WaitACK);
				break;
			}
			break;
		case MSGACK_SYS:
			if(m_callIn != NULL){
				m_callIn->OnRecvAck((void *)msg.wParam);
			}
			break;
		case CANCEL_RCV:
			if (m_callIn != NULL)
			{
				m_callIn->SetState(CCallInState::RecvBye);
				m_callIn->Run((void *)msg.wParam);
			}
			break;
		case BYE_RCV:
			if (m_callOut != NULL)
			{
				m_callOut->OnRecvByeMsg((void *)msg.wParam);
			}
			else if (m_callIn != NULL)
			{
				m_callIn->SetState(CCallInState::RecvBye);
				m_callIn->Run((void *)msg.wParam);
			}

			break;
		case CMD487_RCV:
			if (m_callOut != NULL)
			{
				::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)"对方拒绝连接",NULL);
				m_callOut->SetState(CCallOutState::End);
				m_callOut->Run(NULL);
			}
			break;
		default:
			break;
		}
		if (m_threadState == false)
		{
			break;
		}
		Sleep(100);
	}
	return 0L;
}

CCallInState* CStateMacManager::GetCallInState()
{
	return m_callIn;
}