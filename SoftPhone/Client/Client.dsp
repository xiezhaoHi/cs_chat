# Microsoft Developer Studio Project File - Name="Client" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Client - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Client.mak" CFG="Client - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Client - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Client - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Client - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 osip_parse2_r.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Client - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /ZI /Od /I "SRC" /I "..\libosip2.20\osip2fsm\include" /I "..\libosip2.20\osip2parse\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 osip_parse2_d.lib g7231d.lib va_g729a.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"LIB"
# SUBTRACT LINK32 /map

!ENDIF 

# Begin Target

# Name "Client - Win32 Release"
# Name "Client - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddFriendInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\AdoOperate.cpp
# End Source File
# Begin Source File

SOURCE=.\SRC\AppMutex.cpp
# End Source File
# Begin Source File

SOURCE=.\SRC\AppThread.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioCode.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioControl.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\CallInState.cpp
# End Source File
# Begin Source File

SOURCE=.\CallOutState.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.cpp
# End Source File
# Begin Source File

SOURCE=.\Client.rc
# End Source File
# Begin Source File

SOURCE=.\ClientDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\FriendList.cpp
# End Source File
# Begin Source File

SOURCE=.\SRC\IOSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageControl.cpp
# End Source File
# Begin Source File

SOURCE=.\SRC\MessageQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\ModifyContactDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PhoneWaveIn.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RegState.cpp
# End Source File
# Begin Source File

SOURCE=.\SipMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\SRC\SocketStream.cpp
# End Source File
# Begin Source File

SOURCE=.\SoftPhoneDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StateBase.cpp
# End Source File
# Begin Source File

SOURCE=.\StateMacManager.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TestWaveIn.cpp
# End Source File
# Begin Source File

SOURCE=.\SRC\Time_Value.cpp
# End Source File
# Begin Source File

SOURCE=.\SRC\Timer.cpp
# End Source File
# Begin Source File

SOURCE=.\SRC\TimerQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\SRC\TimerSession.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveIn.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveOut.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddFriendInfo.h
# End Source File
# Begin Source File

SOURCE=.\AdoOperate.h
# End Source File
# Begin Source File

SOURCE=.\SRC\AppMutex.h
# End Source File
# Begin Source File

SOURCE=.\SRC\AppThread.h
# End Source File
# Begin Source File

SOURCE=.\AudioCode.h
# End Source File
# Begin Source File

SOURCE=.\AudioControl.h
# End Source File
# Begin Source File

SOURCE=.\AudioSocket.h
# End Source File
# Begin Source File

SOURCE=.\CallInState.h
# End Source File
# Begin Source File

SOURCE=.\CallOutState.h
# End Source File
# Begin Source File

SOURCE=.\Client.h
# End Source File
# Begin Source File

SOURCE=.\ClientDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\FriendList.h
# End Source File
# Begin Source File

SOURCE=.\SRC\IOSocket.h
# End Source File
# Begin Source File

SOURCE=.\MessageControl.h
# End Source File
# Begin Source File

SOURCE=.\SRC\MessageQueue.h
# End Source File
# Begin Source File

SOURCE=.\ModifyContactDlg.h
# End Source File
# Begin Source File

SOURCE=.\PhoneWaveIn.h
# End Source File
# Begin Source File

SOURCE=.\RecordListDlg.h
# End Source File
# Begin Source File

SOURCE=.\RegState.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SipMessage.h
# End Source File
# Begin Source File

SOURCE=.\SRC\SocketStream.h
# End Source File
# Begin Source File

SOURCE=.\SoftPhoneDlg.h
# End Source File
# Begin Source File

SOURCE=.\StateBase.h
# End Source File
# Begin Source File

SOURCE=.\StateMacManager.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TestWaveIn.h
# End Source File
# Begin Source File

SOURCE=.\SRC\Time_Value.h
# End Source File
# Begin Source File

SOURCE=.\SRC\Timer.h
# End Source File
# Begin Source File

SOURCE=.\SRC\TimerQueue.h
# End Source File
# Begin Source File

SOURCE=.\SRC\TimerSession.h
# End Source File
# Begin Source File

SOURCE=.\WaveIn.h
# End Source File
# Begin Source File

SOURCE=.\WaveOut.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Client.ico
# End Source File
# Begin Source File

SOURCE=.\res\Client.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
