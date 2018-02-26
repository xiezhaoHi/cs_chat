// StateBase.cpp: implementation of the CStateBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "StateBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStateBase::CStateBase()
{

}

CStateBase::~CStateBase()
{

}

void CStateBase::SetCallID(string callID)
{
	m_callID = callID;
}

void CStateBase::SetState(unsigned int state)
{
	m_state = state;
}

unsigned int CStateBase::GetState()
{
	return m_state;
}

string CStateBase::GetCallID()
{
	return m_callID;
}