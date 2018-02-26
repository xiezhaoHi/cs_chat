// StateMacManager.h: interface for the CStateMacManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATEMACMANAGER_H__547DB327_57B8_4526_B54E_E20762FD06D4__INCLUDED_)
#define AFX_STATEMACMANAGER_H__547DB327_57B8_4526_B54E_E20762FD06D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRC\AppThread.h"
#include "StateBase.h"
#include "RegState.h"
#include "CallOutState.h"
#include "CallInState.h"
#include "MessageControl.h"
#include <map>

using namespace std;

//typedef map<string,CStateBase*> StateMacMap;

class CStateMacManager : public CAppThread  
{
public:
	CStateMacManager();
	virtual ~CStateMacManager();
	bool CreateStateMac(CStateBase *pState);
	bool ReleaseStateMac(string callID);
	bool FindStateMac(string callID);
	CStateBase* GetStateMac(string callID);
	friend class CMessageControl;
	CCallInState* GetCallInState();
	ULONG Process();
/*private:*/
	CRegState *m_pRegState;
	CCallOutState *m_callOut;
	CCallInState *m_callIn;
};

#endif // !defined(AFX_STATEMACMANAGER_H__547DB327_57B8_4526_B54E_E20762FD06D4__INCLUDED_)
