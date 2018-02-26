// ServerDlg.h : header file
//

#if !defined(AFX_SERVERDLG_H__29EFE69E_3DAB_4CD6_AF49_F976E987CE28__INCLUDED_)
#define AFX_SERVERDLG_H__29EFE69E_3DAB_4CD6_AF49_F976E987CE28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MessageControl.h"
#include "ServerSocket.h"
#include "StateMacManager.h"

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog



class CServerDlg : public CDialog
{
// Construction
public:
//  	BOOL UpdateUserList(WPARAM wparam,LPARAM lparam);
	CServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CServerDlg)
	enum { IDD = IDD_SERVER_DIALOG };
	CListCtrl	m_userList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	
	// Generated message map functions
	//{{AFX_MSG(CServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnRestart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	LRESULT UpdateUserList(WPARAM wparam,LPARAM lparam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDLG_H__29EFE69E_3DAB_4CD6_AF49_F976E987CE28__INCLUDED_)
