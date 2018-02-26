// RecordListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "RecordListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordListDlg dialog


CRecordListDlg::CRecordListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecordListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecordListDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRecordListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecordListDlg)
	DDX_Control(pDX, IDC_LIST, m_ctlList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecordListDlg, CDialog)
	//{{AFX_MSG_MAP(CRecordListDlg)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordListDlg message handlers

void CRecordListDlg::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	CString strSql;
	strSql.Format("select * from callregister");
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
//	pList->DeleteAllItems();
//	m_ctlList.DeleteAllItems();	
	//RECORD_SET->MoveFirst();int n = 0;
	while(!RECORD_SET->adoEOF){
		//		strClass.Format("%d",n);
		
		int nCount = pList->GetItemCount();	 
		
		//����/�绰�� ����˵绰������ͨѶ���У���ֱ����ʾ�û���������绰������ͨѶ���в����ڣ���ֱ����ʾ�绰����
		//ʱ�䣺�˴�ͨ����¼������ʱ�䣬�꣭�£��� ʱ���֣��� ��ʽ�洢
		//״̬�� ��Ϊ���������������б��ˣ������루�����û����룩��δ�ӣ������û����룬��û���������֡�
		//ʱ��������ͨ����ʱ�䣬��ʾΪ�� ʱ���֣��롣
		
		varValue=RECORD_SET->GetCollect("�����绰");
		sName= CAdoOperate::VariantToCString(varValue);
		
		varValue=RECORD_SET->GetCollect("ʱ��");
		sPhoneNum= CAdoOperate::VariantToCString(varValue);
		
		varValue=RECORD_SET->GetCollect("״̬");
		sAddress= CAdoOperate::VariantToCString(varValue);		
		
		varValue=RECORD_SET->GetCollect("ʱ��");
		sWorkUnit= CAdoOperate::VariantToCString(varValue);
		
		
		pList->InsertItem(nCount,sName);//�������
		
		pList->SetItemText(nCount,1,sPhoneNum);
		pList->SetItemText(nCount,2,sAddress);
		pList->SetItemText(nCount,3,sWorkUnit);
		
		//		MessageBox(strClass);
		RECORD_SET->MoveNext();
		//		n++;
	}
		
}

BOOL CRecordListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	DWORD dwStyle=m_ctlList.GetExtendedStyle();
	dwStyle|= LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT;
    //������չ���
	m_ctlList.SetExtendedStyle(dwStyle);	
	//����/�绰�� ����˵绰������ͨѶ���У���ֱ����ʾ�û���������绰������ͨѶ���в����ڣ���ֱ����ʾ�绰����
	//ʱ�䣺�˴�ͨ����¼������ʱ�䣬�꣭�£��� ʱ���֣��� ��ʽ�洢
	//״̬�� ��Ϊ���������������б��ˣ������루�����û����룩��δ�ӣ������û����룬��û���������֡�
	//ʱ��������ͨ����ʱ�䣬��ʾΪ�� ʱ���֣��롣
	
	m_ctlList.InsertColumn(0,"����/�绰",LVCFMT_LEFT,80);//�����ͷ����
	m_ctlList.InsertColumn(1,"ʱ��",LVCFMT_LEFT,150);//�����ͷ����
	m_ctlList.InsertColumn(2,"״̬",LVCFMT_LEFT,80);//�����ͷ����
	m_ctlList.InsertColumn(3,"ʱ��",LVCFMT_LEFT,80);//�����ͷ����
	
	UpdateList();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecordListDlg::UpdateList()
{
	CString strSql;
	strSql.Format("select * from callregister");
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
	while(!RECORD_SET->adoEOF){
		//		strClass.Format("%d",n);
		
		int nCount = pList->GetItemCount();	 
		
		//����/�绰�� ����˵绰������ͨѶ���У���ֱ����ʾ�û���������绰������ͨѶ���в����ڣ���ֱ����ʾ�绰����
		//ʱ�䣺�˴�ͨ����¼������ʱ�䣬�꣭�£��� ʱ���֣��� ��ʽ�洢
		//״̬�� ��Ϊ���������������б��ˣ������루�����û����룩��δ�ӣ������û����룬��û���������֡�
		//ʱ��������ͨ����ʱ�䣬��ʾΪ�� ʱ���֣��롣
		
		varValue=RECORD_SET->GetCollect("�����绰");
		sName= CAdoOperate::VariantToCString(varValue);
		
		varValue=RECORD_SET->GetCollect("ʱ��");
		sPhoneNum= CAdoOperate::VariantToCString(varValue);
		
		varValue=RECORD_SET->GetCollect("״̬");
		sAddress= CAdoOperate::VariantToCString(varValue);		
		
		varValue=RECORD_SET->GetCollect("ʱ��");
		sWorkUnit= CAdoOperate::VariantToCString(varValue);
		
		
		pList->InsertItem(nCount,sName);//�������
		
		pList->SetItemText(nCount,1,sPhoneNum);
		pList->SetItemText(nCount,2,sAddress);
		pList->SetItemText(nCount,3,sWorkUnit);
		
		//		MessageBox(strClass);
		RECORD_SET->MoveNext();
		//		n++;
	}
}
