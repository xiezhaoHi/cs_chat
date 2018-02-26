// StateManager.h: interface for the CStateManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATEMANAGER_H__5652CD40_603B_4AFB_A7B4_D436E825CB58__INCLUDED_)
#define AFX_STATEMANAGER_H__5652CD40_603B_4AFB_A7B4_D436E825CB58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRC\AppThread.h"

class CStateManager : public CAppThread  
{
public:
	CStateManager();
	virtual ~CStateManager();

};

#endif // !defined(AFX_STATEMANAGER_H__5652CD40_603B_4AFB_A7B4_D436E825CB58__INCLUDED_)
