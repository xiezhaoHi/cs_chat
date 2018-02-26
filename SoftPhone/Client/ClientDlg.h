// ClientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__B3E40789_7623_418F_A041_D48CD1BF8536__INCLUDED_)
#define AFX_CLIENTDLG_H__B3E40789_7623_418F_A041_D48CD1BF8536__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MessageControl.h"
#include "TestWaveIn.h"
/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor
//	CWaveOut* wave_out;
//	CTestWaveIn* wave_in;
//	CTestWaveIn m_wavein;
// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
	CIPAddressCtrl	m_serverIP;
	CString	m_account;
	CString	m_password;
	CString	m_serverPort;
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CSipMessage m_osipMsg;
	CTestWaveIn test;
//  	CClientSocket m_clientSock;
	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRegistOk();
	afx_msg void OnRegistCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__B3E40789_7623_418F_A041_D48CD1BF8536__INCLUDED_)
