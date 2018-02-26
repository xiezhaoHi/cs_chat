// PhoneWaveIn.h: interface for the CPhoneWaveIn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PHONEWAVEIN_H__27848FCE_3520_4F42_B56E_EB07CD52AE8F__INCLUDED_)
#define AFX_PHONEWAVEIN_H__27848FCE_3520_4F42_B56E_EB07CD52AE8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WaveIn.h"
#include "AudioCode.h"

class CPhoneWaveIn : public CWaveIn  
{
public:
	CPhoneWaveIn(CSocketStream *socket);
	virtual ~CPhoneWaveIn();
	void GetData(char *pBuffer,int iLen);
	void SetRemoteAddr(char *ip,unsigned int port);
protected:
	CAudioCodeG729 m_code;
	CSocketStream *m_socket;
	char m_ip[20];
	unsigned int m_port;

};

#endif // !defined(AFX_PHONEWAVEIN_H__27848FCE_3520_4F42_B56E_EB07CD52AE8F__INCLUDED_)
