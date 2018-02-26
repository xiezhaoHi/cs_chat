// Log.cpp: implementation of the CLog class.
//
//////////////////////////////////////////////////////////////////////
//#define DLLAPI _declspec(dllexport)

#include "Log.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLog::CLog()
{

}

CLog::~CLog()
{

}

void CLog::WriteLog(char* logFileName, char* cppFileName, int errLine, ErrorLevel level, char* errMsg)
{
	if (logFileName == NULL || cppFileName == NULL || errMsg == NULL || errLine <= 0)
	{
		return;
	}
	
	char levelBuf[8] = {0};
	char lineBuf[16] = {0};
	char timeBuf[24] = {0};

	switch(level)
	{
	case Normal:
		strcpy(levelBuf, "正常");
		break;
		
	case Warning:
		strcpy(levelBuf, "警告");
		break;
		
	case Error:
		strcpy(levelBuf, "错误");
		break;
		
	default:
		break;
	}

	sprintf(lineBuf, "第%d行", errLine);

	tm *curTime;
	time_t now;
	time(&now);
	curTime = localtime(&now);
	strftime(timeBuf, 24, "%Y-%m-%d %H:%M:%S", curTime);
	
	::WritePrivateProfileString(timeBuf, "级别", levelBuf, logFileName);
	::WritePrivateProfileString(timeBuf, "文件", cppFileName, logFileName);
	::WritePrivateProfileString(timeBuf, "行数", lineBuf, logFileName);
	::WritePrivateProfileString(timeBuf, "信息", errMsg, logFileName);
}