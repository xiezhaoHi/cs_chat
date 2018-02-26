#ifndef SOCKETCONNECT_H
#define SOCKETCONNECT_H

#include "IOSocket.h"


class CSockConnector : public CSocketBase
{
public:
	
	CSockConnector();
	~CSockConnector();
	
	bool Open(const unsigned short port);
	bool Connect(const char *ip, const unsigned short port);
};

#endif;