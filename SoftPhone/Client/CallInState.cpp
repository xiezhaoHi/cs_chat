// CallInState.cpp: implementation of the CCallInState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "CallInState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

long CallInTimeOutProc(void *vParam)
{
 	::PostThreadMessage(g_stateManager.GetThreadID(),STATECHANGE,(WPARAM)CALLIN,NULL);
	return 0;
}

CCallInState::CCallInState()
{
	m_count = 0;
	m_state = Begin;
	m_sipMsg = new CSipMessage;
	m_timerID = 0;
	osip_message_init(&m_sipMsg_t);
//////////////////////////////////////////////////////////////////////////
//初始化数据
//
//
}

CCallInState::~CCallInState()
{
//////////////////////////////////////////////////////////////////////////
//释放空间
	if (m_sipMsg != NULL)
	{
		delete m_sipMsg;
	}
	osip_message_free(m_sipMsg_t);
}

LONG CCallInState::Run(void *vParam /* = NULL */)
{
	switch(m_state)
	{
	case Begin:
		AtBeginState(vParam);
		break;
	case WaitACK:
		AtWaitACKState(vParam);
	    break;
	case Ringing:
		AtRingingState(vParam);
		break;
	case RecvCancel:
		AtRecvCancelState(vParam);
		break;
	case Bye:
		AtByeState(vParam);
		break;
	case Wait200:
		AtWait200State(vParam);
		break;
	case RecvBye:
		AtRectByeState(vParam);
		break;
	case End:
		AtEndState(vParam);
		break;
	case Cancel:
		AtCancenState(vParam);
		break;
	default:
	    break;
	}
	return 0L;	
}

LONG CCallInState::AtBeginState(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//1.送到网络呼叫消息
//
//*****处理过程*****
//1.发送100
//2.发送180
//3.改变状态为Ringing
	char *tMsg = (char*)vParam;
	try
	{
		StrToSipMsgT(tMsg);
	}
	catch (...)
	{
		AfxMessageBox("Error packet");	
	}

	char *ip;
	char *port;
 	sdp_message_t *sdp;
 	sdp_message_init(&sdp);
	osip_body_t *osipBody;
	osip_message_get_body(m_sipMsg_t,0,&osipBody);
 	sdp_message_parse(sdp,osipBody->body);
	ip = sdp_message_o_addr_get(sdp);
	port = sdp_message_m_port_get(sdp,0);
	
	strncpy(m_ip,m_sipMsg_t->from->url->host,20);
	m_port = atoi(m_sipMsg_t->from->url->port);

	strncpy(m_callID,osip_call_id_get_number(m_sipMsg_t->call_id),33);
	memset(m_sendMsg,'\0',BUFSIZ);
	unsigned int send_msg_len = BUFSIZ;
	m_sipMsg->SetRemoteAdd(m_sipMsg_t->from->url->host,
					strlen(m_sipMsg_t->from->url->host),atoi(m_sipMsg_t->from->url->port));
	m_sipMsg->SetLocalAdd(m_sipMsg_t->to->url->host,
				   strlen(m_sipMsg_t->to->url->host),atoi(m_sipMsg_t->to->url->port));
	m_sipMsg->SetRemoteName(m_sipMsg_t->from->url->username,
					strlen(m_sipMsg_t->from->url->username));
	m_sipMsg->SetCallID(m_callID);
	m_sipMsg->GetSipMessage(m_sendMsg,&send_msg_len,CMD180);
	g_clientSock->GetSockStream()->Write(m_sendMsg,strlen(m_sendMsg),
		m_ip,m_port,3);
	m_state = Ringing;
	::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)"有用户请求连接",NULL);
	::PostThreadMessage(g_stateManager.GetThreadID(),STATECHANGE,(WPARAM)CALLIN,NULL);
// 	g_audioCtrl->m_waveIn->SetRemoteAddr(ip,atoi(port));
// 	g_audioCtrl->m_waveIn->StartRec();
// 	g_audioCtrl->m_waveOut->StartPlay();
// 	g_audioCtrl->m_audioSock->Start();
	g_audioCtrl->Start(ip,port);
	return 0L;
}

