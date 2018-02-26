# Microsoft Developer Studio Generated NMAKE File, Based on Client.dsp
!IF "$(CFG)" == ""
CFG=Client - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Client - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Client - Win32 Release" && "$(CFG)" != "Client - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Client - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Client.exe"


CLEAN :
	-@erase "$(INTDIR)\AppMutex.obj"
	-@erase "$(INTDIR)\AppThread.obj"
	-@erase "$(INTDIR)\CallInState.obj"
	-@erase "$(INTDIR)\CallOutState.obj"
	-@erase "$(INTDIR)\Client.obj"
	-@erase "$(INTDIR)\Client.pch"
	-@erase "$(INTDIR)\Client.res"
	-@erase "$(INTDIR)\ClientDlg.obj"
	-@erase "$(INTDIR)\ClientSocket.obj"
	-@erase "$(INTDIR)\CWaveIn.obj"
	-@erase "$(INTDIR)\G7231_G792.obj"
	-@erase "$(INTDIR)\IOSocket.obj"
	-@erase "$(INTDIR)\MessageControl.obj"
	-@erase "$(INTDIR)\MessageQueue.obj"
	-@erase "$(INTDIR)\RegState.obj"
	-@erase "$(INTDIR)\SipMessage.obj"
	-@erase "$(INTDIR)\SocketStream.obj"
	-@erase "$(INTDIR)\SoftPhoneDlg.obj"
	-@erase "$(INTDIR)\StateBase.obj"
	-@erase "$(INTDIR)\StateMacManager.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Time_Value.obj"
	-@erase "$(INTDIR)\Timer.obj"
	-@erase "$(INTDIR)\TimerQueue.obj"
	-@erase "$(INTDIR)\TimerSession.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Client.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Client.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Client.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Client.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=osip_parse2_r.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Client.pdb" /machine:I386 /out:"$(OUTDIR)\Client.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AppMutex.obj" \
	"$(INTDIR)\AppThread.obj" \
	"$(INTDIR)\CallInState.obj" \
	"$(INTDIR)\CallOutState.obj" \
	"$(INTDIR)\Client.obj" \
	"$(INTDIR)\ClientDlg.obj" \
	"$(INTDIR)\ClientSocket.obj" \
	"$(INTDIR)\CWaveIn.obj" \
	"$(INTDIR)\G7231_G792.obj" \
	"$(INTDIR)\IOSocket.obj" \
	"$(INTDIR)\MessageControl.obj" \
	"$(INTDIR)\MessageQueue.obj" \
	"$(INTDIR)\RegState.obj" \
	"$(INTDIR)\SipMessage.obj" \
	"$(INTDIR)\SocketStream.obj" \
	"$(INTDIR)\SoftPhoneDlg.obj" \
	"$(INTDIR)\StateBase.obj" \
	"$(INTDIR)\StateMacManager.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Time_Value.obj" \
	"$(INTDIR)\Timer.obj" \
	"$(INTDIR)\TimerQueue.obj" \
	"$(INTDIR)\TimerSession.obj" \
	"$(INTDIR)\Client.res"

"$(OUTDIR)\Client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Client - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Client.exe" "$(OUTDIR)\Client.pch" "$(OUTDIR)\Client.bsc"


