#if !defined(AFX_SOFTPHONEDLG_H__4662E8EF_36FA_498A_8138_0305189E543A__INCLUDED_)
#define AFX_SOFTPHONEDLG_H__4662E8EF_36FA_498A_8138_0305189E543A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SoftPhoneDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSoftPhoneDlg dialog

class CSoftPhoneDlg : public CDialog
{
// Construction
public:
	CSoftPhoneDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSoftPhoneDlg)
	enum { IDD = IDD_SOFT_PHONE };
	CString	m_userNum;
	CString	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoftPhoneDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTime m_endTime;
	CTime m_startTime;
	// Generated message map functions
	//{{AFX_MSG(CSoftPhoneDlg)
	afx_msg void OnCalling();
	afx_msg void OnButton1();
	afx_msg void OnClean();
	afx_msg void OnBye();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton0();
	virtual BOOL OnInitDialog();
	afx_msg void OnBackSpace();
	afx_msg void OnListen();
	afx_msg void OnAddfriend();
	afx_msg void OnRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	LRESULT OnUIMsg(WPARAM wParam,LPARAM lparam);
	LRESULT OnConnectTime(WPARAM wParam,LPARAM lparam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFTPHONEDLG_H__4662E8EF_36FA_498A_8138_0305189E543A__INCLUDED_)
