// CSocketDemo.h : main header file for the CSOCKETDEMO application
//

#if !defined(AFX_CSOCKETDEMO_H__3C6C29FC_9750_412F_9DFF_440B97801FDA__INCLUDED_)
#define AFX_CSOCKETDEMO_H__3C6C29FC_9750_412F_9DFF_440B97801FDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <afxsock.h>
#include "HyperLink.h"
#include "ClientSocket.h"
#include "CServerSocket.h"
#include "ListenSocket.h"
#include "ChatSocket.h"
#include "ClientCliSocket.h"
#include "ClientSvrSocket.h"
#include "ClientListenSocket.h"

#include "mmsystem.h"//²¥·Åwave
#pragma comment(lib, "winmm.lib")

#define TRANSFERFILE 2
#define SENDTEXTMSG 1
#define SOCKETTYPESERVER 1
#define SOCKETTYPECLIENT 2
#define PACKAGESIZE 1024*10
/////////////////////////////////////////////////////////////////////////////
// CCSocketDemoApp:
// See CSocketDemo.cpp for the implementation of this class
//

class CCSocketDemoApp : public CWinApp
{
public:
	CCSocketDemoApp();

public:
	CMapStringToOb mapSocket;
	CString localHost;
	CString localIP;
	BOOL isServer;
	BOOL canGo;
	BOOL enableVideoChat;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSocketDemoApp)
	public:
	virtual BOOL InitInstance();
	void NotifyAll(CString host,CString ip,CString port,BOOL enter=TRUE);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCSocketDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSOCKETDEMO_H__3C6C29FC_9750_412F_9DFF_440B97801FDA__INCLUDED_)
