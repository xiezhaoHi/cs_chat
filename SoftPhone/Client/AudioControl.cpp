// AudioControl.cpp: implementation of the CAudioControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "AudioControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAudioControl::CAudioControl()
{
  	m_sockBase.Open(0,UDPMode);
  	m_sockStream = new CSocketStream(m_sockBase.GetSocket());
	m_waveIn = new CPhoneWaveIn(m_sockStream);
	m_waveOut = new CWaveOut();
	m_audioSock = new CAudioSocket(m_waveOut,m_sockStream);
}

CAudioControl::~CAudioControl()
{
	if (m_sockStream != NULL)
	{
		delete m_sockStream;
		m_sockStream = NULL;
	}
	if (m_waveIn != NULL)
	{
		delete m_waveIn;
		m_waveIn = NULL;
	}
	if (m_waveOut != NULL)
	{
		delete m_waveOut;
		m_waveOut = NULL;
	}
	if (m_audioSock != NULL)
	{
		delete m_audioSock;
		m_audioSock = NULL;
	}
}

void CAudioControl::Start(char *ip,char *port)
{
	m_waveIn->SetRemoteAddr(ip,atoi(port));
	m_waveIn->StartRec();
	m_waveOut->StartPlay();
	m_audioSock->Start();
}

void CAudioControl::Stop()
{
	m_waveIn->StopRec();
	m_waveOut->StopPlay();
	m_audioSock->Stop();
}
