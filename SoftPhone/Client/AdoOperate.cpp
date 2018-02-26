// AdoOperate.cpp: implementation of the CAdoOperate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "AdoOperate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoOperate::CAdoOperate()
{

}

CAdoOperate::~CAdoOperate()
{

}

BOOL CAdoOperate::ConnectionDb()
{
	//创建ADO连接

	m_pConnection=NULL;
	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pRecordset=NULL;	
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	CString strSQL;
	strSQL="Provider=Microsoft.Jet.OLEDB.4.0;Data Source=DataInfo.mdb";
	//在ADO操作中建议语句中要常用try...catch()来捕获错误信息，
	//因为它有时会经常出现一些想不到的错误songMp3
	try                 
	{	
		//打开mdb库perConnection.mdb
		m_pConnection->Open((_bstr_t)strSQL,"","",adModeUnknown);
	}
	catch (_com_error e)
	{
		CString strError;
		strError.Format("连接数据库失败. 错误信息： %s",e.ErrorMessage());
		AfxMessageBox(strError);
		return FALSE;
	}
	return TRUE;	
}

void CAdoOperate::CloseDbConn()
{
	if(m_pConnection->State)
	{
		m_pConnection->Close();
		m_pConnection=NULL;
	}
}

CString CAdoOperate::VariantToCString(const _variant_t &var)
{
	CString strValue;	
	switch (var.vt)
	{
	case VT_BSTR://字符串
	case VT_LPSTR:
	case VT_LPWSTR:
		strValue = (LPCTSTR)(_bstr_t)var;
		break;
	case VT_I1://无符号字符
	case VT_UI1:
		strValue.Format("%d", var.bVal);
		break;
	case VT_I2://短整型
		strValue.Format("%d", var.iVal);
		break;
	case VT_UI2://无符号短整型
		strValue.Format("%d", var.uiVal);
		break;
	case VT_INT://整型
		strValue.Format("%d", var.intVal);
		break;
	case VT_I4: //整型
	case VT_I8: //长整型
		 strValue.Format("%d", var.lVal);
		break;
	case VT_UINT://无符号整型
		strValue.Format("%d", var.uintVal);
		break;
	case VT_UI4: //无符号整型
	case VT_UI8: //无符号长整型
		 strValue.Format("%d", var.ulVal);
		 break;
	case VT_VOID:
		strValue.Format("%8x", var.byref);
		break;
	case VT_R4://浮点型
		strValue.Format("%.4f", var.fltVal);
		break;
	case VT_R8://双精度型
		strValue.Format("%.8f", var.dblVal);
		break;
	case VT_DECIMAL: //小数
		strValue.Format("%.8f", (double)var);
		break;
	case VT_CY:
		{
			COleCurrency cy = var.cyVal;
			strValue = cy.Format();
		}
		break;
	case VT_BLOB:
	case VT_BLOB_OBJECT:
	case 0x2011:
		strValue = "[BLOB]";
		break;
	case VT_BOOL://布尔型		
		strValue = var.boolVal ? "TRUE" : "FALSE";
		break;
	case VT_DATE: //日期型
		{
			DATE dt = var.date;
			COleDateTime da = COleDateTime(dt); 
			strValue = da.Format("%Y-%m-%d %H:%M:%S");
		}
		break;
	case VT_NULL://NULL值
	case VT_EMPTY://空
		 strValue = "";
		 break;
	case VT_UNKNOWN://未知类型
	default:
		strValue = "UN_KNOW";
		break;
	}
	return strValue;
	

}

void CAdoOperate::ExeSql(CString strSql)
{
	if (m_pRecordset->State) {
		m_pRecordset->Close();
	}
	m_pRecordset->Open(strSql.AllocSysString(),m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	
}