// StateMacManager.cpp: implementation of the CStateMacManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"
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

}

bool CStateMacManager::CreateRegStateMac(string callID)
{
	if (FindRegStateMac(callID))
	{
		return false;
	}
	
	CRegStateMac* pTmp = new CRegStateMac();
	m_RegStateMacMap.insert(make_pair(callID, pTmp));
	return true;
}

bool CStateMacManager::EraseRegStateMac(string callID)
{
	if (FindRegStateMac(callID))
	{
		m_RegStateMacMap.erase(callID);
		return true;
	}
	return false;
}

bool CStateMacManager::FindRegStateMac(string callID)
{
	RegStateMacMap::iterator it = m_RegStateMacMap.find(callID);
	return (it != m_RegStateMacMap.end());
}

CRegStateMac* CStateMacManager::GetRegStateMac(string callID)
{
	RegStateMacMap::iterator it = m_RegStateMacMap.find(callID);
	if (it != m_RegStateMacMap.end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

ULONG CStateMacManager::Process()
{
	MSG msg = {0};
	char *tMsgStr /*= new char[BUFSIZ]*/;
//	memset(tMsgStr,'\0',BUFSIZ);
 	char callID[BUFSIZ] = {0};
//	osip_call_id_t *callIDInfo;
 	CRegStateMac* it;
	user_list::iterator user_it = g_userList.begin();
	while (::GetMessage(&msg, 0, 0, 0))
	{
		switch(msg.message)
		{	
		case REGISTER_SYS:
 			tMsgStr = (char *)msg.wParam;
			if (strncmp(tMsgStr,"REGISTER",6)==0)
			{
				osip_message_t *tOsipMsg;
				parser_init();
				osip_message_init(&tOsipMsg);
				osip_message_parse(tOsipMsg,tMsgStr,strlen(tMsgStr));
				strcpy(callID,osip_call_id_get_number(tOsipMsg->call_id));
				if (!FindRegStateMac(callID))
				{
					CreateRegStateMac(callID);
				}
				it = GetRegStateMac(callID);
				if (it != NULL)
				{
					it->Run((void*)tMsgStr);
				}
			}
			else if (strncmp(tMsgStr,"INVITE",6)==0)
			{
				osip_message_t *tOsipMsg;
				parser_init();
				osip_message_init(&tOsipMsg);
				osip_message_parse(tOsipMsg,tMsgStr,strlen(tMsgStr));
				strcpy(callID,osip_call_id_get_number(tOsipMsg->call_id));
				if (!FindRegStateMac(callID))
				{
					CreateRegStateMac(callID);
				}
				it = GetRegStateMac(callID);
				if (it != NULL)
				{
					it->InviteState((void*)tMsgStr);
				}
			}
	
			break;
		case STATECHANGE:
			tMsgStr = (char *)msg.wParam;
  			if (FindRegStateMac(callID))
			{
				GetRegStateMac(callID)->Run((void*)tMsgStr);
			}
			break;
		case KILLME:
			tMsgStr = (char *)msg.wParam;
			if (FindRegStateMac(tMsgStr))
			{
				if(true ==EraseRegStateMac(tMsgStr));
			}
			user_it = g_userList.begin();
			while (user_it != g_userList.end())
			{
				if ( strncmp(tMsgStr,user_it->call_id,32) == 0 )
				{
					g_userList.erase(user_it);
					::PostMessage(g_hwnd,WM_UPDATEUSERLIST,NULL,NULL);
					break;
				}
				user_it++;
			}
			break;
		default:
			break;
		}
		Sleep(100);
	}
	return 0L;
}
