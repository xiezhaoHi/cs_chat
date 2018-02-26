// AdoOperate.h: interface for the CAdoOperate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOOPERATE_H__9DDD6AA8_F928_4454_971F_C94FA13DF246__INCLUDED_)
#define AFX_ADOOPERATE_H__9DDD6AA8_F928_4454_971F_C94FA13DF246__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define G_ADO g_ado

#define ADO g_ado;\


class CAdoOperate  
{
public:
	CAdoOperate();
	virtual ~CAdoOperate();
	BOOL  ConnectionDb();
	void CloseDbConn();
	static CString VariantToCString(const _variant_t &var);
	void ExeSql(CString strSql);
public:
	//声明一个指向要创建的ADO对象的智能指针
	_ConnectionPtr m_pConnection;
	_RecordsetPtr  m_pRecordset;
	
};

//	CString strSql;
//	strSql.Format("SELECT * FROM ACCOUNT WHERE ACCNAME = '%s' ",m_sAccount);
//	INIT_EXESQL(strSql)

//以下为 数据操作定义一

#define EXESQL(strSql)\
	if (G_ADO.m_pRecordset->State) {\
		G_ADO.m_pRecordset->Close();\
	}\
	G_ADO.m_pRecordset.CreateInstance(__uuidof(Recordset));\
	G_ADO.m_pRecordset->Open(strSql.AllocSysString(),g_ado.m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);\


#define RECORD_COUNT G_ADO.m_pRecordset->RecordCount
#define RECORD_SET G_ADO.m_pRecordset



#endif // !defined(AFX_ADOOPERATE_H__9DDD6AA8_F928_4454_971F_C94FA13DF246__INCLUDED_)