CLEAN :
	-@erase "$(INTDIR)\AppMutex.obj"
	-@erase "$(INTDIR)\AppMutex.sbr"
	-@erase "$(INTDIR)\AppThread.obj"
	-@erase "$(INTDIR)\AppThread.sbr"
	-@erase "$(INTDIR)\CallInState.obj"
	-@erase "$(INTDIR)\CallInState.sbr"
	-@erase "$(INTDIR)\CallOutState.obj"
	-@erase "$(INTDIR)\CallOutState.sbr"
	-@erase "$(INTDIR)\Client.obj"
	-@erase "$(INTDIR)\Client.pch"
	-@erase "$(INTDIR)\Client.res"
	-@erase "$(INTDIR)\Client.sbr"
	-@erase "$(INTDIR)\ClientDlg.obj"
	-@erase "$(INTDIR)\ClientDlg.sbr"
	-@erase "$(INTDIR)\ClientSocket.obj"
	-@erase "$(INTDIR)\ClientSocket.sbr"
	-@erase "$(INTDIR)\CWaveIn.obj"
	-@erase "$(INTDIR)\CWaveIn.sbr"
	-@erase "$(INTDIR)\G7231_G792.obj"
	-@erase "$(INTDIR)\G7231_G792.sbr"
	-@erase "$(INTDIR)\IOSocket.obj"
	-@erase "$(INTDIR)\IOSocket.sbr"
	-@erase "$(INTDIR)\MessageControl.obj"
	-@erase "$(INTDIR)\MessageControl.sbr"
	-@erase "$(INTDIR)\MessageQueue.obj"
	-@erase "$(INTDIR)\MessageQueue.sbr"
	-@erase "$(INTDIR)\RegState.obj"
	-@erase "$(INTDIR)\RegState.sbr"
	-@erase "$(INTDIR)\SipMessage.obj"
	-@erase "$(INTDIR)\SipMessage.sbr"
	-@erase "$(INTDIR)\SocketStream.obj"
	-@erase "$(INTDIR)\SocketStream.sbr"
	-@erase "$(INTDIR)\SoftPhoneDlg.obj"
	-@erase "$(INTDIR)\SoftPhoneDlg.sbr"
	-@erase "$(INTDIR)\StateBase.obj"
	-@erase "$(INTDIR)\StateBase.sbr"
	-@erase "$(INTDIR)\StateMacManager.obj"
	-@erase "$(INTDIR)\StateMacManager.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Time_Value.obj"
	-@erase "$(INTDIR)\Time_Value.sbr"
	-@erase "$(INTDIR)\Timer.obj"
	-@erase "$(INTDIR)\Timer.sbr"
	-@erase "$(INTDIR)\TimerQueue.obj"
	-@erase "$(INTDIR)\TimerQueue.sbr"
	-@erase "$(INTDIR)\TimerSession.obj"
	-@erase "$(INTDIR)\TimerSession.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Client.bsc"
	-@erase "$(OUTDIR)\Client.exe"
	-@erase "$(OUTDIR)\Client.ilk"
	-@erase "$(OUTDIR)\Client.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /w /W0 /Gm /GX /ZI /Od /I "SRC" /I "..\libosip2.20\osip2fsm\include" /I "..\libosip2.20\osip2parse\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Client.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Client.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AppMutex.sbr" \
	"$(INTDIR)\AppThread.sbr" \
	"$(INTDIR)\CallInState.sbr" \
	"$(INTDIR)\CallOutState.sbr" \
	"$(INTDIR)\Client.sbr" \
	"$(INTDIR)\ClientDlg.sbr" \
	"$(INTDIR)\ClientSocket.sbr" \
	"$(INTDIR)\CWaveIn.sbr" \
	"$(INTDIR)\G7231_G792.sbr" \
	"$(INTDIR)\IOSocket.sbr" \
	"$(INTDIR)\MessageControl.sbr" \
	"$(INTDIR)\MessageQueue.sbr" \
	"$(INTDIR)\RegState.sbr" \
	"$(INTDIR)\SipMessage.sbr" \
	"$(INTDIR)\SocketStream.sbr" \
	"$(INTDIR)\SoftPhoneDlg.sbr" \
	"$(INTDIR)\StateBase.sbr" \
	"$(INTDIR)\StateMacManager.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Time_Value.sbr" \
	"$(INTDIR)\Timer.sbr" \
	"$(INTDIR)\TimerQueue.sbr" \
	"$(INTDIR)\TimerSession.sbr"

