// CallOutState.cpp: implementation of the CCallOutState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "CallOutState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long InviteTimeOutProc(void *vParam)
{
	CCallOutState::OnStateChange();
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCallOutState::CCallOutState()
{
//////////////////////////////////////////////////////////////////////////
//初始化数据
//////////////////////////////////////////////////////////////////////////
	m_count = 0;
	m_state = Begin;
	m_sipMsg = new CSipMessage;
	m_timerID = 0;
	osip_message_init(&m_sipMsg_t);
	m_msg200Flag = FromClient;
}

CCallOutState::~CCallOutState()
{
//////////////////////////////////////////////////////////////////////////
//释放空间
//////////////////////////////////////////////////////////////////////////
	if (m_sipMsg != NULL)
	{
		delete m_sipMsg;
	}
	osip_message_free(m_sipMsg_t);
}

LONG CCallOutState::Run(void *vParam /* = NULL */)
{
	switch(m_state)
	{
	case Begin:
		AtBeginState(vParam);
		break;
	case Wait302:
		AtWait302State(vParam);
	    break;
	case Wait180:
		AtWait180State(vParam);
		break;
	case Wait200:
		AtWait200State(vParam);
		break;
	case Cancel:
		AtCancelState(vParam);
		break;
	case Bye:
		AtByeState(vParam);
		break;
	case End:
		AtEndState(vParam);
		break;
	default:
	    break;
	}
	return 0L;	
}

int CCallOutState::StrToSipMsgT(char *tMsg)
{
	parser_init();
	return osip_message_parse(m_sipMsg_t,tMsg,strlen(tMsg));
}

LONG CCallOutState::AtBeginState(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//1.收到界面呼叫消息
//
//*****处理过程*****
//1.初始化INVITE发送数据
//2.发送数据到服务器
//3.保存INVITE数据
//4.改变状态为WAIT302
//////////////////////////////////////////////////////////////////////////
	char *pSendMsg = new char[BUFSIZ];
	char *m_remoteName = new char[30];
	memset(m_remoteName,'\0',30);
	m_remoteName = (char *)vParam;
	unsigned int len = BUFSIZ;
	char ip[20] = {0};
	strncpy(m_ip,g_srvIP,20);
	m_port = g_srvPort;
	g_clientSock->GetSocketStream()->GetLocalIp(ip,20);
	m_sipMsg->SetLocalAdd(ip,strlen(ip),g_clientSock->GetSocketStream()->GetSockPort());
 	m_sipMsg->SetRemoteAdd(m_ip,20,m_port);
  	m_sipMsg->SetUserInfo(g_userInfo->name,strlen(g_userInfo->name)+1,
  		g_userInfo->pwd,strlen(g_userInfo->pwd));
  	m_sipMsg->NewCallIDTag();
	m_sipMsg->SetRemoteName(m_remoteName,strlen(m_remoteName)+1);
	m_sipMsg->GetSipMessage(pSendMsg,&len,Invoid);
  	unsigned int ret = 
  		g_clientSock->GetSocketStream()->
  		Write(pSendMsg,strlen(pSendMsg)+1,m_ip,m_port,3);
  	if (ret != strlen(pSendMsg)+1)
	{
		ASSERT(0);
	}
  	m_sendReg = pSendMsg;
	strncpy(m_callID,m_sipMsg->GetCallId(),33);
	m_callID[32] = '\0';
	m_state = Wait302;
	m_timerID = g_timer.SetTimer(3,InviteTimeOutProc,(void*)pSendMsg);

	return 0L;
}

LONG CCallOutState::AtWait302State(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//1.发送INVITE
//
//*****处理过程*****
//1.插入3秒定时器
//2.保存定时器ID
//3.设置COUNT++
//////////////////////////////////////////////////////////////////////////
	m_count++;
	if (m_count > 3)
	{
		m_state = End;
		CCallOutState::OnStateChange();
		return 0;
	}
    char *pSendMsg = m_sendReg;
  	unsigned int ret = g_clientSock->GetSocketStream()->
   		Write(pSendMsg,strlen(pSendMsg)+1,m_ip,m_port,3);
   	if (ret != strlen(pSendMsg)+1)
 	{
   		ASSERT(0);
 	}
	g_timer.Erase(m_timerID);
 	m_timerID = g_timer.SetTimer(3,InviteTimeOutProc,(void*)pSendMsg);
	return 0L;
}

LONG CCallOutState::AtWait180State(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//1.收到服务器200包
//2.返回ACK给服务器
//3.发送INVITE给客户端
//
//*****处理过程*****
//1.插入3秒定时器
//2.保存定时器ID
//3.设置COUNT++
//////////////////////////////////////////////////////////////////////////
	m_count++;
	if (m_count > 3)
	{
		m_state = End;
		CCallOutState::OnStateChange();
		return 0;
	}
    char *pSendMsg = m_sendReg;
  	unsigned int ret = 	
		g_clientSock->GetSockStream()->Write(m_sendReg,strlen(m_sendReg),m_ip,m_port,3);
 	m_timerID = g_timer.SetTimer(3,InviteTimeOutProc,(void*)pSendMsg);
	return 0L;
}

LONG CCallOutState::AtWait200State(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//.发送给服务器INVITE
//.发送给客户端INVITE，并且收到180
//.发送CANCEL
//.发送BYE
//
//*****处理过程*****
//1.插入3秒定时器
//2.保存定时器ID
//3.设置COUNT++
//////////////////////////////////////////////////////////////////////////
	m_count++;
	if (m_count > 3)
	{
		m_state = End;
		CCallOutState::OnStateChange();
		return 0;
	}
    char *pSendMsg = m_sendReg;
  	unsigned int ret = 	
		g_clientSock->GetSockStream()->Write(m_sendReg,strlen(m_sendReg),m_ip,m_port,3);
 	g_timer.Erase(m_timerID);
 	m_timerID = g_timer.SetTimer(30,InviteTimeOutProc,(void*)pSendMsg);
	return 0L;
}

LONG CCallOutState::AtCancelState(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//作用:主动取消连接，在没有收到200前使用
//
//*****触发条件*****
//1.界面发送取消内部消息
//2.收到180
//
//*****处理过程*****
//1.初始化CANCLE发送数据
//2.发送给客户端CANCLE
//3.改变状态为WAIT200
//4.设置m_msg200Flag=FromCancel
//////////////////////////////////////////////////////////////////////////
	char *pSendMsg = new char[BUFSIZ];
	char *pBody = new char[BUFSIZ];
//	m_remoteName = "";
	memset(pBody,'\0',BUFSIZ);
	unsigned int len = BUFSIZ;
	char ip[20] = {0};
	g_clientSock->GetSocketStream()->GetLocalIp(ip,20);
	m_sipMsg->SetLocalAdd(ip,strlen(ip),g_clientSock->GetSocketStream()->GetSockPort());

 	m_sipMsg->SetRemoteAdd(g_srvIP,20,g_srvPort);
  	m_sipMsg->SetUserInfo(g_userInfo->name,strlen(g_userInfo->name)+1,
  		g_userInfo->pwd,strlen(g_userInfo->pwd));
	m_sipMsg->SetCallID(m_callID);
//	m_sipMsg->SetRemoteName(m_remoteName,strlen(m_remoteName)+1);
  	m_sipMsg->GetSipMessage(pSendMsg,&len,CancelSip);
  	unsigned int ret = 	
		g_clientSock->GetSockStream()->Write(m_sendReg,strlen(m_sendReg),m_ip,m_port,3);
  	m_sendReg = pSendMsg;
	m_state = End;
	CCallOutState::OnStateChange();
	m_msg200Flag=FromCancel;
	return 0L;
}

LONG CCallOutState::AtByeState(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//1.界面发送取消内部消息
//2.收到200
//
//*****处理过程*****
//1.初始化BYE发送数据
//2.发送给客户端BYE
//3.改变状态为WAIT200
//4.设置m_msg200Flag=FromBye
//////////////////////////////////////////////////////////////////////////
	char *pSendMsg = new char[BUFSIZ];
	char *pBody = new char[BUFSIZ];
//	m_remoteName = (char *)vParam;
	memset(pBody,'\0',BUFSIZ);
	unsigned int len = BUFSIZ;
	char ip[20] = {0};
	g_clientSock->GetSocketStream()->GetLocalIp(ip,20);
	m_sipMsg->SetLocalAdd(ip,strlen(ip),g_clientSock->GetSocketStream()->GetSockPort());

 	m_sipMsg->SetRemoteAdd(g_srvIP,20,g_srvPort);
  	m_sipMsg->SetUserInfo(g_userInfo->name,strlen(g_userInfo->name)+1,
  		g_userInfo->pwd,strlen(g_userInfo->pwd));
	m_sipMsg->SetCallID(m_callID);
//	m_sipMsg->SetRemoteName(m_remoteName,strlen(m_remoteName)+1);
  	m_sipMsg->GetSipMessage(pSendMsg,&len,ByeSip);
  	unsigned int ret = 	g_clientSock->GetSockStream()->Write(m_sendReg,strlen(m_sendReg),m_ip,m_port,3);
  	m_sendReg = pSendMsg;
	m_state = End;
	CCallOutState::OnStateChange();
	m_msg200Flag=FromBye;
	return 0L;
}

LONG CCallOutState::AtEndState(void *vparam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//.连接超时
//.CANCEL后收到200
//.BYE后收到200
//
//*****处理过程*****
//1.发送KILLME消息给状态机管理线程，消息包含CALL-ID
//////////////////////////////////////////////////////////////////////////
	::PostThreadMessage(g_stateManager.GetThreadID(),KillMe,(WPARAM)CALLOUT,NULL);
	g_audioCtrl->Stop();
	return 0L;
}

LONG CCallOutState::OnRecv200Msg(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//.收到200
//
//*****处理过程*****
//1.判断m_msg200Flag，调用相应的处理函数（FromClient,FromCancel,FromBye）
	m_count = 0;
	switch(m_msg200Flag)
	{
	case FromClient:
		SendAck(vParam);
		break;
	case FromCancel:
	case FromBye:
		m_state = End;
		CCallOutState::OnStateChange();
	    break;
	default:
	    break;
	}
	return 0L;
}

LONG CCallOutState::OnRecv180_100Msg(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//.收到180 100消息
//
//*****处理过程*****
//1.收到100，删除原有定时器，继续等待180
//2.收到180，删除原因定时器，改变状态为，WAIT200
//3.发送StateChange给状态机管理线程
//////////////////////////////////////////////////////////////////////////
	char *tMsg = (char*)vParam;
	try
	{
		StrToSipMsgT(tMsg);
	}
	catch (...)
	{
		AfxMessageBox("Error packet");	
	}
	char *pSendMsg = m_sendReg;
	if (strncmp(tMsg,"SIP/2.0 100",11)==0)
	{
		m_count++;
		if (m_count > 3)
		{
			m_state = End;
			CCallOutState::OnStateChange();
			return 0;
		}
		
		unsigned int ret = g_clientSock->GetSocketStream()->
			Write(pSendMsg,strlen(pSendMsg)+1,g_srvIP,g_srvPort,3);
		g_timer.Erase(m_timerID);
		m_timerID = g_timer.SetTimer(3,InviteTimeOutProc,(void*)pSendMsg);
	}
	else if (strncmp(tMsg,"SIP/2.0 180",11)==0)
	{
		g_timer.Erase(m_timerID);
		m_state = Wait200;
		m_timerID = g_timer.SetTimer(60,InviteTimeOutProc,(void*)pSendMsg);
		int tcount = 0;
		char msg[BUFSIZ] = {0};
		sprintf(msg,"等待接听",m_sipMsg_t->from->url->username);
		::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)msg,NULL);
	}
	
	return 0L;
}

