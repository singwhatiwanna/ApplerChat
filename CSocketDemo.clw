; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCSocketDemoDlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CSocketDemo.h"

ClassCount=11
Class1=CCSocketDemoApp
Class2=CCSocketDemoDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_AVDLG
Resource2=IDR_MAINFRAME
Class4=MyAsyncSocket
Resource3=IDD_CSOCKETDEMO_DIALOG
Resource4=IDD_SENDFILE_DIALOG
Class5=CClientAsyncSocket
Class6=CListenSocket
Class7=CSendFileDlg
Resource5=IDD_INCOMING_CALL
Resource6=IDD_ABOUTBOX
Class8=CChatSocket
Class9=CClientListenSocket
Class10=CClientSvrSocket
Class11=CClientCliSocket
Resource7=IDR_POPUPMENU

[CLS:CCSocketDemoApp]
Type=0
HeaderFile=CSocketDemo.h
ImplementationFile=CSocketDemo.cpp
Filter=N

[CLS:CCSocketDemoDlg]
Type=0
HeaderFile=CSocketDemoDlg.h
ImplementationFile=CSocketDemoDlg.cpp
Filter=W
LastObject=ID_SERVER_KICK
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CSocketDemoDlg.h
ImplementationFile=CSocketDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_USER_SENDFILE

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342177281
Control5=IDC_STATIC_WEB,static,1342308352

[DLG:IDD_CSOCKETDEMO_DIALOG]
Type=1
Class=?
ControlCount=13
Control1=IDC_EDIT_MSG,edit,1352728580
Control2=IDC_BUTTON_SEND,button,1342242817
Control3=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control4=IDC_RICHEDIT_CONTENT,RICHEDIT,1352734724
Control5=IDC_BUTTON_ESTAB,button,1342242816
Control6=IDC_BUTTON_CONNECT,button,1342242816
Control7=IDC_LIST_CLIENT,SysListView32,1350631433
Control8=IDC_BUTTON_CLOSE,button,1342242816
Control9=IDC_BUTTON_ABOUT,button,1342242816
Control10=IDC_STATIC_TITLE,static,1342308352
Control11=IDC_STATIC,static,1342177795
Control12=IDC_BUTTON_MINIMIZE,button,1342242816
Control13=IDC_BUTTON_MAXMIZE,button,1342242816

[CLS:MyAsyncSocket]
Type=0
HeaderFile=MyAsyncSocket.h
ImplementationFile=MyAsyncSocket.cpp
BaseClass=CAsyncSocket
Filter=N
LastObject=IDC_BUTTON_ABOUT

[MNU:IDR_POPUPMENU]
Type=1
Class=CCSocketDemoDlg
Command1=ID_EDIT_COPY
Command2=ID_EDIT_CLEAR
Command3=ID_USER_SENDFILE
Command4=ID_USER_VIDEOCHAT
Command5=ID_POPUP_SHOW
Command6=ID_POPUP_TRAY
Command7=IDC_BUTTON_ABOUT
Command8=ID_POPUP_EXIT
Command9=ID_USER_SENDFILE
Command10=ID_USER_VIDEOCHAT
Command11=ID_SERVER_KICK
CommandCount=11

[DLG:IDD_SENDFILE_DIALOG]
Type=1
Class=CSendFileDlg
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC_SRCA,static,1342308352
Control6=IDC_STATIC_DESA,static,1342308352
Control7=IDC_STATIC_FINFO,static,1342308352
Control8=IDC_PROGRESS_TRANFILE,msctls_progress32,1350565888
Control9=IDC_STATIC_STATUS,static,1342308352

[CLS:CClientAsyncSocket]
Type=0
HeaderFile=ClientAsyncSocket.h
ImplementationFile=ClientAsyncSocket.cpp
BaseClass=CAsyncSocket
Filter=N

[CLS:CListenSocket]
Type=0
HeaderFile=ListenSocket.h
ImplementationFile=ListenSocket.cpp
BaseClass=CAsyncSocket
Filter=N
LastObject=CListenSocket

[CLS:CSendFileDlg]
Type=0
HeaderFile=SendFileDlg.h
ImplementationFile=SendFileDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CSendFileDlg
VirtualFilter=dWC

[DLG:IDD_AVDLG]
Type=1
Class=?
ControlCount=9
Control1=IDC_SPEAKER_TEXT,static,1342308352
Control2=IDC_MIC_TEXT,static,1342308352
Control3=IDC_SPEAKER_BAR,msctls_progress32,1350565888
Control4=IDC_MIC_BAR,msctls_progress32,1350565888
Control5=IDC_SPEAKER_SLIDER,msctls_trackbar32,1342373912
Control6=IDC_SPEAKERMUTE,button,1342246915
Control7=IDC_MIC_SLIDER,msctls_trackbar32,1342373912
Control8=IDC_MICMUTE,button,1342246915
Control9=IDOK,button,1342242817

[DLG:IDD_INCOMING_CALL]
Type=1
Class=?
ControlCount=6
Control1=65535,static,1342308352
Control2=IDC_CALLERNAME,static,1342308352
Control3=65535,static,1342308352
Control4=IDC_CALLERID,static,1342308352
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816

[CLS:CChatSocket]
Type=0
HeaderFile=ChatSocket.h
ImplementationFile=ChatSocket.cpp
BaseClass=CAsyncSocket
Filter=N

[CLS:CClientListenSocket]
Type=0
HeaderFile=ClientListenSocket.h
ImplementationFile=ClientListenSocket.cpp
BaseClass=CAsyncSocket
Filter=N

[CLS:CClientSvrSocket]
Type=0
HeaderFile=ClientSvrSocket.h
ImplementationFile=ClientSvrSocket.cpp
BaseClass=CAsyncSocket
Filter=N

[CLS:CClientCliSocket]
Type=0
HeaderFile=ClientCliSocket.h
ImplementationFile=ClientCliSocket.cpp
BaseClass=CAsyncSocket
Filter=N