LONG CCallInState::AtWaitACKState(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//1.收到界面建立连接消息
//
//*****处理过程*****
//1.发送200
//2.插入定时器3秒，等待ACk消息
//
	m_count++;
	if (m_count > 3)
	{
		m_state = End;
		CCallOutState::OnStateChange();
		return 0;
	}
    char *pSendMsg = m_sendMsg;
	unsigned int ret = 	
		g_clientSock->GetSockStream()->Write(pSendMsg,strlen(pSendMsg),m_ip,m_port,3);
 	m_timerID = g_timer.SetTimer(30,CallInTimeOutProc,(void*)pSendMsg);
	return 0L;
}

LONG CCallInState::AtRingingState(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//1.Ringing
//
//*****处理过程*****
//1.通知UI
//2.等待客户确定
// 	char m_Data[WAVEBUF] = {0};
// 	m_wave_out = new CWaveOut;
// 	m_wave_out->Start();
// 	m_wave_out->SetWaveFormat(WAVE_FORMAT_PCM, 2, 8000, 16, 0);
// 	m_wave_out->SetCodeType();
// 	m_wave_out->SetData(m_Data, WAVEBUF);
// 	CFile tmp;
// 	tmp.Open("E:\\test.wav", CFile::modeRead);
// 	tmp.Read(m_Data, WAVEBUF);
// 	tmp.Close();

	int tcount = 0;
	char msg[BUFSIZ] = {0};
	while(tcount < 60 && m_state == Ringing)
	{
		switch(tcount % 6)
		{
		case 0:
			
			sprintf(msg,"%s来电",m_sipMsg_t->from->url->username);
			::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)msg,NULL);
			break;
		case 1:
			sprintf(msg,"%s来电…",m_sipMsg_t->from->url->username);
			::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)msg,NULL);
			break;
		case 2:
			sprintf(msg,"%s来电……",m_sipMsg_t->from->url->username);
			::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)msg,NULL);
			break;
		case 3:
			sprintf(msg,"%s来电………",m_sipMsg_t->from->url->username);
			::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)msg,NULL);
			break;
		case 4:
			sprintf(msg,"%s来电…………",m_sipMsg_t->from->url->username);
			::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)msg,NULL);
			break;
		case 5:
			sprintf(msg,"%s来电……………",m_sipMsg_t->from->url->username);
			::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)msg,NULL);
			break;
		default:
			break;
		}
		tcount ++;
		Sleep(1000);
	}
	if (m_state == End)
	{
		return 0L;
	}
	m_sipMsg->SetLocalAdd(m_sipMsg_t->from->url->host,
					strlen(m_sipMsg_t->from->url->host),atoi(m_sipMsg_t->from->url->port));
	m_sipMsg->SetRemoteAdd(m_sipMsg_t->to->url->host,
				   strlen(m_sipMsg_t->to->url->host),atoi(m_sipMsg_t->to->url->port));

	m_sipMsg->SetAudioBody(true);
	unsigned int send_msg_len = BUFSIZ;
	m_sipMsg->GetSipMessage(m_sendMsg,&send_msg_len,Invoid200);
	g_clientSock->GetSockStream()->Write(m_sendMsg,strlen(m_sendMsg),m_ip,m_port,3);
	m_state = WaitACK;
	g_timer.Erase(m_timerID);
	g_timer.SetTimer(3,CallInTimeOutProc,(void*)m_sendMsg);
	::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)"发送200",NULL);
	return 0L;
}

LONG CCallInState::AtRecvCancelState(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//1.送到网络CANCEL消息
//
//*****处理过程*****
//1.通知UI
//2.发送200
//3.设置状态为END
	unsigned int send_msg_len = BUFSIZ;
	m_sipMsg->GetSipMessage(m_sendMsg,&send_msg_len,Invoid200);
	g_clientSock->GetSockStream()->Write(m_sendMsg,strlen(m_sendMsg),m_ip,m_port,3);
	m_state = End;
	::PostThreadMessage(g_stateManager.GetThreadID(),STATECHANGE,(WPARAM)CALLIN,NULL);
	return 0L;
}

