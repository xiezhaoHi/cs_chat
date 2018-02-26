#if !defined(AFX_MODIFYCONTACTDLG_H__CBB027C6_15E1_4EAD_9F3B_E22DEF1F9724__INCLUDED_)
#define AFX_MODIFYCONTACTDLG_H__CBB027C6_15E1_4EAD_9F3B_E22DEF1F9724__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyContactDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifyContactDlg dialog

class CModifyContactDlg : public CDialog
{
// Construction
public:
	CModifyContactDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyContactDlg)
	enum { IDD = IDD_MODIFY_CONTACT };
	CString	m_sName;
	CString	m_sPhone;
	CString	m_sAddress;
	CString	m_sWorkUnit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyContactDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyContactDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYCONTACTDLG_H__CBB027C6_15E1_4EAD_9F3B_E22DEF1F9724__INCLUDED_)
