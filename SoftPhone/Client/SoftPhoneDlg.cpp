// SoftPhoneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "SoftPhoneDlg.h"
#include "AddFriendInfo.h"
#include "FriendList.h"
#include "RecordListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoftPhoneDlg dialog


CSoftPhoneDlg::CSoftPhoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSoftPhoneDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSoftPhoneDlg)
	m_userNum = _T("");
	m_msg = _T("");
	//}}AFX_DATA_INIT
}


void CSoftPhoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoftPhoneDlg)
	DDX_Text(pDX, IDC_USER_NUMBER, m_userNum);
	DDX_Text(pDX, IDC_MSG, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSoftPhoneDlg, CDialog)
	//{{AFX_MSG_MAP(CSoftPhoneDlg)
	ON_BN_CLICKED(IDC_CALLING, OnCalling)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)	
	ON_BN_CLICKED(IDC_CLEAN, OnClean)
	ON_BN_CLICKED(IDC_BYE, OnBye)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON0, OnButton0)
	ON_BN_CLICKED(IDC_BUTTON10, OnBackSpace)
	ON_BN_CLICKED(IDC_LISTEN, OnListen)
	ON_BN_CLICKED(IDC_ADDFRIEND, OnAddfriend)
	ON_MESSAGE(WM_UIMSG,OnUIMsg)
	ON_BN_CLICKED(IDC_RECORD, OnRecord)
	ON_MESSAGE(CONNECT_TIME,OnConnectTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoftPhoneDlg message handlers

void CSoftPhoneDlg::OnCalling() 
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	CMessage *pMsg = new CMessage;
	char *pPhoneNum = new char[20];
	memset(pPhoneNum,'\0',20);
	pPhoneNum = (LPSTR)(LPCSTR)m_userNum;
	pMsg->m_msgType = INVITE_SRV;
	pMsg->m_wparam = (void*)pPhoneNum;
	g_msgCtr.GetMessageQueue()->AddMsg(pMsg);
	
}

void CSoftPhoneDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	m_userNum +="1";
	UpdateData(FALSE);
}

void CSoftPhoneDlg::OnBackSpace() 
{
	// TODO: Add your control notification handler code here
	m_userNum = m_userNum.Left(m_userNum.GetLength()-1);
	UpdateData(FALSE);
}

void CSoftPhoneDlg::OnClean() 
{
	// TODO: Add your control notification handler code here
	m_userNum = "";
	UpdateData(FALSE);
}

void CSoftPhoneDlg::OnBye() 
{
	// TODO: Add your control notification handler code here
	if (g_stateManager.m_callIn != NULL && 
		g_stateManager.m_callIn->GetState() == CCallInState::Ringing)
	{
		g_stateManager.m_callIn->SetState(CCallInState::Cancel);
		g_stateManager.m_callIn->Run(NULL);
	}
	else if (g_stateManager.m_callIn != NULL && 
		g_stateManager.m_callIn->GetState()==CCallInState::WaitACK)
	{
		g_stateManager.m_callIn->SetState(CCallInState::Bye);
		g_stateManager.m_callIn->Run(NULL);
	}
	else if (g_stateManager.m_callIn != NULL && 
		g_stateManager.m_callIn->GetState()==CCallInState::Connecting)
	{
		g_stateManager.m_callIn->SetState(CCallInState::Bye);
		g_stateManager.m_callIn->Run(NULL);
	}
	m_endTime = CTime::GetCurrentTime(); 
	CTimeSpan evalTime = m_endTime - m_startTime  ;
	CString strTime = evalTime.Format("%H:%M:%S");
	CString strstartTime;
	strstartTime = m_startTime.Format("%Y-%m-%d %H:%M:%S");
	CString strSql;
	strSql.Format("insert into callregister (姓名电话,时间,状态,时长) values ('%s','%s','通话','%s')",
		m_userNum,strstartTime,strTime);	
	EXESQL(strSql)	

// 	UpdateData(TRUE);
	CMessage *pMsg = new CMessage;
// 	char *pPhoneNum = new char[20];
// 	memset(pPhoneNum,'\0',20);
// 	pPhoneNum = (LPSTR)(LPCSTR)m_userNum;
	pMsg->m_msgType = CANCEL_SYS;
	pMsg->m_wparam = NULL;
	g_msgCtr.GetMessageQueue()->AddMsg(pMsg);
}

void CSoftPhoneDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	m_userNum +="2";
	UpdateData(FALSE);	
}

void CSoftPhoneDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	m_userNum +="3";
	UpdateData(FALSE);	
}

void CSoftPhoneDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	m_userNum +="4";
	UpdateData(FALSE);	
}

void CSoftPhoneDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	m_userNum +="5";
	UpdateData(FALSE);	
}

void CSoftPhoneDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	m_userNum +="6";
	UpdateData(FALSE);	
}

void CSoftPhoneDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	m_userNum +="7";
	UpdateData(FALSE);	
}

void CSoftPhoneDlg::OnButton8() 
{
	// TODO: Add your control notification handler code here
	m_userNum +="8";
	UpdateData(FALSE);	
}

void CSoftPhoneDlg::OnButton9() 
{
	// TODO: Add your control notification handler code here
	m_userNum +="9";
	UpdateData(FALSE);	
}

void CSoftPhoneDlg::OnButton0() 
{
	// TODO: Add your control notification handler code here
	m_userNum +="0";
	UpdateData(FALSE);	
}

LRESULT CSoftPhoneDlg::OnUIMsg(WPARAM wParam,LPARAM lparam)
{
	m_msg = (char*)wParam;
	UpdateData(FALSE);
	return 0L;
}

BOOL CSoftPhoneDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ui_hwnd = m_hWnd;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSoftPhoneDlg::OnListen() 
{
	// TODO: Add your control notification handler code here
	CMessage *msg = new CMessage;
	msg->m_msgType = LISTEN_SYS;
	msg->m_lparam = NULL;
	msg->m_wparam = NULL;
	g_msgCtr.GetMessageQueue()->AddMsg(msg);	
}

void CSoftPhoneDlg::OnAddfriend() 
{
	// TODO: Add your control notification handler code here
// 	CAddFriendInfo dlg;
// 	dlg.DoModal();
	CFriendList dlg;
	dlg.DoModal();
//	CDialog::OnOK();
}

void CSoftPhoneDlg::OnRecord() 
{
	// TODO: Add your control notification handler code here
	CRecordListDlg dlg;
	dlg.DoModal();
}

LRESULT CSoftPhoneDlg::OnConnectTime(WPARAM wParam,LPARAM lparam)
{
	m_startTime = CTime::GetCurrentTime();
	return 0L;
}
