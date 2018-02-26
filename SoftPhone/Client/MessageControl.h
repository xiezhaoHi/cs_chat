// MessageControl.h: interface for the CMessageControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGECONTROL_H__6657174C_6AEA_4550_8037_3B8C8A36F3B6__INCLUDED_)
#define AFX_MESSAGECONTROL_H__6657174C_6AEA_4550_8037_3B8C8A36F3B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRC\AppThread.h"
//#include "StateMacManager.h"


class CMessageControl : public CAppThread  
{
public:
	CMessageControl();
	virtual ~CMessageControl();
	CMsgQueue* GetMessageQueue();
	ULONG Process();
//	friend class CStateMacManager;
protected:
	CMsgQueue *m_msgQueue;
};

#endif // !defined(AFX_MESSAGECONTROL_H__6657174C_6AEA_4550_8037_3B8C8A36F3B6__INCLUDED_)
