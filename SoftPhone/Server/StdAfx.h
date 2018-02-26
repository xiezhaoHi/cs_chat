// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__188F8B3F_07C2_4B0E_BABE_FD19D3B74701__INCLUDED_)
#define AFX_STDAFX_H__188F8B3F_07C2_4B0E_BABE_FD19D3B74701__INCLUDED_

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

#include "SRC\SocketStream.h"
#include "SRC\IOSocket.h"
#include "SRC\MessageQueue.h"
#include "MessageControl.h"
#include "ServerSocket.h"
#include "StateMacManager.h"
#include "Timer.h"
#include <list>

typedef struct  
{
	char username[20];
	char ip[20];
	unsigned int port;
	char call_id[40];
}user_info;

typedef std::list<user_info> user_list;

extern CMessageControl g_msgCtr;
extern CServerSocket *g_serverSock;
extern CStateMacManager g_stateMacManager;
extern CTimer g_timer;
extern user_list g_userList;
extern HWND g_hwnd;


#define SERVER_PORT 8000
#define BUFFER_SIZE 8192
#define IP_LEN 18
enum ServerState{REGISTER_MSG = 1,INVITE_MSG};

//////////////////////////////////////////////////////////////////////////
//消息类型定义
#define REGISTER_SYS WM_USER + REGISTER_MSG
#define INVOID_SYS WM_USER + INVITE_MSG
#define STATECHANGE WM_USER + 3
#define KILLME WM_USER + 4
#define WM_UPDATEUSERLIST WM_USER + 100


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__188F8B3F_07C2_4B0E_BABE_FD19D3B74701__INCLUDED_)
