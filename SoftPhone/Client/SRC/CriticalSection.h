#ifndef _CriticalSection_H
#define _CriticalSection_H

#include <windows.h>

class CCriticalSection
{
public:
	CCriticalSection(LPCRITICAL_SECTION lpCriticalSection = NULL);
	~CCriticalSection();
	void SetCriticalSection(LPCRITICAL_SECTION lpCriticalSection = NULL);
	/*设置安全属性*/
	void Enter();//进入临界区
	void Leave();//离开临界区
protected:
	LPCRITICAL_SECTION m_lpCriticalSection;
};

#endif