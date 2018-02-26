#ifndef _SOCKETCONNECT_CPP
#define _SOCKETCONNECT_CPP
#include "SocketConnect.h"

CSockConnector::CSockConnector()
{
	
}

CSockConnector::~CSockConnector()
{
	
}


bool CSockConnector::Open(const unsigned short port)
{
	m_socket = socket(AF_INET,SOCK_STREAM,0);
	
	return m_socket != SOCKET_ERROR;
}

bool CSockConnector::Connect(const char *ip, const unsigned short port)
{
	SOCKADDR_IN to;
	to.sin_family = AF_INET;
	to.sin_addr.S_un.S_addr = inet_addr(ip);
	to.sin_port = htons(port);
	
	int ret = connect(m_socket,(SOCKADDR*)&to,sizeof(SOCKADDR));
	
	return ret != SOCKET_ERROR;
}

#endif /*_SOCKCONNECT_CPP*/