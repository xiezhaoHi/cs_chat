#ifndef _APP_THREAD_H
#define _APP_THREAD_H

#include <windows.h>
#include <iostream>

typedef unsigned long ULONG;

class CAppThread
{
public:
	CAppThread();
	virtual ~CAppThread();
	bool Start(ULONG dwCreateFlags = 0,
					 UINT nStackSize = 0,
					 LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL );//创建线程
	void Stop();
	HANDLE GetThreadHandle() const;			//获得线程句柄
	ULONG GetThreadID() const;				//获得线程ID
	int GetThreadPriority();				//获得线程优先级
	bool SetThreadPriority(int nPriority);	//设置线程优先级
	ULONG Suspend();					//线程挂起
	ULONG Resume();					//线程唤醒
	BOOL Close();
	virtual ULONG ThreadStop();				//停止线程
	virtual ULONG Process() = 0;				//线程处理函数
protected:
	static ULONG WINAPI ThreadProc(void *lpParameter);				//线程处理函数	
	bool m_threadState;						//线程状态，是否创建过
	ULONG m_threadID;						//线程ID
	HANDLE m_threadHandle;					//线程句柄
	bool m_stopFlag;
};
#endif//_APP_THREAD_H
