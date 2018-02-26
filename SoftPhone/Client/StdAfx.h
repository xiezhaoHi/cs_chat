// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__7155A564_F4B3_495F_B8CD_D26D299BE6E2__INCLUDED_)
#define AFX_STDAFX_H__7155A564_F4B3_495F_B8CD_D26D299BE6E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#import "C:\Program Files\Common Files\System\ado\msado15.dll" rename_namespace("ADOCG") rename("EOF","adoEOF")
using namespace ADOCG;

#include "SRC\SocketStream.h"
#include "SRC\IOSocket.h"
#include "SRC\MessageQueue.h"
#include "SRC\AppThread.h"
#include "SipMessage.h"
#include "ClientSocket.h"
#include "MessageControl.h"
#include "StateMacManager.h"
#include "Timer.h"
#include "AudioControl.h"
#include "AdoOperate.h"

#define SERVER_PORT 8000
#define BUFFER_SIZE 8192
#define IP_LEN 18

enum StateMac{REGISER = 1,CALLOUT,CALLIN,MSGACK,MSG200,MSG302,MSG180,MSG400};
//////////////////////////////////////////////////////////////////////////
//消息类型定义
#define RegistMsg WM_USER + 1
#define STATECHANGE WM_USER + 2
#define KillMe WM_USER + 3
#define MSG200_SYS WM_USER + 4
#define MSG400_SYS WM_USER + 5
#define INVITE_SRV WM_USER + 6
#define CALLIN_SYS WM_USER + 7
#define MSG302_SYS WM_USER + 8
#define MSG180_SYS WM_USER + 9
#define LISTEN_SYS WM_USER + 10
#define MSGACK_SYS WM_USER + 11
#define CANCEL_SYS WM_USER + 12
#define CANCEL_RCV WM_USER + 13
#define CMD487_RCV WM_USER + 15
#define BYE_RCV WM_USER + 14
#define CONNECT_TIME WM_USER + 16
#define WM_UIMSG WM_USER + 100

typedef struct  
{
	char *name;
	char *pwd;
}user_info;

//extern CSipMessage g_osipMsg;
extern CMessageControl g_msgCtr;
extern CClientSocket *g_clientSock;
extern CStateMacManager g_stateManager;
extern CTimer g_timer;
extern user_info *g_userInfo;
extern HWND m_ui_hwnd;
extern CAudioControl *g_audioCtrl;
extern CAdoOperate g_ado;
extern char g_srvIP[20];
extern unsigned int g_srvPort;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__7155A564_F4B3_495F_B8CD_D26D299BE6E2__INCLUDED_)
