// TestWaveIn.cpp: implementation of the CTestWaveIn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "TestWaveIn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestWaveIn::CTestWaveIn()
{
	m_waveOut.StartPlay();
}

CTestWaveIn::~CTestWaveIn()
{

}

void CTestWaveIn::GetData(char *pBuffer,int iLen)
{
	char buf[1024] = {0};
	memcpy(buf,pBuffer,iLen);
	m_waveOut.Play(buf,iLen);
	CWaveIn::GetData(pBuffer,iLen);
}
