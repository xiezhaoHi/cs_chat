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
		
		
		//遍历记录集示例代码
		CString sName;
	CString sPhoneNum;
	CString sAddress;
	CString sWorkUnit;
	
	//定义变量
	_variant_t varValue;
	CString strClass;
	
	CListCtrl*	pList=(CListCtrl*)(GetDlgItem(IDC_LIST));
//	pList->DeleteAllItems();
//	m_ctlList.DeleteAllItems();	
	//RECORD_SET->MoveFirst();int n = 0;
	while(!RECORD_SET->adoEOF){
		//		strClass.Format("%d",n);
		
		int nCount = pList->GetItemCount();	 
		
		//姓名/电话： 如果此电话号码在通讯簿中，则直接显示用户名；如果电话号码在通讯簿中不存在，则直接显示电话号码
		//时间：此次通话记录发生的时间，年－月－日 时：分：秒 格式存储
		//状态： 分为：呼出（主动呼叫别人），呼入（其他用户呼入），未接（其他用户呼入，但没接听）三种。
		//时长：具体通话的时间，表示为： 时：分：秒。
		
		varValue=RECORD_SET->GetCollect("姓名电话");
		sName= CAdoOperate::VariantToCString(varValue);
		
		varValue=RECORD_SET->GetCollect("时间");
		sPhoneNum= CAdoOperate::VariantToCString(varValue);
		
		varValue=RECORD_SET->GetCollect("状态");
		sAddress= CAdoOperate::VariantToCString(varValue);		
		
		varValue=RECORD_SET->GetCollect("时长");
		sWorkUnit= CAdoOperate::VariantToCString(varValue);
		
		
		pList->InsertItem(nCount,sName);//添加新行
		
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
    //设置扩展风格
	m_ctlList.SetExtendedStyle(dwStyle);	
	//姓名/电话： 如果此电话号码在通讯簿中，则直接显示用户名；如果电话号码在通讯簿中不存在，则直接显示电话号码
	//时间：此次通话记录发生的时间，年－月－日 时：分：秒 格式存储
	//状态： 分为：呼出（主动呼叫别人），呼入（其他用户呼入），未接（其他用户呼入，但没接听）三种。
	//时长：具体通话的时间，表示为： 时：分：秒。
	
	m_ctlList.InsertColumn(0,"姓名/电话",LVCFMT_LEFT,80);//插入表头标题
	m_ctlList.InsertColumn(1,"时间",LVCFMT_LEFT,150);//插入表头标题
	m_ctlList.InsertColumn(2,"状态",LVCFMT_LEFT,80);//插入表头标题
	m_ctlList.InsertColumn(3,"时长",LVCFMT_LEFT,80);//插入表头标题
	
	UpdateList();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecordListDlg::UpdateList()
{
	CString strSql;
	strSql.Format("select * from callregister");
	EXESQL(strSql)
		
		
		//遍历记录集示例代码
		CString sName;
	CString sPhoneNum;
	CString sAddress;
	CString sWorkUnit;
	
	//定义变量
	_variant_t varValue;
	CString strClass;
	
	CListCtrl*	pList=(CListCtrl*)(GetDlgItem(IDC_LIST));
	pList->DeleteAllItems();
	
	//RECORD_SET->MoveFirst();int n = 0;
	while(!RECORD_SET->adoEOF){
		//		strClass.Format("%d",n);
		
		int nCount = pList->GetItemCount();	 
		
		//姓名/电话： 如果此电话号码在通讯簿中，则直接显示用户名；如果电话号码在通讯簿中不存在，则直接显示电话号码
		//时间：此次通话记录发生的时间，年－月－日 时：分：秒 格式存储
		//状态： 分为：呼出（主动呼叫别人），呼入（其他用户呼入），未接（其他用户呼入，但没接听）三种。
		//时长：具体通话的时间，表示为： 时：分：秒。
		
		varValue=RECORD_SET->GetCollect("姓名电话");
		sName= CAdoOperate::VariantToCString(varValue);
		
		varValue=RECORD_SET->GetCollect("时间");
		sPhoneNum= CAdoOperate::VariantToCString(varValue);
		
		varValue=RECORD_SET->GetCollect("状态");
		sAddress= CAdoOperate::VariantToCString(varValue);		
		
		varValue=RECORD_SET->GetCollect("时长");
		sWorkUnit= CAdoOperate::VariantToCString(varValue);
		
		
		pList->InsertItem(nCount,sName);//添加新行
		
		pList->SetItemText(nCount,1,sPhoneNum);
		pList->SetItemText(nCount,2,sAddress);
		pList->SetItemText(nCount,3,sWorkUnit);
		
		//		MessageBox(strClass);
		RECORD_SET->MoveNext();
		//		n++;
	}
}
