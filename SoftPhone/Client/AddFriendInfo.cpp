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
	//������ֻ����Ӣ�ĵ��ʻ�ո񣬳��Ȳ�����20��������Ϊ��
	
	m_name.TrimLeft();
	m_name.TrimRight();
	if (m_name.IsEmpty()) {
		MessageBox("������Ϊ��!","");
		return;
	}
// 	if (!CheckAlphaOrSpace((char*)((LPCTSTR)m_name))) {
// 		MessageBox("ֻ����Ӣ�ĵ��ʻ�ո�!","");
// 		return;
/*	}*/
	//�绰���룺�����ֻ����루11λ��12λ���� ��ͨ�̻����루8λ��12λ����������Ϊ��
	m_phone.TrimLeft();
	m_phone.TrimRight();
	if (m_phone.IsEmpty()) {
		MessageBox("�绰���벻Ϊ��!","");
		return;
	}
	int nLen = 0;
	nLen = m_phone.GetLength();
// 	if ( !(nLen==8||nLen==11||nLen==12) ){
// 		MessageBox("�绰���볤���д�!\n�����ֻ����루11λ��12λ��\n�� ��ͨ�̻����루8λ��12λ��","");
// 		return;
// 	}
	//סַ���û�סַ�����Ȳ�����100������Ϊ��
	//������λ�����Ȳ�����100������Ϊ��
	
	
	CString strSql;
	strSql.Format("select * from contact where ���� = '%s' ",m_name);
	EXESQL(strSql)
		
		if (!g_ado.m_pRecordset->adoEOF) {//��Ȼ��recordsetcount!!
			MessageBox("�������Ѵ���!","");
			return;
		}
		else{
			strSql.Format("insert into contact (����,�绰����,��ַ,������λ) values('%s','%s','%s','%s')",
				m_name,m_phone,m_addr,m_workUnit);
			EXESQL(strSql)
						MessageBox("�����˻��ɹ�!","");
//				UpdateList();
			CDialog::OnOK();	
	}	
}

void CAddFriendInfo::OnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
