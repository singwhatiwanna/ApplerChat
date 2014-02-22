// CSocketDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CSocketDemo.h"
#include "CSocketDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSocketDemoApp

BEGIN_MESSAGE_MAP(CCSocketDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CCSocketDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSocketDemoApp construction

CCSocketDemoApp::CCSocketDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCSocketDemoApp object

CCSocketDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCSocketDemoApp initialization

BOOL CCSocketDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	SetDialogBkColor(RGB(106,172,38),RGB(255,255,255));
	enableVideoChat=TRUE;
	if(!AfxInitRichEdit())
	{
		return FALSE;
	}

	if (!AfxSocketInit(NULL))
	{
		return FALSE;
	}

	gethostname(localHost.GetBuffer(128),128);//get local ipaddress and hostname
	localHost.ReleaseBuffer();
	struct hostent* pHost;
	pHost=gethostbyname(localHost);
	localIP=inet_ntoa(*(struct in_addr*)pHost->h_addr_list[0]);

	CCSocketDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CCSocketDemoApp::NotifyAll(CString host,CString ip,CString port,BOOL enter/* =TRUE */)
{
	canGo=0;
	POSITION pos;
	CString key;
	CServerSocket* tempSocket;
	CString msg;
	if(enter)	msg.Format("+%s %s %s",host,ip,port);
	else	msg.Format("#%s %s %s",host,ip,port);//用#号代替-号，因为-号可能出现在主机名中。
	
	for(pos = mapSocket.GetStartPosition(); pos!= NULL; )
	{
		mapSocket.GetNextAssoc(pos,key,(CObject*&)tempSocket );
		tempSocket->Send(CString("<?Command update client list?>")+msg,256);
	}
}