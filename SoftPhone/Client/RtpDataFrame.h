/********************************************************************************************
描述：定义RTP、RTCP包格式, RTPSESSION网络通讯类
********************************************************************************************/
#ifndef __RTPDATAFRAME_H
#define __RTPDATAFRAME_H

//#include <winsock2.h>
//#include <pthread.h>
//定义协议版本
#define RTPVERSION 2
#define MINHEADERSIZE 12

class CRtpDataFrame
{
public:
	CRtpDataFrame(int iPlayLoadSize  = 2048);
	~CRtpDataFrame();

	//定义编解码类型
	enum PayloadTypes {
		PCMU,         // G.711 u-Law
			FS1016,       // Federal Standard 1016 CELP
			G721,         // ADPCM - Subsumed by G.726
			G726 = G721,
			GSM,          // GSM 06.10
			G7231,        // G.723.1 at 6.3kbps or 5.3 kbps
			DVI4_8k,      // DVI4 at 8kHz sample rate
			DVI4_16k,     // DVI4 at 16kHz sample rate
			LPC,          // LPC-10 Linear Predictive CELP
			PCMA,         // G.711 A-Law
			G722,         // G.722
			L16_Stereo,   // 16 bit linear PCM
			L16_Mono,     // 16 bit linear PCM
			G723,         // G.723
			CN,           // Confort Noise
			MPA,          // MPEG1 or MPEG2 audio
			G728,         // G.728 16kbps CELP
			DVI4_11k,     // DVI4 at 11kHz sample rate
			DVI4_22k,     // DVI4 at 22kHz sample rate
			G729,         // G.729 8kbps
			Cisco_CN,     // Cisco systems comfort noise (unofficial)
			
			CelB = 25,    // Sun Systems Cell-B video
			JPEG,         // Motion JPEG
			H261 = 31,    // H.261
			MPV,          // MPEG1 or MPEG2 video
			MP2T,         // MPEG2 transport system
			H263,         // H.263
			
			LastKnownPayloadType,
			
			DynamicBase = 96,
			DTMF_RFC2833 = 101,
			MaxPayloadType = 127,
			IllegalPayloadType
	   };

	//接口成员
	unsigned m_uGetVersion() const;
	bool m_bGetExtension() const;
	void m_vSetExtension(bool bExt);

	bool m_bGetMarker() const;
	void m_vSetMarker(bool bMarker);

	PayloadTypes m_pGetPayloadType() const;
	void m_vSetPayloadType(PayloadTypes payLoadType);

	WORD m_wGetSequenceNumber() const;
	void m_vSetSequenceNumber(WORD seqNumber);

	DWORD m_dwGetTimestamp() const;
	void m_vSetTimestamp(DWORD Timestamp);

	DWORD m_dwGetSyncSource() const;
	void m_vSetSyncSource(DWORD SyncSource);
	
	int m_iGetContribSrcCount() const;
	DWORD m_dwGetContribSource(int idx) const;
	void m_vSetContribSource(int idx, DWORD src);

	int m_iGetHeaderSize() const;
	int m_iGetExtensionType() const;
	void m_vSetExtensionType(int iType);
	int m_iGetExtensionSize() const;
	bool m_bSetExtensionSize(int iSize);
	char* m_pcExtensionPtr() const;

	int m_iGetPayloadSize() const;
	bool m_bSetPayloadSize(int iPayloadSize);
	char* m_pcPayloadPtr() const;

	char* m_pcGetPointer() const;

	//CRtpDataFrame& operator=(const CRtpDataFrame frame);

protected:
	char* m_pcData;
	int m_iPayloadSize;
};

#endif


