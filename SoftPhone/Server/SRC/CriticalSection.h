#ifndef _CriticalSection_H
#define _CriticalSection_H

#include <windows.h>

class CCriticalSection
{
public:
	CCriticalSection(LPCRITICAL_SECTION lpCriticalSection = NULL);
	~CCriticalSection();
	void SetCriticalSection(LPCRITICAL_SECTION lpCriticalSection = NULL);
	/*���ð�ȫ����*/
	void Enter();//�����ٽ���
	void Leave();//�뿪�ٽ���
protected:
	LPCRITICAL_SECTION m_lpCriticalSection;
};

#endif