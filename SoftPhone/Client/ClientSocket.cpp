// ClientSocket.cpp: implementation of the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "ClientSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientSocket::CClientSocket()
{
	m_sockBase.Open(0,UDPMode);
	m_socket = new CSocketStream(m_sockBase.GetSocket());
}

CClientSocket::~CClientSocket()
{
	if (m_socket != NULL)
	{
		delete m_socket;
		m_socket = NULL;
	}
}

void CClientSocket::SetMsgQueue(CMsgQueue *msgQueue)
{
	m_msgQueue = msgQueue;
	if (m_msgQueue == NULL)
	{
		::MessageBox(NULL,"消息队列未创建","错误",MB_OK);
		return ;
	}
}

CSocketStream* CClientSocket::GetSocketStream()
{
	return m_socket;
}

ULONG CClientSocket::Process()
{
	int ret = 0;
  	char ip[IP_LEN] = {0};
  	while(!m_stopFlag)
	{
		char *buf = new char[BUFFER_SIZE];
  		memset(buf,0,BUFFER_SIZE);
  		ret = m_socket->Read(buf,BUFFER_SIZE,ip,sizeof(ip),10);
  		if (ret > 0)
		{
			buf[ret] = '\0';
			CMessage *tMsg = new CMessage;
			if(0 == strncmp(buf,"SIP/2.0 200",11))
			{			
				tMsg->m_msgType = MSG200;
				tMsg->m_lparam = (void *)buf;
				tMsg->m_wparam = (void *)&ret;
				m_msgQueue->AddMsg(tMsg);
			}
			else if (0 == strncmp(buf,"SIP/2.0 400",11))
			{
				tMsg->m_msgType = MSG400;
				tMsg->m_lparam = (void *)buf;
				tMsg->m_wparam = (void *)&ret;
				m_msgQueue->AddMsg(tMsg);
			}
			else if (0 == strncmp(buf,"SIP/2.0 302",11))
			{
				tMsg->m_msgType = MSG302;
				tMsg->m_lparam = (void *)buf;
				tMsg->m_wparam = (void *)&ret;
				m_msgQueue->AddMsg(tMsg);
			}
			else if(0 == strncmp(buf,"SIP/2.0 180",11))
			{
				tMsg->m_msgType = MSG180;
				tMsg->m_lparam = (void *)buf;
				tMsg->m_wparam = (void *)&ret;
				m_msgQueue->AddMsg(tMsg);
			}
			else if (0 == strncmp(buf,"INVITE",6))
			{
				tMsg->m_msgType = CALLIN;
				tMsg->m_lparam = (void *)buf;
				tMsg->m_wparam = (void *)&ret;
				m_msgQueue->AddMsg(tMsg);
			}
			else if (0 == strncmp(buf,"SIP/2.0 404",11))
			{
				::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)"对方不在线或不存在号码",NULL);
			}
			else if (0 == strncmp(buf,"ACK",3))
			{
 				::PostMessage(m_ui_hwnd,WM_UIMSG,(WPARAM)"正在通话1111",NULL);
				tMsg->m_msgType = MSGACK;
				tMsg->m_lparam = (void *)buf;
				tMsg->m_wparam = (void *)&ret;
				m_msgQueue->AddMsg(tMsg);				
			}
			else if(0 == strncmp(buf,"CANCEL",6))
			{
				tMsg->m_msgType = CANCEL_RCV;
				tMsg->m_lparam = (void *)buf;
				tMsg->m_wparam = (void *)ret;
				m_msgQueue->AddMsg(tMsg);
			}
			else if(0 == strncmp(buf,"BYE",3))
			{
				tMsg->m_msgType = BYE_RCV;
				tMsg->m_lparam = (void *)buf;
				tMsg->m_wparam = (void *)ret;
				m_msgQueue->AddMsg(tMsg);
			}
			else if (0 == strncmp(buf,"SIP/2.0 487",11))
			{
				tMsg->m_msgType = CMD487_RCV;
				tMsg->m_lparam = (void *)buf;
				tMsg->m_wparam = (void *)ret;
				m_msgQueue->AddMsg(tMsg);
			}
			else
			{
				delete []buf;
				delete tMsg;
			}
		}
		else
		{
			delete []buf;
		}
		Sleep(100);
	}
  	return 0;
}

CSocketStream* CClientSocket::GetSockStream()
{
	return m_socket;
}