// FriendList.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "FriendList.h"
#include "AddFriendInfo.h"
#include "ModifyContactDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFriendList dialog


CFriendList::CFriendList(CWnd* pParent /*=NULL*/)
	: CDialog(CFriendList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFriendList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFriendList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFriendList)
	DDX_Control(pDX, IDC_LIST, m_ctlList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFriendList, CDialog)
	//{{AFX_MSG_MAP(CFriendList)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_CHANGE, OnChange)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFriendList message handlers

void CFriendList::OnAdd() 
{
	// TODO: Add your control notification handler code here
	CAddFriendInfo dlg;
  	dlg.DoModal();	
}

BOOL CFriendList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	m_ctlList.SetExtendedStyle(dwStyle);	
	DWORD dwStyle=m_ctlList.GetExtendedStyle();
	dwStyle|= LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT;
    //������չ���
	m_ctlList.SetExtendedStyle(dwStyle);
	
	m_ctlList.InsertColumn(0,"����",LVCFMT_LEFT,85);//�����ͷ����
	m_ctlList.InsertColumn(1,"�绰����",LVCFMT_LEFT,85);//�����ͷ����
	m_ctlList.InsertColumn(2,"��ַ",LVCFMT_LEFT,160);//�����ͷ����
	m_ctlList.InsertColumn(3,"������λ",LVCFMT_LEFT,160);//�����ͷ����	
	UpdateList();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFriendList::UpdateList()
{
	CString strSql;
	strSql.Format("select * from contact");
	EXESQL(strSql)
		
		
		//������¼��ʾ������
	CString sName;
	CString sPhoneNum;
	CString sAddress;
	CString sWorkUnit;
	
	//�������
	_variant_t varValue;
	CString strClass;
	
	CListCtrl*	pList=(CListCtrl*)(GetDlgItem(IDC_LIST));
	pList->DeleteAllItems();
	
	//RECORD_SET->MoveFirst();int n = 0;
	while(!RECORD_SET->adoEOF)
	{		
		int nCount = pList->GetItemCount();	 				
		varValue=RECORD_SET->GetCollect("����");
		sName= CAdoOperate::VariantToCString(varValue);		
		varValue=RECORD_SET->GetCollect("�绰����");
		sPhoneNum= CAdoOperate::VariantToCString(varValue);		
		varValue=RECORD_SET->GetCollect("��ַ");
		sAddress= CAdoOperate::VariantToCString(varValue);				
		varValue=RECORD_SET->GetCollect("������λ");
		sWorkUnit= CAdoOperate::VariantToCString(varValue);				
		pList->InsertItem(nCount,sName);//�������		
		pList->SetItemText(nCount,1,sPhoneNum);
		pList->SetItemText(nCount,2,sAddress);
		pList->SetItemText(nCount,3,sWorkUnit);
		RECORD_SET->MoveNext();
	}
	
}

void CFriendList::OnChange() 
{
	// TODO: Add your control notification handler code here
	CString str;
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	POSITION pos = pList->GetFirstSelectedItemPosition();
	if (pos == NULL)
		MessageBox("��ѡ���޸���Ŀ!\n","");
	else
	{
		while (pos)
		{
			int nItem = pList->GetNextSelectedItem(pos);
			//str.Format("Item %d was selected!\n", nItem);
			// you could do your own processing on nItem here
			str = pList->GetItemText(nItem,0);
			//		str = str.Mid(3,str.GetLength());
			
			CString strSql;
			strSql.Format("select * from contact where ���� = '%s'",str);
			EXESQL(strSql)
				
				CString sName;
			CString sPhoneNum;
			CString sAddress;
			CString sWorkUnit;
			
			//�������
			_variant_t varValue;
			CString strClass;
			
			varValue=RECORD_SET->GetCollect("����");
			sName= CAdoOperate::VariantToCString(varValue);
			
			varValue=RECORD_SET->GetCollect("�绰����");
			sPhoneNum= CAdoOperate::VariantToCString(varValue);
			
			varValue=RECORD_SET->GetCollect("��ַ");
			sAddress= CAdoOperate::VariantToCString(varValue);		
			
			varValue=RECORD_SET->GetCollect("������λ");
			sWorkUnit= CAdoOperate::VariantToCString(varValue);
			
			CModifyContactDlg dlg;
			dlg.m_sName = sName;
			dlg.m_sPhone = sPhoneNum;
			dlg.m_sAddress = sAddress;
			dlg.m_sWorkUnit = sWorkUnit;
			
			UpdateData(FALSE);
			dlg.DoModal();			
		}
	}	
	UpdateList();
}

void CFriendList::OnDelete() 
{
	// TODO: Add your control notification handler code here
	CString str;
	CListCtrl* pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	POSITION pos = pList->GetFirstSelectedItemPosition();
	if (pos == NULL)
		MessageBox("��ѡ��ɾ����Ŀ!\n","");
	else
	{
		while (pos)
		{
			int nItem = pList->GetNextSelectedItem(pos);
			str = pList->GetItemText(nItem,0);
			
			if (IDOK == MessageBox("�Ƿ�ɾ���ü�¼?","",MB_OKCANCEL | MB_ICONWARNING)) {
				CString strSql;
				strSql.Format("delete from contact where ���� = '%s'",str);
				EXESQL(strSql)
					UpdateList();
			}	
		}
	}
	UpdateList();
}