LONG CCallOutState::OnRecv302Msg(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//.收到302消息
//
//*****处理过程*****
//1.给服务器发送ACK
//2.解析客户端地址
//3.给客户端地址发送INVITE
//4.将m_state设置为WAIT180
//////////////////////////////////////////////////////////////////////////
	char *tMsg = (char*)vParam;
	try
	{
		StrToSipMsgT(tMsg);
	}
	catch (...)
	{
		AfxMessageBox("Error packet");	
	}
	char *pSendMsg = new char[BUFSIZ];
	char *pBody = new char[BUFSIZ];
	m_remoteName = (char *)vParam;
	memset(pBody,'\0',BUFSIZ);
	unsigned int len = BUFSIZ;
	char ip[20] = {0};
	g_clientSock->GetSocketStream()->GetLocalIp(ip,20);
	m_sipMsg->SetLocalAdd(ip,strlen(ip),g_clientSock->GetSocketStream()->GetSockPort());

 	m_sipMsg->SetRemoteAdd(g_srvIP,20,g_srvPort);
  	m_sipMsg->SetUserInfo(g_userInfo->name,strlen(g_userInfo->name)+1,
  		g_userInfo->pwd,strlen(g_userInfo->pwd));
// 	sprintf(pBody,"user=%s\r\npwd=%s\r\n",pUserInfo->name,pUserInfo->pwd);
	m_sipMsg->SetCallID(m_callID);
//  m_sipMsg->SetMsgBody(pBody,strlen(pBody)+1);
	//////////////////////////////////////////////////////////////////////////
	// 设置包体（未）
	//////////////////////////////////////////////////////////////////////////
	m_sipMsg->SetRemoteName(m_remoteName,strlen(m_remoteName)+1);
  	m_sipMsg->GetSipMessage(pSendMsg,&len,AckSip);
  	unsigned int ret = 
  		g_clientSock->GetSocketStream()->
  		Write(pSendMsg,strlen(pSendMsg)+1,m_ip,m_port,3);
//	g_timer.Erase(m_timerID);
//   	if (ret != strlen(pSendMsg)+1)
// 	{
// 		ASSERT(0);
// 	}
  	m_sendReg = pSendMsg;

	//2.解析客户端地址
	strncpy(m_ip,m_sipMsg_t->to->url->host,20);
	m_port = atoi(m_sipMsg_t->to->url->port);
	int callid_len = atoi(m_callID);
	memset(m_sendReg,'\0',BUFSIZ);
	unsigned int send_msg_len = BUFSIZ;
	m_sipMsg->SetLocalAdd(m_sipMsg_t->from->url->host,
					strlen(m_sipMsg_t->from->url->host),atoi(m_sipMsg_t->from->url->port));
	m_sipMsg->SetRemoteAdd(m_sipMsg_t->to->url->host,
				   strlen(m_sipMsg_t->to->url->host),atoi(m_sipMsg_t->to->url->port));
	m_sipMsg->SetRemoteName(m_sipMsg_t->to->url->username,
					strlen(m_sipMsg_t->to->url->username));
	m_sipMsg->SetCallID(m_callID);
	m_sipMsg->SetAudioBody(true);
	m_sipMsg->GetSipMessage(m_sendReg,&send_msg_len,Invoid);
	g_clientSock->GetSockStream()->Write(m_sendReg,strlen(m_sendReg),m_ip,m_port,3);
	m_state = Wait180;
	 	m_timerID = g_timer.SetTimer(3,InviteTimeOutProc,(void*)pSendMsg);
	return 0L;
}

