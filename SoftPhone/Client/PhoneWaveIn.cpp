// PhoneWaveIn.cpp: implementation of the CPhoneWaveIn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "PhoneWaveIn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPhoneWaveIn::CPhoneWaveIn(CSocketStream *socket):m_socket(socket)
{
	m_port = 0;
}

CPhoneWaveIn::~CPhoneWaveIn()
{

}

void CPhoneWaveIn::SetRemoteAddr(char *ip,unsigned int port)
{
	strncpy(m_ip,ip,20);
	m_port = port;
}

void CPhoneWaveIn::GetData(char *pBuffer,int iLen)
{
	if (m_ip == NULL && m_port == 0)
	{
		return;
	}
	char buf[1024] = {0};
	memcpy(buf,pBuffer,iLen);
	char sbuf[1024] = {0};
	int len = 0;
	m_code.EncodeAudioData(buf,iLen,sbuf,&len);
 	m_socket->Write(buf,iLen,m_ip,m_port,10);
	CWaveIn::GetData(pBuffer,iLen);
//	Sleep(1);
// 	char buf[1024] = {0};
// 	memcpy(buf,pBuffer,iLen);
// 	m_waveOut.Play(buf,iLen);
// 	CWaveIn::GetData(pBuffer,iLen);

}