"$(OUTDIR)\Client.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=osip_parse2_d.lib g7231d.lib va_g729a.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Client.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Client.exe" /pdbtype:sept /libpath:"LIB" 
LINK32_OBJS= \
	"$(INTDIR)\AppMutex.obj" \
	"$(INTDIR)\AppThread.obj" \
	"$(INTDIR)\CallInState.obj" \
	"$(INTDIR)\CallOutState.obj" \
	"$(INTDIR)\Client.obj" \
	"$(INTDIR)\ClientDlg.obj" \
	"$(INTDIR)\ClientSocket.obj" \
	"$(INTDIR)\CWaveIn.obj" \
	"$(INTDIR)\G7231_G792.obj" \
	"$(INTDIR)\IOSocket.obj" \
	"$(INTDIR)\MessageControl.obj" \
	"$(INTDIR)\MessageQueue.obj" \
	"$(INTDIR)\RegState.obj" \
	"$(INTDIR)\SipMessage.obj" \
	"$(INTDIR)\SocketStream.obj" \
	"$(INTDIR)\SoftPhoneDlg.obj" \
	"$(INTDIR)\StateBase.obj" \
	"$(INTDIR)\StateMacManager.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Time_Value.obj" \
	"$(INTDIR)\Timer.obj" \
	"$(INTDIR)\TimerQueue.obj" \
	"$(INTDIR)\TimerSession.obj" \
	"$(INTDIR)\Client.res"

"$(OUTDIR)\Client.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Client.dep")
!INCLUDE "Client.dep"
!ELSE 
!MESSAGE Warning: cannot find "Client.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Client - Win32 Release" || "$(CFG)" == "Client - Win32 Debug"
SOURCE=.\SRC\AppMutex.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\AppMutex.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\AppMutex.obj"	"$(INTDIR)\AppMutex.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\SRC\AppThread.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\AppThread.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\AppThread.obj"	"$(INTDIR)\AppThread.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\CallInState.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\CallInState.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\CallInState.obj"	"$(INTDIR)\CallInState.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CallOutState.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\CallOutState.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\CallOutState.obj"	"$(INTDIR)\CallOutState.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Client.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\Client.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\Client.obj"	"$(INTDIR)\Client.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Client.rc

"$(INTDIR)\Client.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ClientDlg.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\ClientDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\ClientDlg.obj"	"$(INTDIR)\ClientDlg.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ClientSocket.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\ClientSocket.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\ClientSocket.obj"	"$(INTDIR)\ClientSocket.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\CWaveIn.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\CWaveIn.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\CWaveIn.obj"	"$(INTDIR)\CWaveIn.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SRC\G7231_G792.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\G7231_G792.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\G7231_G792.obj"	"$(INTDIR)\G7231_G792.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\SRC\IOSocket.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\IOSocket.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\IOSocket.obj"	"$(INTDIR)\IOSocket.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\MessageControl.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\MessageControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\MessageControl.obj"	"$(INTDIR)\MessageControl.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SRC\MessageQueue.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\MessageQueue.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\MessageQueue.obj"	"$(INTDIR)\MessageQueue.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\RegState.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\RegState.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\RegState.obj"	"$(INTDIR)\RegState.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SipMessage.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\SipMessage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\SipMessage.obj"	"$(INTDIR)\SipMessage.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SRC\SocketStream.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\SocketStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\SocketStream.obj"	"$(INTDIR)\SocketStream.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\SoftPhoneDlg.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\SoftPhoneDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\SoftPhoneDlg.obj"	"$(INTDIR)\SoftPhoneDlg.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StateBase.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\StateBase.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\StateBase.obj"	"$(INTDIR)\StateBase.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StateMacManager.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\StateMacManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\StateMacManager.obj"	"$(INTDIR)\StateMacManager.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Client - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Client.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Client.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /w /W0 /Gm /GX /ZI /Od /I "SRC" /I "..\libosip2.20\osip2fsm\include" /I "..\libosip2.20\osip2parse\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Client.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Client.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\SRC\Time_Value.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\Time_Value.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\Time_Value.obj"	"$(INTDIR)\Time_Value.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\SRC\Timer.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\Timer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\Timer.obj"	"$(INTDIR)\Timer.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\SRC\TimerQueue.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\TimerQueue.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\TimerQueue.obj"	"$(INTDIR)\TimerQueue.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\SRC\TimerSession.cpp

!IF  "$(CFG)" == "Client - Win32 Release"


"$(INTDIR)\TimerSession.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Client.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "Client - Win32 Debug"


"$(INTDIR)\TimerSession.obj"	"$(INTDIR)\TimerSession.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