LONG CCallOutState::OnRecvByeMsg(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//作用:收到对方的BYE消息后的状态机处理
//*****触发条件*****
//.收到BYE消息
//
//*****处理过程*****
//1.通知界面
//2.返回200
//4.将m_state设置为End
//////////////////////////////////////////////////////////////////////////
	AfxMessageBox("对方已经挂断");

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
	memset(m_sendReg,'\0',BUFSIZ);
	unsigned int send_msg_len = BUFSIZ;
	m_sipMsg->SetRemoteAdd(m_sipMsg_t->from->url->host,
					strlen(m_sipMsg_t->from->url->host),atoi(m_sipMsg_t->from->url->port));
	m_sipMsg->SetLocalAdd(m_sipMsg_t->to->url->host,
				   strlen(m_sipMsg_t->to->url->host),atoi(m_sipMsg_t->to->url->host));
	m_sipMsg->SetRemoteName(m_sipMsg_t->from->url->username,
					strlen(m_sipMsg_t->from->url->username));
	m_sipMsg->SetCallID(m_callID);/**/
	m_sipMsg->GetSipMessage(m_sendReg,&send_msg_len,Regist200);
	g_clientSock->GetSockStream()->Write(m_sendReg,strlen(m_sendReg),m_ip,m_port,3);
	m_state = End;
	CCallOutState::OnStateChange();
	return 0L;
}

