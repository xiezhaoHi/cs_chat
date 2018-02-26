#ifndef _SOCKETSTREAM_CPP
#define _SOCKETSTREAM_CPP

#include "SocketStream.h"

CSocketStream::CSocketStream(SOCKET socket)
{
	m_socket = socket;
}

CSocketStream::~CSocketStream()
{
	
}


int CSocketStream::Read(char *buf, const int len)
{
	if(NULL == buf)
	{
		return -2;
	}
	return recv(m_socket,buf,len,0);
}

int CSocketStream::Read(char *buf,
						const int len,
						char *ip, 
						const int ipLen)
{
	if(NULL==buf || NULL==ip)
	{
		return -2;
	}	
	sockaddr_in from = {0};
	int fromLen = sizeof(sockaddr_in);	
	int ret = recvfrom(m_socket,buf,len,0,(sockaddr*)&from,&fromLen);	
	strncpy(ip, inet_ntoa(from.sin_addr),ipLen-1);	
	return ret;
}

int CSocketStream::Read(char *buf, 
						const int len, 
						char *ip, 
						const int ipLen,
						const struct timeval FAR *timeout)
{
	if(NULL==buf || NULL==ip)
	{
		return -2;
	}
	sockaddr_in from = {0};
	int fromLen = sizeof(sockaddr_in);
	int ret;
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(m_socket,&fdset);
	ret = select(m_socket,&fdset,NULL,NULL,timeout);
	if (ret > 0 && FD_ISSET(m_socket,&fdset))
	{
		ret = recvfrom(m_socket,buf,len,0,(sockaddr*)&from,&fromLen);
		if (ret == SOCKET_ERROR)
		{
			ret = GetLastError();
		}
		strncpy(ip, inet_ntoa(from.sin_addr),ipLen-1);
	}
	return ret;
}

int CSocketStream::Read(char *buf, 
						const int len, 
						char *ip, 
						const int ipLen, 
						const unsigned int timeVal)
{
	timeval tm;
	tm.tv_sec = timeVal;
	tm.tv_usec = 0;
	return Read(buf,len,ip,ipLen,&tm);
}


int CSocketStream::Write(const char *buf, const int len)
{

	return send(m_socket,buf,len,0);
}
int CSocketStream::Write(const char *buf, 
						 const int len, 
						 const char *ip, 
						 unsigned short port)
{
	sockaddr_in remute = {0};
	remute.sin_family = AF_INET;
	remute.sin_port = htons(port);
	remute.sin_addr.S_un.S_addr = inet_addr(ip);
	return sendto(m_socket,buf,len,0,(sockaddr*)&remute,sizeof(sockaddr_in));
}

int CSocketStream::Write(const char *buf, 
						 const int len, 
						 const char *ip, 
						 unsigned short port, 
						 const struct timeval FAR *timeout)
{
	sockaddr_in remute = {0};
	remute.sin_family = AF_INET;
	remute.sin_port = htons(port);
	remute.sin_addr.S_un.S_addr = inet_addr(ip);
	int ret;
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(m_socket,&fdset);
	ret = select(m_socket,NULL,&fdset,NULL,timeout);
	if (ret > 0 && FD_ISSET(m_socket,&fdset))
	{
		ret = sendto(m_socket,buf,len,0,(sockaddr*)&remute,sizeof(sockaddr_in));
	}
	return ret;
}

int CSocketStream::Write(const char *buf, 
						 const int len, 
						 const char *ip, 
						 unsigned short port, 
						 const unsigned int timeVal)
{
	timeval tm;
	tm.tv_sec = timeVal;
	tm.tv_usec = 0;
	return Write(buf,len,ip,port,&tm);

}

int CSocketStream::GetSockPort()
{
	sockaddr_in addr;
	int port = 0;
	int len = sizeof(sockaddr_in);
	getsockname(m_socket,(sockaddr*)&addr,&len);
	port = htons(addr.sin_port);
	return port;
}

int CSocketStream::GetLocalIp(char *ip,int ipLen)
{
	char *name = new char[MAX_PATH];
	int len = MAX_PATH;
	gethostname(name,len);
	hostent *hen;
	hen = gethostbyname(name);
	strncpy(ip,inet_ntoa(*(struct in_addr *)hen->h_addr_list[0]),len);
	return 0;
}

#endif