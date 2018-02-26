#include "AppMutex.h"
#include <iostream>

CAppMutex::CAppMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes /* = NULL */, 
					 BOOL bInitialOwner /* = FALSE */, 
					 LPCTSTR lpName /* = NULL */)
{
	m_handle = NULL;
	m_milliSeconds = INFINITE;
	m_handle = CreateMutex(lpMutexAttributes,bInitialOwner,lpName);
}

CAppMutex::~CAppMutex()
{
	if (m_handle != NULL)
	{
		CloseHandle(m_handle);
		m_handle = NULL;
	}
}

CAppMutex::Lock(DWORD dwMilliseconds /*= INFINITE*/)
{
	BOOL flag = FALSE;
	m_milliSeconds = dwMilliseconds;
	if (m_handle != NULL)
	{
		if(0==::WaitForSingleObject(m_handle,m_milliSeconds))
		{
			flag = TRUE;
		}
	}
	return flag;
}

DWORD CAppMutex::Process()
{
	return 0;
}

DWORD CAppMutex::BeginMutex()
{
	Lock();
	Process();
	UnLock();
	return 0;
}

BOOL CAppMutex::UnLock()
{
	BOOL flag = FALSE;
	if (m_handle != NULL)
	{
		flag = ::ReleaseMutex(m_handle);
	}
	return flag;
}

BOOL CAppMutex::Close()
{
	BOOL flag = FALSE;
	if (m_handle != NULL)
	{
		flag = CloseHandle(m_handle);
		m_handle = NULL;
		
	}
	return flag;
}

void CAppMutex::SetMilliSeconds(DWORD dwMilliseconds /*= INFINITE*/)
{
	m_milliSeconds = dwMilliseconds;
}