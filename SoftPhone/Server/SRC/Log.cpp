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
		strcpy(levelBuf, "����");
		break;
		
	case Warning:
		strcpy(levelBuf, "����");
		break;
		
	case Error:
		strcpy(levelBuf, "����");
		break;
		
	default:
		break;
	}

	sprintf(lineBuf, "��%d��", errLine);

	tm *curTime;
	time_t now;
	time(&now);
	curTime = localtime(&now);
	strftime(timeBuf, 24, "%Y-%m-%d %H:%M:%S", curTime);
	
	::WritePrivateProfileString(timeBuf, "����", levelBuf, logFileName);
	::WritePrivateProfileString(timeBuf, "�ļ�", cppFileName, logFileName);
	::WritePrivateProfileString(timeBuf, "����", lineBuf, logFileName);
	::WritePrivateProfileString(timeBuf, "��Ϣ", errMsg, logFileName);
}