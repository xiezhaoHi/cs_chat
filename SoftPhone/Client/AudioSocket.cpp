// AudioSocket.cpp: implementation of the CAudioSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "AudioSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAudioSocket::CAudioSocket(CWaveOut *waveOut,CSocketStream* socket)
:m_waveOut(waveOut),m_socket(socket)
{
// 	m_sockID = m_socketBase.Open(0,UDPMode);
// 	m_socket = new CSocketStream(m_sockID);
}

CAudioSocket::~CAudioSocket()
{
	if (NULL != m_socket)
	{
		delete m_socket;
		m_socket = NULL;
	}
}

CSocketStream* CAudioSocket::GetSocketStream()
{
	return m_socket;
}

int CAudioSocket::GetSocketPort()
{
	return m_socket->GetSockPort();
}

ULONG CAudioSocket::Process()
{
	char buf[1024] = {0};
	char tbuf[1024] = {0};
	int len = 0;
	char ip[IP_LEN] = {0};
	int ret;
	while (!m_stopFlag)
	{
		ret = m_socket->Read(buf,1024,ip,IP_LEN,10);
		if (ret > 0)
		{
  			m_code.DecodeAudioData(buf,ret,tbuf,&len);
			m_waveOut->Play(buf,ret);
		}
	}
	return 0L;
}