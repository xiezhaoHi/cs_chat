// ModifyContactDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "ModifyContactDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyContactDlg dialog


CModifyContactDlg::CModifyContactDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyContactDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyContactDlg)
	m_sName = _T("");
	m_sPhone = _T("");
	m_sAddress = _T("");
	m_sWorkUnit = _T("");
	//}}AFX_DATA_INIT
}


void CModifyContactDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyContactDlg)
	DDX_Text(pDX, IDC_EDIT_NAME, m_sName);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_sPhone);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_sAddress);
	DDX_Text(pDX, IDC_EDIT_WORK_UNIT, m_sWorkUnit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyContactDlg, CDialog)
	//{{AFX_MSG_MAP(CModifyContactDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyContactDlg message handlers