void CCallOutState::OnStateChange()
{
	::PostThreadMessage(g_stateManager.GetThreadID(),STATECHANGE,(WPARAM)CALLOUT,NULL);
}

LONG CCallOutState::SendAck(void *vParam)
{	
	char *tMsg = (char*)vParam;
	parser_init();
	osip_message_t *tosipMsg;
	osip_message_init(&tosipMsg);
	osip_message_parse(tosipMsg,tMsg,strlen(tMsg));
	char *ip;
	char *port;
 	sdp_message_t *sdp;
 	sdp_message_init(&sdp);
	osip_body_t *osipBody;
	unsigned int ret = osip_message_get_body(tosipMsg,0,&osipBody);
 	sdp_message_parse(sdp,osipBody->body);
	ip = sdp_message_o_addr_get(sdp);
	port = sdp_message_m_port_get(sdp,0);
	strncpy(m_callID,osip_call_id_get_number(m_sipMsg_t->call_id),33);
	int len = atoi(m_callID);
	memset(m_sendReg,'\0',BUFSIZ);
	unsigned int send_msg_len = BUFSIZ;
// 	g_audioCtrl->m_waveIn->SetRemoteAddr(ip,atoi(port));
// 	g_audioCtrl->m_waveIn->StartRec();
// 	g_audioCtrl->m_waveOut->StartPlay();
// 	g_audioCtrl->m_audioSock->Start();

	g_audioCtrl->Start(ip,port);
	m_sipMsg->GetSipMessage(m_sendReg,&send_msg_len,AckSip);
	g_clientSock->GetSockStream()->Write(m_sendReg,strlen(m_sendReg),m_ip,m_port,3);
	::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)"通话建立",NULL);
	::PostMessage(m_ui_hwnd,CONNECT_TIME,NULL,NULL);
	m_state = Connecting;
	return 0L;
}


