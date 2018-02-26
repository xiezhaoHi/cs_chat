// RegStateMac.cpp: implementation of the CRegStateMac class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"
#include "RegStateMac.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

long RegTimeOutProc(void *vParam)
{
	
	::PostThreadMessage(g_stateMacManager.GetThreadID(),KILLME,(WPARAM)vParam,NULL);
	return 0;
}

CRegStateMac::CRegStateMac():m_count(0)
{
	m_sipMsg = new CSipMessage;
	if (NULL == m_sipMsg)
	{
		ASSERT(0);
	}
	m_count = 0;
	m_timerID = 0;
	m_state = Begin;
	osip_message_init(&m_sipMsg_t);
}

CRegStateMac::~CRegStateMac()
{
	if (NULL != m_sipMsg)
	{
		delete m_sipMsg;
	}
	osip_message_free(m_sipMsg_t);
}

LONG CRegStateMac::Run(void *vParam /* = NULL */)
{
	switch(m_state)
	{
	case Begin:
		AtBeginState(vParam);
		break;
	case Registed:
		AtRegistedState(vParam);
	    break;
	case End:
		AtEndState(vParam);
	default:
	    break;
	}
	return 0L;
}

LONG CRegStateMac::AtBeginState(void *vParam)
{
	
	char *tMsg = (char*)vParam;
	try
	{
		StrToSipMsgT(tMsg);
	}
	catch (...)
	{
		AfxMessageBox("Error packet");	
	}
	strncpy(m_callID,osip_call_id_get_number(m_sipMsg_t->call_id),33);
	int len = atoi(m_callID);
	if (false == CheckUserInfo(tMsg))
	{
		//////////////////////////////////////////////////////////////////////////
		//验证用户名密码
		m_state = End;
 		::PostThreadMessage(g_stateMacManager.GetThreadID(),
			STATECHANGE,(WPARAM)m_callID,(LPARAM)len);
		return m_state;
	}
	memset(m_sendMsg,'\0',BUFSIZ);
	unsigned int send_msg_len = BUFSIZ;
	m_sipMsg->SetRemoteAdd(m_sipMsg_t->from->url->host,
					strlen(m_sipMsg_t->from->url->host),atoi(m_sipMsg_t->from->url->port));
	m_sipMsg->SetLocalAdd(m_sipMsg_t->to->url->host,
				   strlen(m_sipMsg_t->to->url->host),atoi(m_sipMsg_t->to->url->host));
	m_sipMsg->SetRemoteName(m_sipMsg_t->from->url->username,
					strlen(m_sipMsg_t->from->url->username));
	m_sipMsg->SetCallID(m_callID);
	strncpy(m_ip,m_sipMsg_t->from->url->host,20);
	m_port = atoi(m_sipMsg_t->from->url->port);
	m_sipMsg->GetSipMessage(m_sendMsg,&send_msg_len,Regist200);
	g_serverSock->GetSockStream()->Write(m_sendMsg,strlen(m_sendMsg),
		m_ip,m_port,3);
	osip_header_t *expires = NULL;
	unsigned int ret = osip_message_get_expires(m_sipMsg_t, 0, &expires);

	if (/*ret != -1*/1)
	{
		if (strcmp(expires->hvalue, "1") == 0)
		{
			m_state = Registed;
			user_info user;
			strncpy(user.username,m_sipMsg_t->from->url->username,20);
			strncpy(user.ip,m_sipMsg_t->from->url->host,18);
			strncpy(user.call_id,m_callID,40);
			user.port = atoi(m_sipMsg_t->from->url->port);
			g_userList.push_back(user);
			::PostMessage(g_hwnd,WM_UPDATEUSERLIST,NULL,NULL);
		}
		else if (strcmp(expires->hvalue, "0") == 0)
		{
			m_state = End;
			user_list::iterator it = g_userList.begin();
			while (it != g_userList.end())
			{
				if (strcmp(it->username,m_sipMsg_t->from->url->username)!=0)
				{
					it++;
					continue;
				}
				g_userList.erase(it);
				
				break;
			}
 			::PostMessage(g_hwnd,WM_UPDATEUSERLIST,NULL,NULL);
		}
	}
	::PostThreadMessage(g_stateMacManager.GetThreadID(),STATECHANGE,(WPARAM)m_callID,(LPARAM)len);
	return 0L;
}

