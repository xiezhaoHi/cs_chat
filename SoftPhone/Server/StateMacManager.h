// StateMacManager.h: interface for the CStateMacManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATEMACMANAGER_H__FF904F22_125E_4E3C_9FF7_7A58E8267C5E__INCLUDED_)
#define AFX_STATEMACMANAGER_H__FF904F22_125E_4E3C_9FF7_7A58E8267C5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRC\AppThread.h"
#include "RegStateMac.h"
#include <map>
#include <string>

using namespace std;

typedef map<string, CRegStateMac*> RegStateMacMap;

class CStateMacManager : public CAppThread  
{
public:
	CStateMacManager();
	virtual ~CStateMacManager();
	bool CreateRegStateMac(string callID);
	bool EraseRegStateMac(string callID);
	bool FindRegStateMac(string callID);
	CRegStateMac* GetRegStateMac(string callID);
protected:
	ULONG Process();
	RegStateMacMap m_RegStateMacMap;
};

#endif // !defined(AFX_STATEMACMANAGER_H__FF904F22_125E_4E3C_9FF7_7A58E8267C5E__INCLUDED_)
