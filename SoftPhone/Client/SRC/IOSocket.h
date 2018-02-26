#ifndef _IOSOCKET_H
#define _IOSOCKET_H

#include <windows.h>
#include <winsock.H>
#pragma  comment(lib,"ws2_32.lib")
enum SocketMode{
	TCPMode,
	UDPMode
};

class ISocketIO{
public:
	virtual int Read(char *buf, const int len) = 0;
	virtual int Read(char *buf, 
					 const int len, 
					 char *ip, 
					 const int ipLen) = 0;
	virtual int Read(char *buf,
					 const int len,
					 char *ip,
					 const int ipLen,
					 const struct timeval FAR *timeout) = 0;

	virtual int Write(const char *buf, const int len) = 0;
	virtual int Write(const char *buf, 
					  const int len, 
					  const char *ip,  
					  unsigned short port) = 0;
	virtual int Write(const char *buf,
					  const int len,
					  const char *ip,
					  unsigned short port,
					  const struct timeval FAR *timeout) = 0;
};

class CSocketBase{
public:
	CSocketBase();
	virtual ~CSocketBase();

	static bool InitSocket(UINT low = 2,UINT high = 2);
	static void UnitSocket();

	virtual bool Open(const unsigned short port);
	bool Open(const unsigned short port,SocketMode socketMode);
	bool Close();

	const SOCKET GetSocket() const;
	void SetSocket(SOCKET socket);
protected:
	SOCKET m_socket;
};

#endif /*_IOSOCKET_H*/