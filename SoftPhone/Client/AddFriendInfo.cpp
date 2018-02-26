// AddFriendInfo.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "AddFriendInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddFriendInfo dialog


CAddFriendInfo::CAddFriendInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CAddFriendInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddFriendInfo)
	m_name = _T("");
	m_phone = _T("");
	m_addr = _T("");
	m_workUnit = _T("");
	//}}AFX_DATA_INIT
}


void CAddFriendInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddFriendInfo)
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_PHONE, m_phone);
	DDX_Text(pDX, IDC_ADDR, m_addr);
	DDX_Text(pDX, IDC_WORKUNIT, m_workUnit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddFriendInfo, CDialog)
	//{{AFX_MSG_MAP(CAddFriendInfo)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddFriendInfo message handlers

void CAddFriendInfo::OnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	//姓名：只允许英文单词或空格，长度不超过20，不允许为空
	
	m_name.TrimLeft();
	m_name.TrimRight();
	if (m_name.IsEmpty()) {
		MessageBox("姓名不为空!","");
		return;
	}
// 	if (!CheckAlphaOrSpace((char*)((LPCTSTR)m_name))) {
// 		MessageBox("只允许英文单词或空格!","");
// 		return;
/*	}*/
	//电话号码：允许手机号码（11位或12位）或 普通固化号码（8位或12位），不允许为空
	m_phone.TrimLeft();
	m_phone.TrimRight();
	if (m_phone.IsEmpty()) {
		MessageBox("电话号码不为空!","");
		return;
	}
	int nLen = 0;
	nLen = m_phone.GetLength();
// 	if ( !(nLen==8||nLen==11||nLen==12) ){
// 		MessageBox("电话号码长度有错!\n允许手机号码（11位或12位）\n或 普通固化号码（8位或12位）","");
// 		return;
// 	}
	//住址：用户住址，长度不超过100，允许为空
	//工作单位：长度不超过100，允许为空
	
	
	CString strSql;
	strSql.Format("select * from contact where 姓名 = '%s' ",m_name);
	EXESQL(strSql)
		
		if (!g_ado.m_pRecordset->adoEOF) {//竟然无recordsetcount!!
			MessageBox("该姓名已存在!","");
			return;
		}
		else{
			strSql.Format("insert into contact (姓名,电话号码,地址,工作单位) values('%s','%s','%s','%s')",
				m_name,m_phone,m_addr,m_workUnit);
			EXESQL(strSql)
						MessageBox("创建账户成功!","");
//				UpdateList();
			CDialog::OnOK();	
	}	
}

void CAddFriendInfo::OnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
