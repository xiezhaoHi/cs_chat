// ServerControl.h: interface for the CServerControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SERVERCONTROL_H__AFDBA9F2_F6DC_4795_9AE9_093A49F7D310__INCLUDED_)
#define AFX_SERVERCONTROL_H__AFDBA9F2_F6DC_4795_9AE9_093A49F7D310__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SRC\AppThread.h"

class CServerControl : public CAppThread  
{
public:
	CServerControl();
	virtual ~CServerControl();
	bool Start();
protected:
};

#endif // !defined(AFX_SERVERCONTROL_H__AFDBA9F2_F6DC_4795_9AE9_093A49F7D310__INCLUDED_)
