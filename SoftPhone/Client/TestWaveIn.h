// TestWaveIn.h: interface for the CTestWaveIn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTWAVEIN_H__1624EC77_EBC3_4CF2_910A_0C8716CE7EA2__INCLUDED_)
#define AFX_TESTWAVEIN_H__1624EC77_EBC3_4CF2_910A_0C8716CE7EA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WaveIn.h"
#include "WaveOut.h"

class CTestWaveIn : public CWaveIn  
{
public:
	CTestWaveIn();
	virtual ~CTestWaveIn();
	void GetData(char *pBuffer,int iLen);

	CWaveOut m_waveOut;
};

#endif // !defined(AFX_TESTWAVEIN_H__1624EC77_EBC3_4CF2_910A_0C8716CE7EA2__INCLUDED_)
