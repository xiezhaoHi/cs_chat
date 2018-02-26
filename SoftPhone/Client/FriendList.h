#if !defined(AFX_FRIENDLIST_H__AE6CE7B0_05FC_4553_9D63_3BDFEF03B19F__INCLUDED_)
#define AFX_FRIENDLIST_H__AE6CE7B0_05FC_4553_9D63_3BDFEF03B19F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FriendList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFriendList dialog

class CFriendList : public CDialog
{
// Construction
public:
	virtual void UpdateList();
	CFriendList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFriendList)
	enum { IDD = IDD_DIALOG_LIST };
	CListCtrl	m_ctlList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFriendList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFriendList)
	afx_msg void OnAdd();
	virtual BOOL OnInitDialog();
	afx_msg void OnChange();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRIENDLIST_H__AE6CE7B0_05FC_4553_9D63_3BDFEF03B19F__INCLUDED_)
