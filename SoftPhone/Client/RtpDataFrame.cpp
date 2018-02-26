/********************************************************************************/
#include "stdafx.h"
#include "RtpDataFrame.h"
#include <string.h>
#include <time.h>
#include "trace.h"

CRtpDataFrame::CRtpDataFrame(int iPlayLoadSize)
{
	m_pcData = new char[iPlayLoadSize + MINHEADERSIZE];
	m_iPayloadSize = iPlayLoadSize;
	memset(m_pcData, 0, iPlayLoadSize + MINHEADERSIZE);
	
	m_pcData[0] = '\x80';	//设置协议版本 2.0
}

CRtpDataFrame::~CRtpDataFrame()
{
	if(m_pcData != NULL)
		delete []m_pcData;
}

unsigned CRtpDataFrame::m_uGetVersion() const
{
	return (m_pcData[0] >> 6) & 3;
}

bool CRtpDataFrame::m_bGetExtension() const 
{
	return (m_pcData[0] & 0x10) != 0;
}

void CRtpDataFrame::m_vSetExtension(bool bExt)
{
	if (bExt)
		m_pcData[0] |= 0x10;
	else
		m_pcData[0] &= 0xef;
}

bool CRtpDataFrame::m_bGetMarker() const
{
	return (m_pcData[1] & 0x80) != 0;
}

void CRtpDataFrame::m_vSetMarker(bool bMarker)
{
	if (bMarker)
		m_pcData[1] |= 0x80;
	else
		m_pcData[1] &= 0x7f;
}

CRtpDataFrame::PayloadTypes CRtpDataFrame::m_pGetPayloadType() const
{
	return (CRtpDataFrame::PayloadTypes)(m_pcData[1]&0x7f);
}

void CRtpDataFrame::m_vSetPayloadType(CRtpDataFrame::PayloadTypes payLoadType)
{
	m_pcData[1] &= 0x80;
	m_pcData[1] |= payLoadType;
}

WORD CRtpDataFrame::m_wGetSequenceNumber() const
{
	return m_pcData[2] * 256 + m_pcData[3];	
}

void CRtpDataFrame::m_vSetSequenceNumber(WORD seqNumber)
{
	m_pcData[2] = (seqNumber &0xff00) >> 8;
	m_pcData[3] = seqNumber &0x00ff; 
}

DWORD CRtpDataFrame::m_dwGetTimestamp() const
{
	return m_pcData[4] * 256 * 256 * 256 + m_pcData[5] * 256 * 256 + m_pcData[6] * 256 + m_pcData[7];
}

void CRtpDataFrame::m_vSetTimestamp(DWORD Timestamp)
{
	m_pcData[4] = (Timestamp & 0xff000000) >> 24;
	m_pcData[5] = (Timestamp & 0x00ff0000) >> 16;
	m_pcData[6] = (Timestamp & 0x0000ff00) >> 8;
	m_pcData[7] = (Timestamp & 0x000000ff);
}

DWORD CRtpDataFrame::m_dwGetSyncSource() const
{
	return m_pcData[8] * 256 * 256 * 256 + m_pcData[9] * 256 * 256 + m_pcData[10] * 256 + m_pcData[11];
};

void CRtpDataFrame::m_vSetSyncSource(DWORD SyncSource)
{
	m_pcData[8] = (SyncSource & 0xff000000) >> 24;
	m_pcData[9] = (SyncSource & 0x00ff0000) >> 16;
	m_pcData[10] = (SyncSource & 0x0000ff00) >> 8;
	m_pcData[11] = (SyncSource & 0x000000ff);
}

int CRtpDataFrame::m_iGetContribSrcCount() const
{
	return m_pcData[0] & 0xf;
}

DWORD CRtpDataFrame::m_dwGetContribSource(int idx) const
{
	return ((DWORD *)&m_pcData[MINHEADERSIZE])[idx];
}

void CRtpDataFrame::m_vSetContribSource(int idx, DWORD src)
{
	if(idx > m_iGetContribSrcCount())
	{
		int iOldSize = m_iGetHeaderSize();

		m_pcData[0] &= 0xf0;
		m_pcData[0] |= idx+1;

		char* pcTmp = new char[m_iGetHeaderSize()+m_iPayloadSize];
		memset(pcTmp, 0x00, m_iGetHeaderSize()+m_iPayloadSize);

		memcpy(pcTmp, m_pcData, iOldSize);
		memcpy(pcTmp + m_iGetHeaderSize(), m_pcData + iOldSize, m_iPayloadSize);
		
		delete []m_pcData;
		m_pcData = pcTmp;
	}
	((DWORD *)&m_pcData[MINHEADERSIZE])[idx] = src;
}

int CRtpDataFrame::m_iGetHeaderSize() const 
{
	int iSize = MINHEADERSIZE + 4*m_iGetContribSrcCount();
	if(m_bGetExtension())
	{
		iSize += 4 + m_iGetExtensionSize();
	}

	return iSize;
}

int CRtpDataFrame::m_iGetExtensionType() const 
{
	if(m_bGetExtension())
	{
		return *(WORD *)&m_pcData[MINHEADERSIZE + 4*m_iGetContribSrcCount()];
	}
	else
		return -1;
}

void CRtpDataFrame::m_vSetExtensionType(int iType)
{
	if(iType < 0)
		m_vSetExtension(false);
	else
	{
		if(!m_bGetExtension())
			m_bSetExtensionSize(0);
		else
			*(WORD *)&m_pcData[MINHEADERSIZE + 4*m_iGetContribSrcCount()] = (WORD)iType;
	}
}

int CRtpDataFrame::m_iGetExtensionSize() const
{
	if(m_bGetExtension())
	{
		return *(WORD *)&m_pcData[MINHEADERSIZE + 4*m_iGetContribSrcCount() + 2];
	}
	else
		return 0;
}

bool CRtpDataFrame::m_bSetExtensionSize(int iSize)
{
	return true;
}

char* CRtpDataFrame::m_pcExtensionPtr() const
{
	if(m_bGetExtension())
	return (char *)&m_pcData[MINHEADERSIZE + 4*m_iGetContribSrcCount()];
}

int CRtpDataFrame::m_iGetPayloadSize() const
{
	return m_iPayloadSize;
}

bool CRtpDataFrame::m_bSetPayloadSize(int iPayloadSize)
{
	if(m_iPayloadSize < iPayloadSize)
	{
		char* pcTmp = new char[m_iGetHeaderSize() + iPayloadSize + 5];
		memset(pcTmp, 0x00, m_iGetHeaderSize()+iPayloadSize);
		memcpy(pcTmp, m_pcData, m_iGetHeaderSize() + m_iPayloadSize);

		delete []m_pcData;
		m_pcData = pcTmp;
	}

	m_iPayloadSize = iPayloadSize;

	return true;
}

char* CRtpDataFrame::m_pcPayloadPtr() const
{
	return (char *)(m_pcData + m_iGetHeaderSize());
}

char* CRtpDataFrame::m_pcGetPointer() const
{
	return m_pcData;
}
/********************************************************************************/