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
	void SetMilliSeconds(DWORD dwMilliseconds = INFINITE);	//���û������ȴ�ʱ��
	BOOL Lock(DWORD dwMilliseconds = INFINITE);				//��ס
	BOOL UnLock();											//����
	DWORD BeginMutex();										//��ʼʹ�û���
	BOOL Close();											//�رջ���
protected:
	virtual DWORD Process();								//��Ҫ���Ĵ��뺯��
	HANDLE m_handle;
	DWORD m_milliSeconds;
};

#endif//mutex