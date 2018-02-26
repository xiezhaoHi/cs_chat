; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSoftPhoneDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "client.h"
LastPage=0

ClassCount=8
Class1=CClientApp
Class2=CAboutDlg
Class3=CClientDlg
Class4=CSoftPhoneDlg

ResourceCount=7
Resource1=IDD_SOFT_PHONE
Resource2=IDD_DIALOG_LIST
Resource3=IDD_ABOUTBOX
Class5=CAddFriendInfo
Resource4=IDD_ADD_USER
Class6=CFriendList
Resource5=IDD_MODIFY_CONTACT
Class7=CModifyContactDlg
Resource6=IDD_CLIENT_DIALOG
Class8=CRecordListDlg
Resource7=IDD_CALL_REGISTER

[CLS:CClientApp]
Type=0
BaseClass=CWinApp
HeaderFile=Client.h
ImplementationFile=Client.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=ClientDlg.cpp
ImplementationFile=ClientDlg.cpp
LastObject=CAboutDlg

[CLS:CClientDlg]
Type=0
BaseClass=CDialog
HeaderFile=ClientDlg.h
ImplementationFile=ClientDlg.cpp
Filter=D
VirtualFilter=dWC

[CLS:CSoftPhoneDlg]
Type=0
BaseClass=CDialog
HeaderFile=SoftPhoneDlg.h
ImplementationFile=SoftPhoneDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CSoftPhoneDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CLIENT_DIALOG]
Type=1
Class=CClientDlg
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_ACCOUNT,edit,1350639744
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PASSWORD,edit,1350631552
Control5=IDC_REGIST_OK,button,1342242816
Control6=IDCANCEL,button,1342242816
Control7=IDC_SERVER_IP,SysIPAddress32,1342242816
Control8=IDC_STATIC,static,1342308352
Control9=IDC_SERVER_PORT,edit,1350639744
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_SOFT_PHONE]
Type=1
Class=CSoftPhoneDlg
ControlCount=20
Control1=IDC_USER_NUMBER,edit,1350633600
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816
Control4=IDC_BUTTON3,button,1342242816
Control5=IDC_BUTTON4,button,1342242816
Control6=IDC_BUTTON5,button,1342242816
Control7=IDC_BUTTON6,button,1342242816
Control8=IDC_BUTTON7,button,1342242816
Control9=IDC_BUTTON8,button,1342242816
Control10=IDC_BUTTON9,button,1342242816
Control11=IDC_BUTTON10,button,1342242816
Control12=IDC_BUTTON0,button,1342242816
Control13=IDC_CLEAN,button,1342242816
Control14=IDC_CALLING,button,1342242816
Control15=IDC_BYE,button,1342242816
Control16=IDC_LISTEN,button,1342242816
Control17=IDC_BUTTON16,button,1342242816
Control18=IDC_MSG,edit,1350633612
Control19=IDC_ADDFRIEND,button,1342242816
Control20=IDC_RECORD,button,1342242816

[DLG:IDD_ADD_USER]
Type=1
Class=CAddFriendInfo
ControlCount=10
Control1=IDC_STATIC,static,1342308352
Control2=IDC_NAME,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PHONE,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_ADDR,edit,1350631556
Control8=IDC_WORKUNIT,edit,1350631556
Control9=IDC_SAVE,button,1342242817
Control10=IDC_CANCEL,button,1342242816

[CLS:CAddFriendInfo]
Type=0
HeaderFile=AddFriendInfo.h
ImplementationFile=AddFriendInfo.cpp
BaseClass=CDialog
Filter=D
LastObject=CAddFriendInfo
VirtualFilter=dWC

[DLG:IDD_DIALOG_LIST]
Type=1
Class=CFriendList
ControlCount=5
Control1=IDC_LIST,SysListView32,1350631425
Control2=IDC_ADD,button,1342242816
Control3=IDC_CHANGE,button,1342242816
Control4=IDC_DELETE,button,1342242816
Control5=IDCANCEL,button,1342242816

[CLS:CFriendList]
Type=0
HeaderFile=FriendList.h
ImplementationFile=FriendList.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_MODIFY_CONTACT]
Type=1
Class=CModifyContactDlg
ControlCount=10
Control1=IDC_EDIT_NAME,edit,1350631552
Control2=IDC_EDIT_PHONE,edit,1484857472
Control3=IDC_EDIT_ADDRESS,edit,1350631556
Control4=IDC_EDIT_WORK_UNIT,edit,1350631556
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[CLS:CModifyContactDlg]
Type=0
HeaderFile=ModifyContactDlg.h
ImplementationFile=ModifyContactDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CModifyContactDlg

[DLG:IDD_CALL_REGISTER]
Type=1
Class=CRecordListDlg
ControlCount=3
Control1=IDCANCEL,button,1342242816
Control2=IDC_BTN_DEL,button,1342242816
Control3=IDC_LIST,SysListView32,1350631429

[CLS:CRecordListDlg]
Type=0
HeaderFile=RecordListDlg.h
ImplementationFile=RecordListDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

