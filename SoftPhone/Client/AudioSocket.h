// AudioSocket.h: interface for the CAudioSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDIOSOCKET_H__407839A9_245D_46C9_85CF_55E4F48B6778__INCLUDED_)
#define AFX_AUDIOSOCKET_H__407839A9_245D_46C9_85CF_55E4F48B6778__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRC\AppThread.h"
#include "WaveOut.h"
#include "AudioCode.h"

class CAudioSocket : public CAppThread  
{
public:
	CAudioSocket(CWaveOut *waveOut,CSocketStream* socket);
	CSocketStream* GetSocketStream();
	int GetSocketPort();
	virtual ~CAudioSocket();
protected:
	CSocketStream *m_socket;
// 	CSocketBase m_socketBase;
	CWaveOut *m_waveOut;
	CAudioCodeG729 m_code;
	ULONG Process();
};

#endif // !defined(AFX_AUDIOSOCKET_H__407839A9_245D_46C9_85CF_55E4F48B6778__INCLUDED_)