LONG CCallInState::AtByeState(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//1.送到界面BYE消息
//
//*****处理过程*****
//1.发送BYE给对方
//2.插入定时器3秒，进去等待200状态
	unsigned int send_msg_len = BUFSIZ;
	m_sipMsg->GetSipMessage(m_sendMsg,&send_msg_len,ByeSip);
	AfxMessageBox(m_sendMsg);
	g_clientSock->GetSockStream()->Write(m_sendMsg,strlen(m_sendMsg),m_ip,m_port,3);
//	m_state = Wait200;
//	g_timer.SetTimer(3,CallInTimeOutProc,(void*)m_sendMsg);	
	m_state = End;
	::PostThreadMessage(g_stateManager.GetThreadID(),STATECHANGE,(WPARAM)CALLIN,NULL);	
	return 0L;
}

LONG CCallInState::AtEndState(void *vparam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//
//*****处理过程*****
//1.发送KILLME给状态机管理类
	::PostThreadMessage(g_stateManager.GetThreadID(),KillMe,(WPARAM)CALLIN,NULL);
	g_audioCtrl->Stop();
	return 0L;
}

LONG CCallInState::AtWait200State(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//1.发送了BYE给对方
//
//*****处理过程*****
//1.插入3秒定时器
//2.保存定时器ID
//3.设置COUNT++
	m_count++;
	if (m_count > 3)
	{
		m_state = End;
		CCallOutState::OnStateChange();
		return 0;
	}
    char *pSendMsg = m_sendMsg;
  	unsigned int ret = 	
		g_clientSock->GetSockStream()->Write(pSendMsg,strlen(pSendMsg),m_ip,m_port,3);
 	m_timerID = g_timer.SetTimer(1,CallInTimeOutProc,(void*)pSendMsg);
	return 0L;
}

LONG CCallInState::AtRectByeState(void *vParam)
{
//////////////////////////////////////////////////////////////////////////
//
//*****触发条件*****
//1.收到对方BYE消息
//
//*****处理过程*****
//1.发送200给对方
//2.通知界面
//设置状态为END
	unsigned int send_msg_len = BUFSIZ;
	m_sipMsg->GetSipMessage(m_sendMsg,&send_msg_len,Invoid200);
	g_clientSock->GetSockStream()->Write(m_sendMsg,strlen(m_sendMsg),m_ip,m_port,3);
	m_state = End;
	::PostThreadMessage(g_stateManager.GetThreadID(),STATECHANGE,(WPARAM)CALLIN,NULL);
	return 0L;
}

int CCallInState::StrToSipMsgT(char *tMsg)
{
	parser_init();
	return osip_message_parse(m_sipMsg_t,tMsg,strlen(tMsg));
}

LONG CCallInState::OnRecvAck(void *vParam)
{
	m_state = Connecting;
	g_timer.Erase(m_timerID);
	::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)"正在通话",NULL);
	::PostMessage(m_ui_hwnd,CONNECT_TIME,NULL,NULL);
	return 0L;
}

LONG CCallInState::AtCancenState(void *vParam)
{
	unsigned int send_msg_len = BUFSIZ;
	m_sipMsg->GetSipMessage(m_sendMsg,&send_msg_len,CMD487);
	g_clientSock->GetSockStream()->Write(m_sendMsg,strlen(m_sendMsg),m_ip,m_port,3);
	::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)"已经拒绝连接",NULL);
	::PostThreadMessage(g_stateManager.GetThreadID(),KillMe,(WPARAM)CALLIN,NULL);
 	m_state = End;
//	::PostThreadMessage(g_stateManager.GetThreadID(),STATECHANGE,(WPARAM)CALLIN,NULL);
	return 0L;
}