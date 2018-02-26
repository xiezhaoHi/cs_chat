#ifndef _SOCKETSTREAM_H
#define _SOCKETSTREAM_H


#include "IOSocket.h"

class CSocketStream : public ISocketIO
{
public:
	
	CSocketStream(SOCKET socket);
	~CSocketStream();
	
	virtual int Read(char *buf, const int len);
	virtual int Read(char *buf, 
				   	 const int len, 
					 char *ip, 
					 const int ipLen);
	virtual int Read(char *buf,
					 const int len,
					 char *ip,
					 const int ipLen,
					 const struct timeval FAR *timeout);
	virtual int Read(char *buf,
					 const int len,
					 char *ip,
					 const int ipLen,
					 const unsigned int timeVal);

	
	virtual int Write(const char *buf, const int len);
	virtual int Write(const char *buf, 
					  const int len, 
					  const char *ip,  
					  unsigned short port);
	virtual int Write(const char *buf,
					  const int len,
					  const char *ip,
					  unsigned short port,
					  const struct timeval FAR *timeout);	
	virtual int Write(const char *buf,
					  const int len,
					  const char *ip,
					  unsigned short port,
					  const unsigned int timeVal);
	int GetSockPort();
	int GetLocalIp(char *ip,int ipLen);

	
private:
	SOCKET m_socket;
};


#endif;