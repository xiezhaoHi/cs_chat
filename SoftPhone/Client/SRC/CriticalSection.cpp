#include "CriticalSection.h"

CCriticalSection::CCriticalSection
	(LPCRITICAL_SECTION lpCriticalSection /* = NULL */)
{
	m_lpCriticalSection = lpCriticalSection;
	InitializeCriticalSection(m_lpCriticalSection);
}

CCriticalSection::~CCriticalSection()
{
	DeleteCriticalSection(m_lpCriticalSection);
}

void CCriticalSection::Enter()
{
	EnterCriticalSection(m_lpCriticalSection);
}

void CCriticalSection::Leave()
{
	LeaveCriticalSection(m_lpCriticalSection);
}

