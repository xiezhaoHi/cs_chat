// AudioControl.h: interface for the CAudioControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDIOCONTROL_H__3FA2A99F_C012_4AA1_AFC9_C77C918569A9__INCLUDED_)
#define AFX_AUDIOCONTROL_H__3FA2A99F_C012_4AA1_AFC9_C77C918569A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AudioSocket.h"
#include "PhoneWaveIn.h"
#include "WaveOut.h"


class CAudioControl  
{
public:
	CAudioControl();
	virtual ~CAudioControl();
	void Start(char *ip,char *port);
	void Stop();

	CSocketBase m_sockBase;
	CSocketStream* m_sockStream;
	CAudioSocket* m_audioSock;
	CPhoneWaveIn* m_waveIn;
	CWaveOut* m_waveOut;
	SOCKET m_sockID;

};

#endif // !defined(AFX_AUDIOCONTROL_H__3FA2A99F_C012_4AA1_AFC9_C77C918569A9__INCLUDED_)
