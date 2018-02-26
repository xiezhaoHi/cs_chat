// stdafx.cpp : source file that includes just the standard includes
//	Client.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

//CSipMessage g_osipMsg;
CMessageControl g_msgCtr;
CClientSocket *g_clientSock;
CStateMacManager g_stateManager;
CTimer g_timer;
user_info *g_userInfo;
HWND m_ui_hwnd;
CAudioControl *g_audioCtrl;
CAdoOperate g_ado;
char g_srvIP[20];
unsigned int g_srvPort;
