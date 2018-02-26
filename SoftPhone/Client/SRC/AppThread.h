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
					 LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL );//�����߳�
	void Stop();
	HANDLE GetThreadHandle() const;			//����߳̾��
	ULONG GetThreadID() const;				//����߳�ID
	int GetThreadPriority();				//����߳����ȼ�
	bool SetThreadPriority(int nPriority);	//�����߳����ȼ�
	ULONG Suspend();					//�̹߳���
	ULONG Resume();					//�̻߳���
	BOOL Close();
	virtual ULONG ThreadStop();				//ֹͣ�߳�
	virtual ULONG Process() = 0;				//�̴߳�����
protected:
	static ULONG WINAPI ThreadProc(void *lpParameter);				//�̴߳�����	
	bool m_threadState;						//�߳�״̬���Ƿ񴴽���
	ULONG m_threadID;						//�߳�ID
	HANDLE m_threadHandle;					//�߳̾��
	bool m_stopFlag;
};
#endif//_APP_THREAD_H
