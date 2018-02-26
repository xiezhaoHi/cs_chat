// ReadSocket.cpp: implementation of the CReadSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Server.h"
#include "ServerSocket.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServerSocket::CServerSocket()
{
	m_sockBase.Open(SERVER_PORT,UDPMode);
	m_socket = new CSocketStream(m_sockBase.GetSocket());
}

CServerSocket::~CServerSocket()
{
	if (m_socket != NULL)
	{
		delete m_socket;
	}
}

ULONG CServerSocket::Process()
{
	int ret = 0;
	char *buf;
  	char ip[IP_LEN] = {0};
  	while(!m_stopFlag)
	{
		buf = new char[BUFFER_SIZE];
  		memset(buf,0,BUFFER_SIZE);
  		ret = m_socket->Read(buf,BUFFER_SIZE,ip,IP_LEN,3);
  		if (ret > 0)
		{
			buf[ret] = '\0';
			CMessage *tMsg = new CMessage;
			if(0 == strncmp(buf,"REGISTER",6))
			{			
				tMsg->m_msgType = REGISTER_MSG;
				tMsg->m_lparam = (void *)buf;
				tMsg->m_wparam = (void *)&ret;
				m_msgQueue->AddMsg(tMsg);
			}
			else if (0 == strncmp(buf,"INVITE",6))
			{
				tMsg->m_msgType = INVITE_MSG;
				tMsg->m_lparam = (void *)buf;
				tMsg->m_wparam = (void *)&ret;
				m_msgQueue->AddMsg(tMsg);
			}
		}
		Sleep(100);
	}
  	return 0;
}

void CServerSocket::SetMsgQueue(CMsgQueue *msgQueue)
{
	m_msgQueue = msgQueue;
	if (m_msgQueue == NULL)
	{
		::MessageBox(NULL,"消息队列未创建","错误",MB_OK);
		return ;
	}
	
}

CSocketStream* CServerSocket::GetSockStream()
{
	return m_socket;
}