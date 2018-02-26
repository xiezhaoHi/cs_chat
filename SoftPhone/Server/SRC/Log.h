// Log.h: interface for the CLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__E20EF9D7_348A_4195_8701_F6162E8BDB8D__INCLUDED_)
#define AFX_LOG_H__E20EF9D7_348A_4195_8701_F6162E8BDB8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "WinPre.h"

enum ErrorLevel
{
	Normal,
	Warning,
	Error
};

class CLog  
{
public:
	CLog();
	virtual ~CLog();
	static void WriteLog(char* logFileName, 
						 char* cppFileName, 
						 int line, 
						 ErrorLevel errLevel, 
						 char* errMsg);
};

#define ERRLOG(logFileName,errLevel,errMsg) CLog::WriteLog(logFileName, __FILE__, __LINE__, errLevel, errMsg);

#endif // !defined(AFX_LOG_H__E20EF9D7_348A_4195_8701_F6162E8BDB8D__INCLUDED_)
