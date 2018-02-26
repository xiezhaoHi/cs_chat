#ifndef _SOCKETSTREAM_CPP
#define _SOCKETSTREAM_CPP

#include "SocketAccept.h"

CSocketAccept::CSocketAccept()
{

}

CSocketAccept::~CSocketAccept()
{

}

bool CSocketAccept::Open(const unsigned short port)
{
	m_socket = socket(AF_INET,SOCK_STREAM,0);
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

bool CSocketAccept::Listen(int maxLog)
{
	int ret = listen(m_socket,maxLog);
	return SOCKET_ERROR != ret;
}

SOCKET CSocketAccept::Accept()
{
	SOCKADDR_IN from;
	int len = sizeof(from);
	return accept(m_socket,(SOCKADDR*)&from,&len);
}


#endif /*_SOCKSTREAM_CPP*/