int CRegStateMac::StrToSipMsgT(char *tMsg)
{
	parser_init();
	return osip_message_parse(m_sipMsg_t,tMsg,strlen(tMsg));
}

LONG CRegStateMac::AtRegistedState(void *vParam)
{
	g_timer.Erase(m_timerID);
 	m_timerID = g_timer.SetTimer(60,RegTimeOutProc,(void*)m_callID);
	return 0L;
}

LONG CRegStateMac::AtEndState(void *vParam)
{
	::PostThreadMessage(g_stateMacManager.GetThreadID(),
			KILLME,(WPARAM)m_callID,(LPARAM)strlen(m_callID));
	return 0L;
}

bool CRegStateMac::CheckUserInfo(char *pInfo)
{
	return true;
}

LONG CRegStateMac::InviteState(void *vParam /* = NULL */)
{
	char *tMsg = (char*)vParam;
	try
	{
		StrToSipMsgT(tMsg);
	}
	catch (...)
	{
		AfxMessageBox("Error packet");	
	}
	
	int len = atoi(m_callID);
	if (false == CheckUserInfo(tMsg))
	{
		//////////////////////////////////////////////////////////////////////////
		//验证用户名密码
		m_state = End;
 		::PostThreadMessage(g_stateMacManager.GetThreadID(),
			STATECHANGE,(WPARAM)m_callID,(LPARAM)len);
		return m_state;
	}
	memset(m_sendMsg,'\0',BUFSIZ);
	unsigned int send_msg_len = BUFSIZ;

	user_list::iterator it = g_userList.begin();
	user_info to_user;

	while (it != g_userList.end())
	{
		if (strcmp(it->username,m_sipMsg_t->to->url->username)!=0)
		{
			it++;
			continue;
		}
		to_user = *it;
		break;
	}
	strncpy(m_ip,m_sipMsg_t->from->url->host,20);
	m_port = atoi(m_sipMsg_t->from->url->port);
//	AfxMessageBox(it->username);
//	AfxMessageBox(m_sipMsg_t->to->url->username);
	if (it != g_userList.end())
	{
		m_sipMsg->SetRemoteAdd(to_user.ip,strlen(to_user.ip),to_user.port);
		m_sipMsg->SetLocalAdd(m_sipMsg_t->from->url->host,
			strlen(m_sipMsg_t->from->url->host),atoi(m_sipMsg_t->from->url->port));
		m_sipMsg->SetRemoteName(to_user.username,strlen(to_user.username));
		strncpy(m_callID,osip_call_id_get_number(m_sipMsg_t->call_id),33);
		m_sipMsg->SetCallID(m_callID);
		m_sipMsg->GetSipMessage(m_sendMsg,&send_msg_len,CMD302);
	}
 	else
	{
		m_sipMsg->SetRemoteAdd(m_sipMsg_t->from->url->host,
			strlen(m_sipMsg_t->from->url->host),atoi(m_sipMsg_t->from->url->port));
		m_sipMsg->SetLocalAdd(m_sipMsg_t->from->url->host,
			strlen(m_sipMsg_t->from->url->host),atoi(m_sipMsg_t->from->url->port));
		m_sipMsg->SetRemoteName(m_sipMsg_t->from->url->username,
			strlen(m_sipMsg_t->from->url->username));
		strncpy(m_callID,osip_call_id_get_number(m_sipMsg_t->call_id),33);
		m_sipMsg->SetCallID(m_callID);
		m_sipMsg->GetSipMessage(m_sendMsg,&send_msg_len,CMD404);
	}
 	g_serverSock->GetSockStream()->Write(m_sendMsg,strlen(m_sendMsg),
 		/*m_sipMsg_t->from->url->host*/m_ip,m_port/*atoi(m_sipMsg_t->from->url->port)*/,3);
 	m_state = End;
	::PostThreadMessage(g_stateMacManager.GetThreadID(),KILLME,(WPARAM)m_callID,(LPARAM)len);
	return 0L;
}