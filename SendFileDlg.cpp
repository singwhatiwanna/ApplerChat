// SendFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSocketDemo.h"
#include "SendFileDlg.h"
#include "CServerSocket.h"
#include "ClientSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendFileDlg dialog


CSendFileDlg::CSendFileDlg(int _socketType,CAsyncSocket *_attachedSocket,CWnd* pParent /*=NULL*/)
	: CDialog(CSendFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	attachedSocket=_attachedSocket;
	socketType=_socketType;
	//}}AFX_DATA_INIT
}


void CSendFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendFileDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendFileDlg, CDialog)
	//{{AFX_MSG_MAP(CSendFileDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendFileDlg message handlers

BOOL CSendFileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(m_hIcon,TRUE);
	SetIcon(m_hIcon,FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSendFileDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (socketType==1)
	{
		CServerSocket *serverSocket=(CServerSocket*)attachedSocket;
		serverSocket->fileTran=NULL;
	}
	else
	{
		CClientSocket *clientSocket=(CClientSocket*)attachedSocket;
		clientSocket->fileTran=NULL;
	}
	CDialog::PostNcDestroy();
	delete this;
}

void CSendFileDlg::OnCancel()
{
	DestroyWindow();
}