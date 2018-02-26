// RegState.cpp: implementation of the CRegState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "RegState.h"

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
 	::PostThreadMessage(g_stateManager.GetThreadID(),STATECHANGE,(WPARAM)REGISER,NULL);
	return 0;
}

CRegState::CRegState()
{
	m_state = Begin;
	m_count = 0;
	m_timerID = 0;
	m_isRegMsg = true;
	m_sipMsg = new CSipMessage;
}

CRegState::~CRegState()
{
	delete m_sipMsg;
	m_sipMsg = NULL;
}

LONG CRegState::Run(void *vParam /* = NULL */)
{
	switch(m_state)
	{
	case Begin:
		AtBeginState(vParam);
		break;
	case KeepLift:
		AtKeepLiftState(vParam);
	    break;
	case Wait200:
		AtWait200State(vParam);
		break;
	case End:
		AtEndState(vParam);
		break;
	default:
	    break;
	}
	return 0L;
}

LONG CRegState::AtBeginState(void *vParam)
{
	user_info *pUserInfo = (user_info*)vParam;
	char *pSendMsg = new char[BUFSIZ];
	char *pBody = new char[BUFSIZ];
	memset(pBody,'\0',BUFSIZ);
	unsigned int len = BUFSIZ;
	
    char ip[20] = {0};
	strncpy(m_ip,g_srvIP,20);
	m_port = g_srvPort;
    unsigned int port = g_clientSock->GetSocketStream()->GetSockPort();
    g_clientSock->GetSocketStream()->GetLocalIp(ip,20);
	int iplen = strlen(ip);
	m_sipMsg->SetLocalAdd(ip,strlen(ip),port);
 	m_sipMsg->SetRemoteAdd(m_ip,20,m_port);
	m_sipMsg->SetUserInfo(pUserInfo->name,strlen(pUserInfo->name)+1,
		pUserInfo->pwd,strlen(pUserInfo->pwd));
	sprintf(pBody,"user=%s\r\npwd=%s\r\n",pUserInfo->name,pUserInfo->pwd);
	m_sipMsg->NewCallIDTag();
	m_sipMsg->SetMsgBody(pBody,strlen(pBody)+1);
	m_sipMsg->GetSipMessage(pSendMsg,&len,Regist);

	unsigned int ret = 
		g_clientSock->GetSocketStream()->
		Write(pSendMsg,strlen(pSendMsg)+1,m_ip,m_port,3);
	if (ret != strlen(pSendMsg)+1)
	{
		ASSERT(0);
	}
	m_sendReg = pSendMsg;
 	m_timerID = g_timer.SetTimer(3,RegTimeOutProc,(void*)pSendMsg);	
	m_state = Wait200;
	return 0L;
}

LONG CRegState::AtWait200State(void *vParam)
{
	m_count++;
	if (m_count > 3)
	{
		m_state = End;
		::PostThreadMessage(g_stateManager.GetThreadID(),STATECHANGE,(WPARAM)REGISER,NULL);
		return 0;
	}
    char *pSendMsg = m_sendReg;
  	unsigned int ret = g_clientSock->GetSocketStream()->
   		Write(pSendMsg,strlen(pSendMsg)+1,m_ip,m_port,3);
   	if (ret != strlen(pSendMsg)+1)
 	{
   		ASSERT(0);
 	}
 	m_timerID = g_timer.SetTimer(3,RegTimeOutProc,(void*)pSendMsg);
 	return 0;
}

////////////////////////////////////////////////////////////////////////////
//改变状态m_state
//用于收到200消息
//如果m_isRegMsg是true设置KeepLift
//如果m_isRegMsg是false设置END
void CRegState::SetRegState()
{
	if (m_isRegMsg == true)
	{
		m_state = KeepLift;
	}
	else if (m_isRegMsg == false)
	{
		m_state = End;
	}
	::PostThreadMessage(g_stateManager.GetThreadID(),STATECHANGE,(WPARAM)REGISER,NULL);
}


LONG CRegState::AtKeepLiftState(void *vParam)
{
    char *pSendMsg = m_sendReg;
	g_timer.Erase(m_timerID);
	m_count = 0;
  	unsigned int ret = g_clientSock->GetSocketStream()->
   		Write(pSendMsg,strlen(pSendMsg)+1,m_ip,m_port,3);
   	if (ret != strlen(pSendMsg)+1)
 	{
   		ASSERT(0);
 	}
 	m_timerID = g_timer.SetTimer(KEEPLIFE,RegTimeOutProc,(void*)pSendMsg);
	m_state = Wait200;
	return 0L;
}

LONG CRegState::AtEndState(void *vParam)
{
	::PostThreadMessage(g_stateManager.GetThreadID(),KillMe,(WPARAM)REGISER,NULL);
	return 0L;
}

LONG CRegState::UnRegister()
{
	char *pSendMsg = new char[BUFSIZ];
	unsigned int len = BUFSIZ;
	m_sipMsg->GetSipMessage(pSendMsg,&len,Unregist);
	unsigned int ret = 
		g_clientSock->GetSocketStream()->
		Write(pSendMsg,strlen(pSendMsg)+1,m_ip,m_port,3);
	if (ret != strlen(pSendMsg)+1)
	{
		ASSERT(0);
	}
	m_sendReg = pSendMsg;
 	m_timerID = g_timer.SetTimer(3,RegTimeOutProc,(void*)pSendMsg);
	m_state = Wait200;
	return 0L;
}

//////////////////////////////////////////////////////////////////////////
//未完成 osip_message_set_exprise()
//////////////////////////////////////////////////////////////////////////
//发送反注册消息，把m_isRegMsg设置true，把状态m_state设置为KeepLift
//   
