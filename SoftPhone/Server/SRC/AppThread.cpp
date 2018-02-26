#include "AppThread.h"

CAppThread::CAppThread()
{
	m_threadState = false;
	m_stopFlag = false;
	m_threadID = 0;
	m_threadHandle = 0;
}

CAppThread::~CAppThread()
{
	if (m_threadHandle != NULL)
	{
		::CloseHandle(m_threadHandle);
	}
}

BOOL CAppThread::Close()
{
	BOOL flag = FALSE;
	if (m_threadHandle != NULL)
	{
		flag = ::CloseHandle(m_threadHandle);
		m_threadHandle = NULL;
	}
	return flag;
}

bool CAppThread::Start(ULONG dwCreateFlags,
		UINT nStackSize,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{
	m_stopFlag = false;
	if (m_threadState == true)
	{
		return m_threadState;
	}
	m_threadHandle = CreateThread(lpSecurityAttrs,nStackSize,ThreadProc,
					this,dwCreateFlags,&m_threadID);
	if (m_threadHandle == NULL)
	{
		m_threadState = false;
	} 
	else
	{
		m_threadState = true;
	}
	
	return m_threadState;
}

HANDLE CAppThread::GetThreadHandle() const
{
	return m_threadHandle;
}

ULONG CAppThread::GetThreadID() const
{
	return m_threadID;
}

ULONG CAppThread::Suspend()
{
	ULONG tCount;
	if (m_threadID != 0)
	{
		tCount = ::SuspendThread(m_threadHandle);
		if (tCount > 0)
		{
			return tCount;
		}
		else
		{
			return GetLastError();
		}
	}
	return 0;
}

ULONG CAppThread::Resume()
{
	ULONG tCount;
	if (m_threadID != 0)
	{
		tCount = ::ResumeThread(m_threadHandle);
		if (tCount > 0)
		{
			return tCount;
		}
		else
		{
			return GetLastError();
		}
	}
	return 0;
}

ULONG CAppThread::ThreadStop()
{
	m_threadState = false;
	return 0;
}

int CAppThread::GetThreadPriority()
{
	if (m_threadHandle == NULL)
	{
		return 0;
	}
	return ::GetThreadPriority(m_threadHandle);
}

bool CAppThread::SetThreadPriority(int nPriority)
{
	if (m_threadHandle == NULL)
	{
		return false;
	}
	if(TRUE == ::SetThreadPriority(m_threadHandle,nPriority))
	{
		return true;
	}
	return false;
}

// ULONG CAppThread::Process()
// {
//  	::MessageBox(NULL,"BASE","test",MB_OK);
// 	return 0;
// }

ULONG WINAPI CAppThread::ThreadProc(void *lpParameter)
{
	CAppThread *appThread = (CAppThread*)lpParameter;
	return appThread->Process();
}

void CAppThread::Stop()
{
	m_stopFlag = true;
}