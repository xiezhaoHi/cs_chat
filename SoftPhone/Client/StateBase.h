// StateBase.h: interface for the CStateBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATEBASE_H__69C9EC16_B902_4024_BEEC_05DD2ED8B879__INCLUDED_)
#define AFX_STATEBASE_H__69C9EC16_B902_4024_BEEC_05DD2ED8B879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;

class CStateBase  
{
public:
	CStateBase();
	virtual ~CStateBase();
	virtual void SetCallID(string callID);
	virtual void SetState(unsigned int state);
	virtual unsigned int GetState();
	virtual string GetCallID();
 	virtual LONG Run(void *vParam)=0;
	char m_ip[20];
	unsigned int m_port;
protected:
	string m_callID;
	unsigned int m_state;
};

#endif // !defined(AFX_STATEBASE_H__69C9EC16_B902_4024_BEEC_05DD2ED8B879__INCLUDED_)
