#if !defined(AFX_RECORDLISTDLG_H__3A2CA8F0_2C1C_4671_A836_46C68A7F4559__INCLUDED_)
#define AFX_RECORDLISTDLG_H__3A2CA8F0_2C1C_4671_A836_46C68A7F4559__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecordListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecordListDlg dialog

class CRecordListDlg : public CDialog
{
// Construction
public:
	void UpdateList();
	CRecordListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRecordListDlg)
	enum { IDD = IDD_CALL_REGISTER };
	CListCtrl	m_ctlList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRecordListDlg)
	afx_msg void OnBtnDel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDLISTDLG_H__3A2CA8F0_2C1C_4671_A836_46C68A7F4559__INCLUDED_)
