#ifndef _IOSOCKET_CPP
#define _IOSOCKET_CPP

#include "IOSocket.h"

CSocketBase::CSocketBase()  
{
	m_socket = -1;
}

CSocketBase::~CSocketBase()
{
	Close();
}


bool CSocketBase::Close()
{
	return closesocket(m_socket)==0;
}


const SOCKET CSocketBase::GetSocket() const
{
	return m_socket;
}

void CSocketBase::SetSocket(SOCKET socket)
{
	m_socket = socket;
}


bool CSocketBase::InitSocket(UINT low /* = 2 */,UINT high /* = 2 */)
{
	WORD ver = MAKEWORD(low,high);
	WSADATA wsaData;
	
	WSAStartup(ver,&wsaData);
	
	if(LOBYTE(wsaData.wVersion)!=low ||
		HIBYTE(wsaData.wVersion) != high)
	   {
		WSACleanup();
		return false;
	   }
	return true;
}

void CSocketBase::UnitSocket()
{
	WSACleanup();
}

bool CSocketBase::Open(const unsigned short port,SocketMode socketMode)
{
	switch(socketMode)
	{
	case TCPMode:
		m_socket = socket(AF_INET,SOCK_STREAM,0);
		break;
	case UDPMode:
		m_socket = socket(AF_INET,SOCK_DGRAM,0);
	    break;
	default:
	    break;
	}
	if (m_socket == SOCKET_ERROR)
	{
		return false;
	}
	SOCKADDR_IN local;
	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_port = htons(port);
	int ret = bind(m_socket,(SOCKADDR*)&local,sizeof(SOCKADDR_IN));
	if (ret == SOCKET_ERROR)
	{
		return false;
	}
	return true;
}

bool CSocketBase::Open(const unsigned short port)
{
	return true;
}

#endif /*_IOSOCKET_CPP*/