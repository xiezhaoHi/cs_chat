#ifndef _APP_MUTEX_H
#define _APP_MUTEX_H

#include <windows.h>

class CAppMutex
{
public:
	CAppMutex(LPSECURITY_ATTRIBUTES lpMutexAttributes = NULL,
			  BOOL bInitialOwner = FALSE,
			  LPCTSTR lpName = NULL);
	~CAppMutex();
	void SetMilliSeconds(DWORD dwMilliseconds = INFINITE);	//设置互斥量等待时间
	BOOL Lock(DWORD dwMilliseconds = INFINITE);				//锁住
	BOOL UnLock();											//解锁
	DWORD BeginMutex();										//开始使用互斥
	BOOL Close();											//关闭互斥
protected:
	virtual DWORD Process();								//需要锁的代码函数
	HANDLE m_handle;
	DWORD m_milliSeconds;
};

#endif//mutex