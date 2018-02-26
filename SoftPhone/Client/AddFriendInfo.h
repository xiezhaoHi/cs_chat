#if !defined(AFX_ADDFRIENDINFO_H__F7C1E1F4_800B_4D45_86F8_180E98711DB2__INCLUDED_)
#define AFX_ADDFRIENDINFO_H__F7C1E1F4_800B_4D45_86F8_180E98711DB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddFriendInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddFriendInfo dialog

class CAddFriendInfo : public CDialog
{
// Construction
public:
	CAddFriendInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddFriendInfo)
	enum { IDD = IDD_ADD_USER };
	CString	m_name;
	CString	m_phone;
	CString	m_addr;
	CString	m_workUnit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddFriendInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddFriendInfo)
	afx_msg void OnSave();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDFRIENDINFO_H__F7C1E1F4_800B_4D45_86F8_180E98711DB2__INCLUDED_)
