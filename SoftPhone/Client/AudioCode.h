/*------------------------------------------------------------------------------*\
 [ģ������]
	CAudioCode

 [�ļ�����]
	AudioCode.h

 [����ļ�]
	AudioCode.cpp

 [Ŀ��]
 
     ������Ƶ��ѹ�� 
     	  
 [����]
		
	��װ g.729 api
	
 [������]
	
	 va_g729a.lib      g7231.lib                        
\*------------------------------------------------------------------------------*/

#ifndef _AUDIOCODE_H_
#define _AUDIOCODE_H_

#define SIZE_AUDIO_FRAME 160
#define SIZE_AUDIOG729_PACKED 10

#define SIZE_AUDIOG7231_PACKED 48

class CAudioCodeG729
{
public:
	virtual  ~CAudioCodeG729();
	CAudioCodeG729();

	BOOL EncodeAudioData(char *pin,int len,char* pout,int* lenr);
	BOOL DecodeAudioData(char *pin,int len,char* pout,int* lenr);
};


class CAudioCodeG7231
{
public:
	virtual  ~CAudioCodeG7231();
	CAudioCodeG7231();

	BOOL EncodeAudioData(char *pin,int len,char* pout,int* lenr);
	BOOL DecodeAudioData(char *pin,int len,char* pout,int* lenr);
};


#endif