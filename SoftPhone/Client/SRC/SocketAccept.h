#ifndef _SOCKETSTREAM_H
#define _SOCKETSTREAM_H

#include "IOSocket.h"

class CSocketAccept : public CSocketBase
{
public:
	CSocketAccept();
	~CSocketAccept();

	bool Open(const unsigned short port);
	bool Listen(int maxLog);
	SOCKET Accept();

};

#endif /*_SOCKSTREAM_H*/