// CSocketDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CSocketDemo.h"
#include "CSocketDemoDlg.h"
#include "CServerSocket.h"
#include "resource.h"
#include "defines.h"
#include "IncomingDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BSTR g_bstrAddr;
extern CCSocketDemoApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CSMButton m_btnOk;
	CHyperLink	m_staticWeb;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_staticWeb.SetURL("http://www.renyugang.cn");
	m_btnOk.SetTextColor(RGB(255,255,255));
	m_btnOk.SetInactiveBgColor(RGB(176,200,68));
	m_btnOk.SetActiveBgColor(RGB(255,153,0));
	m_btnOk.SetBorderColor(RGB(176,200,68));
	//m_staticWeb.set
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_STATIC_WEB, m_staticWeb);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSocketDemoDlg dialog

CCSocketDemoDlg::CCSocketDemoDlg(CWnd* pParent /*=NULL*/)
	: ClxDialog(CCSocketDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCSocketDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_redApple=AfxGetApp()->LoadIcon(IDI_ICON_RAPPLE);
	isMax=0;
	flashicon=0;
	flashWindowCount=0;
}

void CCSocketDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCSocketDemoDlg)
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSend);
	DDX_Control(pDX, IDC_BUTTON_MINIMIZE, m_btnMinmize);
	DDX_Control(pDX, IDC_BUTTON_MAXMIZE, m_btnMaxmize);
	DDX_Control(pDX, IDC_BUTTON_ESTAB, m_btnEstab);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_btnClose);
	DDX_Control(pDX, IDC_BUTTON_ABOUT, m_btnAbout);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCSocketDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CCSocketDemoDlg)
	ON_WM_CONTEXTMENU()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_ESTAB, OnButtonEstab)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnButtonAbout)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_MAXMIZE, OnButtonMaxmize)
	ON_BN_CLICKED(IDC_BUTTON_MINIMIZE, OnButtonMinimize)
	ON_COMMAND(ID_USER_SENDFILE, OnUserSendfile)
	ON_COMMAND(ID_USER_VIDEOCHAT, OnUserVideochat)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_NOTIFYICON,OnNotifyIcon)
	ON_COMMAND(ID_POPUP_SHOW, OnPopupShow)
	ON_COMMAND(ID_POPUP_TRAY, OnPopupTray)
	ON_COMMAND(ID_POPUP_EXIT, OnPopupExit)
	ON_WM_TIMER()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_SERVER_KICK, OnServerKick)
	ON_MESSAGE(WM_HOTKEY,OnHotKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSocketDemoDlg message handlers

BOOL CCSocketDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetWindowText("Appler");
	//SetWindowPos(NULL,0,0,586,508,SWP_NOMOVE);
	if (InitRTCClient() != S_OK)
	{
		theApp.enableVideoChat=FALSE;
		MessageBox("视频通信初始化失败！",NULL,MB_ICONWARNING);
	}
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	CString ip=((CCSocketDemoApp*)AfxGetApp())->localIP;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->SetAddress(ntohl(inet_addr(ip.GetBuffer(0))));
	imageList.Create(16,16,TRUE|ILC_COLOR32,10,10);
	HICON icon=AfxGetApp()->LoadIcon(IDI_ICON_RAPPLE);
	imageList.Add(icon);
	imageList.Add(m_hIcon);
	CListCtrl *lc=(CListCtrl*)GetDlgItem(IDC_LIST_CLIENT);
	lc->InsertColumn(0,"主机名",LVCFMT_LEFT,150);
	lc->InsertColumn(1,"IP地址",LVCFMT_LEFT,100);
	lc->InsertColumn(2,"端口号",LVCFMT_LEFT,50);
	lc->SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	lc->SetImageList(&imageList,LVSIL_SMALL);
	//  控件信息数组
	static DLGCTLINFO  dcMenuGroup[] = 
	{
		{IDC_BUTTON_SEND, MOVEX, 83},
		{IDC_BUTTON_SEND, MOVEY, 100},
		{IDC_IPADDRESS1, MOVEY, 100},
		{IDC_RICHEDIT_CONTENT, ELASTICX, 83},
		{IDC_RICHEDIT_CONTENT, ELASTICY, 100},
		{IDC_EDIT_MSG, MOVEY, 100},
		{IDC_EDIT_MSG, ELASTICX, 83},
		{IDC_LIST_CLIENT, MOVEX, 83},
		{IDC_LIST_CLIENT, ELASTICX, 17},
		{IDC_LIST_CLIENT, ELASTICY, 100},
		{IDC_BUTTON_ESTAB, MOVEY, 100},
		{IDC_BUTTON_CONNECT, MOVEY, 100},
		{IDC_BUTTON_CLOSE, MOVEX, 100},
		{IDC_BUTTON_ABOUT, MOVEX, 100},
		{IDC_BUTTON_MAXMIZE, MOVEX, 100},
		{IDC_BUTTON_MINIMIZE, MOVEX, 100},
	};
	//  设置控件信息
	SetControlProperty(dcMenuGroup, sizeof(dcMenuGroup)/sizeof(DLGCTLINFO));
	ShowSizeIcon(TRUE);


	//set button style
	m_btnClose.SetTextColor(RGB(255,255,255));
	m_btnClose.SetInactiveBgColor(RGB(176,200,68));
	m_btnClose.SetActiveBgColor(RGB(255,0,0));
	m_btnClose.SetBorderColor(RGB(176,200,68));

	m_btnAbout.SetTextColor(RGB(255,255,255));
	m_btnAbout.SetInactiveBgColor(RGB(176,200,68));
	m_btnAbout.SetActiveBgColor(RGB(255,153,0));
	m_btnAbout.SetBorderColor(RGB(176,200,68));

	m_btnMaxmize.SetTextColor(RGB(255,255,255));
	m_btnMaxmize.SetInactiveBgColor(RGB(176,200,68));
	m_btnMaxmize.SetActiveBgColor(RGB(255,153,0));
	m_btnMaxmize.SetBorderColor(RGB(176,200,68));
	
	m_btnMinmize.SetTextColor(RGB(255,255,255));
	m_btnMinmize.SetInactiveBgColor(RGB(176,200,68));
	m_btnMinmize.SetActiveBgColor(RGB(255,153,0));
	m_btnMinmize.SetBorderColor(RGB(176,200,68));

	m_btnSend.SetTextColor(RGB(0,0,0));
	m_btnSend.SetInactiveBgColor(RGB(176,200,68));
	m_btnSend.SetActiveBgColor(RGB(255,153,0));
	m_btnSend.SetBorderColor(RGB(176,200,68));
	
	m_btnEstab.SetTextColor(RGB(0,0,0));
	m_btnEstab.SetInactiveBgColor(RGB(176,200,68));
	m_btnEstab.SetActiveBgColor(RGB(255,153,0));
	m_btnEstab.SetBorderColor(RGB(176,200,68));
	
	m_btnConnect.SetTextColor(RGB(0,0,0));
	m_btnConnect.SetInactiveBgColor(RGB(176,200,68));
	m_btnConnect.SetActiveBgColor(RGB(255,153,0));
	m_btnConnect.SetBorderColor(RGB(176,200,68));

	//将图标放入系统托盘
	CoInitialize(NULL);//CoInitialize函数初始化COM库
	nd.cbSize = sizeof(NOTIFYICONDATA);
	nd.hWnd = m_hWnd;
	nd.uID = IDR_MAINFRAME;       
	nd.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
	nd.uCallbackMessage = WM_NOTIFYICON;  
	nd.hIcon = m_hIcon;      
	strcpy(nd.szTip, "Appler");   
	Shell_NotifyIcon(NIM_ADD, &nd);
	RegisterHotKey(this->m_hWnd,1001,MOD_CONTROL|MOD_ALT,'o');//注册全局快捷键 即热键
	RegisterHotKey(this->m_hWnd,1002,MOD_CONTROL|MOD_ALT,'O');

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCSocketDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCSocketDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCSocketDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CCSocketDemoDlg::InitAsyncSocket()
{
	int ret=m_listenSocket.Create(8888,SOCK_STREAM,FD_ACCEPT,((CCSocketDemoApp*)AfxGetApp())->localIP);
	if (!ret)
	{
		AfxMessageBox("创建套接字失败",MB_ICONERROR);
	}
	ret=m_listenSocket.Listen(5);
	if (!ret)
	{
		AfxMessageBox("监听失败",MB_ICONERROR);
	}
	return ret;
}

BOOL CCSocketDemoDlg::InitClientAsyncSocket()
{
	int ret=m_clientListenSocket.Create(8989,SOCK_STREAM,FD_ACCEPT,((CCSocketDemoApp*)AfxGetApp())->localIP);
	if (!ret)
	{
		AfxMessageBox("创建文件传输套接字失败",MB_ICONWARNING);
		return ret;
	}
	ret=m_clientListenSocket.Listen(5);
	if (!ret)
	{
		AfxMessageBox("监听失败",MB_ICONWARNING);
		return ret;
	}
	return ret;
}

void CCSocketDemoDlg::OnButtonSend(int type/*=SENDTEXTMSG*/,int responseTo/*=RESPONSETOSERVER*/) 
{
	// TODO: Add your control notification handler code here
	CString buf;
	int ret;
	GetDlgItemText(IDC_EDIT_MSG,buf);
	if (buf.GetLength()==0)
	{
		GetDlgItem(IDC_EDIT_MSG)->SetFocus();
		return;
	}
	CListCtrl *lc=(CListCtrl*)GetDlgItem(IDC_LIST_CLIENT);
	for (int i=0,total=0;i<lc->GetItemCount();i++)
	{
		if(lc->GetCheck(i))	total++;
	}
	if (total<=0)
	{
		return;
	}

	CRichEditCtrl *m_RichEdit1;
	m_RichEdit1=(CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_CONTENT);
	CCSocketDemoApp *socketapp=(CCSocketDemoApp*)AfxGetApp();
	CString host,msg;

	CTime time=CTime::GetCurrentTime();
	CString currentTime;
	currentTime.Format("          %02d:%02d:%02d",time.GetHour(),time.GetMinute(),time.GetSecond());

	host.Format("%s%s",socketapp->localHost,currentTime);
	msg.Format("\r\n  %s\r\n",buf);

	DWORD lineCount=m_RichEdit1->GetLineCount();
	
	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_BOLD | CFM_COLOR | CFM_FACE |
		CFM_ITALIC | CFM_SIZE | CFM_UNDERLINE;
	cf.dwEffects = 0;
	cf.yHeight = 15*15;//文字高度
	cf.crTextColor = RGB(255, 0, 0); //文字颜色
	strcpy(cf.szFaceName ,_T("宋体"));//设置字体
	m_RichEdit1->SetDefaultCharFormat(cf);
	m_RichEdit1->SetBackgroundColor(FALSE,RGB(255,255,255));
	cf.yHeight = 13*13;//文字高度
	cf.crTextColor = RGB(0,102,0); //文字颜色
	strcpy(cf.szFaceName ,_T("微软雅黑"));//设置字体
	m_RichEdit1->SetSel(m_RichEdit1->GetTextLength(),m_RichEdit1->GetTextLength());
	m_RichEdit1->ReplaceSel(host);
	m_RichEdit1->SetSel(m_RichEdit1->GetTextLength()-host.GetLength(),m_RichEdit1->GetTextLength());
	m_RichEdit1->SetSelectionCharFormat(cf);
	
	m_RichEdit1->SetSel(-1,-1);
	m_RichEdit1->ReplaceSel(msg);
	cf.yHeight = 14*14;//文字高度
	cf.crTextColor = RGB(204,0,204); //文字颜色
	strcpy(cf.szFaceName ,_T("微软雅黑"));//设置字体
	m_RichEdit1->SetSel(m_RichEdit1->GetTextLength()-msg.GetLength(),m_RichEdit1->GetTextLength());
	m_RichEdit1->SetSelectionCharFormat(cf);
	m_RichEdit1->LineScroll(m_RichEdit1->GetLineCount()-lineCount);
	m_RichEdit1->SetSel(0,0);

	int itemNumber=lc->GetItemCount();
	CMapStringToOb *mapSocket=&(((CCSocketDemoApp*)AfxGetApp())->mapSocket);
	
	UINT uSelectedCount = lc->GetSelectedCount();
	int  nItem = -1;
	CString ip,port,key;

	if (theApp.isServer)
	{
		buf=CString("<?PlainMsg?>:")+buf;	
		/*if (uSelectedCount > 0)
		{
			for (UINT i=0;i<uSelectedCount;i++)
			{
				nItem = lc->GetNextItem(nItem, LVNI_SELECTED);
				ip=lc->GetItemText(nItem,1);
				port=lc->GetItemText(nItem,2);
				key.Format("%s%s",ip,port);
				CServerSocket* tempSocket;
				ret=mapSocket->Lookup(key,(CObject*&)tempSocket);
				if (ret)
					ret=tempSocket->Send(buf.GetBuffer(0),buf.GetLength()+1);
			}
		}*/
		for (int j=0;j<lc->GetItemCount();j++)
		{
			if(lc->GetCheck(j))
			{
				ip=lc->GetItemText(j,1);
				port=lc->GetItemText(j,2);
				key.Format("%s%s",ip,port);
				CServerSocket* tempSocket;
				ret=mapSocket->Lookup(key,(CObject*&)tempSocket);
				if (ret)
					ret=tempSocket->Send(buf.GetBuffer(0),buf.GetLength()+1);
			}
		}
	}
	else
	{
		buf=CString("<?PlainMsg?>:")+buf;		
		/*if (uSelectedCount > 0)
		{
			for (UINT i=0;i<uSelectedCount;i++)
			{
				nItem = lc->GetNextItem(nItem, LVNI_SELECTED);
				ip=lc->GetItemText(nItem,1);
				port=lc->GetItemText(nItem,2);
				UINT uport;
				sscanf(port.GetBuffer(0),"%u",&uport);
				ret=m_chatSocket.SendTo(buf.GetBuffer(0),buf.GetLength()+1,uport,ip);
			}
		}*/
		for (int j=0;j<lc->GetItemCount();j++)
		{
			if(lc->GetCheck(j))
			{
				ip=lc->GetItemText(j,1);
				port=lc->GetItemText(j,2);
				UINT uport;
				sscanf(port.GetBuffer(0),"%u",&uport);
				ret=m_chatSocket.SendTo(buf.GetBuffer(0),buf.GetLength()+1,uport,ip);
			}
		}
	}
	if (ret==SOCKET_ERROR)
	{
		AfxMessageBox("发送数据出错,对方可能已离线。",MB_ICONWARNING);
	}
	SetDlgItemText(IDC_EDIT_MSG,"");
	GetDlgItem(IDC_EDIT_MSG)->SetFocus();
}

void CCSocketDemoDlg::OnButtonEstab() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ESTAB)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	SetDlgItemText(IDC_STATIC_TITLE,"Appler-服务器");
	SetWindowText("Appler-服务器");

	nd.hIcon = m_redApple;      
	strcpy(nd.szTip, "Appler服务器正在运行..."); 
	Shell_NotifyIcon(NIM_MODIFY, &nd);
	int ret=InitAsyncSocket();
	if (ret==0)
	{
		AfxMessageBox("TCP监听失败:初始化异步套接字失败！\n点击 确定 结束程序。",MB_ICONERROR);
		PostQuitMessage(0);
	}
	theApp.isServer=1;
	m_listenSocket.pcwnd=AfxGetApp()->GetMainWnd();
	CString ip=((CCSocketDemoApp*)AfxGetApp())->localIP;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->SetAddress(ntohl(inet_addr(ip.GetBuffer(0))));
}

void CCSocketDemoDlg::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_IPADDRESS1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ESTAB)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	SetDlgItemText(IDC_BUTTON_CONNECT,"正在连接...");
	strcpy(nd.szTip, "Appler即时通讯");   
	Shell_NotifyIcon(NIM_MODIFY, &nd);
	theApp.isServer=0;
	UINT portno;
	int ret=m_clientSocket.Create(0,SOCK_STREAM,FD_CONNECT|FD_READ|FD_CLOSE,((CCSocketDemoApp*)AfxGetApp())->localIP);
	m_clientSocket.GetSockName(CString(""),portno);
	int ret1=m_chatSocket.Create(portno,SOCK_DGRAM,FD_READ|FD_CLOSE,NULL);
	int ret2=InitClientAsyncSocket();
	if (!ret || !ret1 || !ret2)
	{
		AfxMessageBox("创建客户端套接字失败",MB_ICONERROR);
	}
	CString ip;
	//UINT port;

	DWORD dwIP;
	int len=sizeof(SOCKADDR);
	SOCKADDR_IN addrTo;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);
	addrTo.sin_addr.S_un.S_addr=htonl(dwIP);
	
	addrTo.sin_family=AF_INET;
	addrTo.sin_port=htons(8888);
	
	ret=m_clientSocket.Connect((SOCKADDR*)&addrTo,len);
	if (ret)
	{
		//AfxMessageBox("连接服务器成功");
		//m_clientSocket.GetSockName(ip,port);
		//m_clientSocket.Send((ip+" comes in").GetBuffer(0),ip.GetLength()+10);
	}
	else
	{
		//AfxMessageBox("连接失败");
	}

}

void CCSocketDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CRect rect;
	GetClientRect(&rect);
	if (rect.Width()<501)
	{
		return;
	}
	ClxDialog::OnSize(nType, cx, cy);	
	// TODO: Add your message handler code here
}

void CCSocketDemoDlg::OnButtonClose() 
{
	// TODO: Add your control notification handler code here
	m_btnClose.ResetWhenClose();
	GetDlgItem(IDC_EDIT_MSG)->SetFocus();
	OnClose();
	//PostQuitMessage(0);
}

UINT CCSocketDemoDlg::OnNcHitTest(CPoint point)
{
	UINT nHitTest = CDialog::OnNcHitTest (point);
	if (nHitTest==HTCLIENT)
	{
		nHitTest=HTCAPTION;
	}
	return nHitTest;
	/*CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	return rc.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);*/
}

void CCSocketDemoDlg::OnButtonAbout() 
{
	// TODO: Add your control notification handler code here
	m_btnAbout.ResetWhenClose();
	this->SetFocus();
	CAboutDlg dlg;
	dlg.DoModal();
}

BOOL CCSocketDemoDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rcrect;
	GetClientRect(&rcrect);
	CBitmap m_BkGndBmp;
	m_BkGndBmp.LoadBitmap(IDB_BITMAP_BK);
	BITMAP bm;
	m_BkGndBmp.GetBitmap(&bm);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBmp=memDC.SelectObject(&m_BkGndBmp);
	//pDC->StretchBlt(0,0,rcrect.Width(),rcrect.Height(),&memDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	pDC->StretchBlt(0,0,1600,1200,&memDC,0,0,bm.bmWidth,bm.bmHeight,SRCCOPY);
	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

void CCSocketDemoDlg::OnButtonMaxmize() 
{
	// TODO: Add your control notification handler code here
	if (isMax==1)
	{
		ShowWindow(SW_SHOWNORMAL);
	}
	else
	{
		CRect rcWorkArea; 
		SystemParametersInfo(SPI_GETWORKAREA,0,(LPVOID)&rcWorkArea,0); 
		ShowWindow(SW_MAXIMIZE);
		MoveWindow(&rcWorkArea);
	}
	isMax=!isMax;
	m_btnMaxmize.ResetWhenClose();
	this->SetFocus();
}

void CCSocketDemoDlg::OnButtonMinimize() 
{
	// TODO: Add your control notification handler code here
	ShowWindow(SW_MINIMIZE);
	m_btnMinmize.ResetWhenClose();
}

void CCSocketDemoDlg::OnContextMenu(CWnd*, CPoint point)
{
	int owner=0;//代表用户列表的右键菜单

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CRect listRect;
		GetDlgItem(IDC_LIST_CLIENT)->GetWindowRect(&listRect);
		BOOL tag=(point.x>listRect.left)&&(point.x<listRect.right);
		BOOL _tag=(point.y>listRect.top)&&(point.y<listRect.bottom);
		if (tag&&_tag)
			owner=1;

		GetDlgItem(IDC_RICHEDIT_CONTENT)->GetWindowRect(&listRect);
		tag=(point.x>listRect.left)&&(point.x<listRect.right);
		_tag=(point.y>listRect.top)&&(point.y<listRect.bottom);
		if (tag&&_tag)
			owner=2;

		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_POPUPMENU));

		CMenu* pPopup;
		if (owner==1)//用户列表
		{
			if (theApp.isServer)
				pPopup=menu.GetSubMenu(3);//服务器 多了一个踢出
			else
				pPopup=menu.GetSubMenu(1);//客户端
		}
		else if (owner==2)//聊天内容区
		{
			pPopup=menu.GetSubMenu(0);
		}
		else
		{
			return;
		}
		
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		CListCtrl* listCtrl=(CListCtrl*)GetDlgItem(IDC_LIST_CLIENT);
		int count=listCtrl->GetSelectedCount();
		if (count<=0)
		{
			pPopup->EnableMenuItem(ID_USER_SENDFILE,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
			pPopup->EnableMenuItem(ID_USER_VIDEOCHAT,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
			pPopup->EnableMenuItem(ID_SERVER_KICK,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
		}
		if (theApp.enableVideoChat==FALSE)//视频初始化失败后 禁止视频通信
		{
			pPopup->EnableMenuItem(ID_USER_VIDEOCHAT,MF_BYCOMMAND|MF_DISABLED|MF_GRAYED);
		}


		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

void CCSocketDemoDlg::OnUserSendfile() 
{
	// TODO: Add your command handler code here
	if (theApp.isServer==0)
	{
		TransferFileBetweenClient();
		return;
	}
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrTitle="请选择要发送的文件";
	dlg.m_ofn.lpstrFilter="所有文件(*.*)\0*.*\0压缩文件(*.rar,*.zip)\0*.rar,*.zip\0";
	if (IDOK==dlg.DoModal())
	{
		filePath=dlg.GetPathName();
		fileName=dlg.GetFileName();
	}
	else{return;}
	DWORD len;
	CFile file;
	file.Open(filePath,CFile::modeRead|CFile::typeBinary,NULL);
	len=file.GetLength();
	file.Close();
	CString buf,fileLen;
	fileLen.Format("%u",len);
	int ret;
	CListCtrl *lc=(CListCtrl*)GetDlgItem(IDC_LIST_CLIENT);
	int itemNumber=lc->GetItemCount();
	CMapStringToOb *mapSocket=&(((CCSocketDemoApp*)AfxGetApp())->mapSocket);
	
	UINT uSelectedCount = lc->GetSelectedCount();
	int  nItem = -1;
	CString ip,port,key;
	// Update all of the selected items.
	if (uSelectedCount > 0)
	{
		for (UINT i=0;i<uSelectedCount;i++)
		{
			nItem = lc->GetNextItem(nItem, LVNI_SELECTED);
			ip=lc->GetItemText(nItem,1);
			port=lc->GetItemText(nItem,2);
			key.Format("%s%s",ip,port);
			CServerSocket* tempSocket;
			ret=mapSocket->Lookup(key,(CObject*&)tempSocket);
			if (ret)
			{
				temp_socket=tempSocket;
				temp_socket->filePath=filePath;
				temp_socket->fileName=fileName;
				temp_socket->Send(CString("<?Request FILETRANSFER?>:"+fileName+":"+fileLen),512);
			}
			else
				MessageBox("无权限执行此操作！","发送失败",MB_ICONERROR);
		}
	}
	if (ret==SOCKET_ERROR)
	{
		AfxMessageBox("发送数据出错",MB_ICONWARNING);
	}
	
}

void CCSocketDemoDlg::TransferFileBetweenClient()
{
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrTitle="请选择要发送的文件";
	dlg.m_ofn.lpstrFilter="所有文件(*.*)\0*.*\0压缩文件(*.rar,*.zip)\0*.rar,*.zip\0";
	if (IDOK==dlg.DoModal())
	{
		filePath=dlg.GetPathName();
		fileName=dlg.GetFileName();
	}
	else{return;}
	DWORD len;
	CFile file;
	file.Open(filePath,CFile::modeRead|CFile::typeBinary,NULL);
	len=file.GetLength();
	file.Close();
	CString buf,fileLen;
	fileLen.Format("%u",len);
	int ret;
	CListCtrl *lc=(CListCtrl*)GetDlgItem(IDC_LIST_CLIENT);
	int itemNumber=lc->GetItemCount();
	
	UINT uSelectedCount = lc->GetSelectedCount();
	int  nItem = -1;
	CString ip,port,key;
	// Update all of the selected items.
	if (uSelectedCount > 0)
	{
		for (UINT i=0;i<uSelectedCount;i++)
		{
			nItem = lc->GetNextItem(nItem, LVNI_SELECTED);
			ip=lc->GetItemText(nItem,1);
			port=lc->GetItemText(nItem,2);
			CClientCliSocket* tempSocket=new CClientCliSocket();
			tempSocket->Create(0,SOCK_STREAM,FD_READ|FD_CONNECT|FD_CLOSE,theApp.localIP);
			if (ret)
			{
				tempSocket->filePath=filePath;
				tempSocket->fileName=fileName;
				tempSocket->fileLen=fileLen;
				tempSocket->pcwnd=theApp.GetMainWnd();
				tempSocket->Connect(ip,8989);
				//tempSocket->Send(CString("<?Request FILETRANSFER?>:"+fileName+":"+fileLen),256);
			}
		}
	}
	if (ret==SOCKET_ERROR)
	{
		AfxMessageBox("发送数据出错");
	}
}

HRESULT CCSocketDemoDlg::MakeCall(RTC_SESSION_TYPE enType, BSTR bstrURI)
{
    HRESULT hr;
	if (enType != RTCST_IM)
    {
		if ((m_AVDlg) && (m_AVDlg.GetState () != RTCSS_IDLE))
        {
			MessageBoxW (m_hWnd, L"An audio/video call is in progress!", NULL, MB_OK );
            return S_FALSE;
        }
    }
    IRTCSession * pSession = NULL;
    hr = m_pClient->CreateSession(enType, NULL, NULL, 0, &pSession);
    if (FAILED(hr))
    {
        return hr;
    }
    
    hr = pSession->AddParticipant(bstrURI, NULL, &m_Participant);
	if (FAILED(hr))
    {
        SAFE_RELEASE(pSession);
        return hr;
    }
    
    hr = AddSession(pSession, enType);
    
    if (FAILED(hr))
    {  
		
        return hr;
    }
    return S_OK;
}

HRESULT CCSocketDemoDlg::InitRTCClient()
{
	HRESULT hr;
	m_pClient = NULL;
	m_pEvents = NULL;
	
	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		return hr;
	}
	hr = CoCreateInstance (CLSID_RTCClient, NULL,
		CLSCTX_INPROC_SERVER, IID_IRTCClient,
		(LPVOID *)&m_pClient);
	if (FAILED(hr))
	{
		return hr;
	}
	hr = m_pClient->Initialize();
	if (FAILED(hr))
	{
		SAFE_RELEASE(m_pClient);
		return hr;
	}
	m_pClient->SetPreferredMediaTypes ( RTCMT_ALL, VARIANT_TRUE );
	long lEventMask = RTCEF_SESSION_STATE_CHANGE |
		RTCEF_MESSAGING |
		RTCEF_MEDIA |
		RTCEF_INTENSITY |
		RTCEF_CLIENT;
	hr = m_pClient->put_EventFilter( lEventMask );
    if ( FAILED(hr) )
    {
        SAFE_RELEASE(m_pClient);
        return hr;
    }
    m_pEvents = new CRTCEvents;
    if (!m_pEvents)
    {
        SAFE_RELEASE(m_pClient);
        return hr;
    }
    hr = m_pEvents->Advise( m_pClient, m_hWnd );
    if ( FAILED(hr) )
    {
        SAFE_RELEASE(m_pClient);
        return hr;
    }
    
    hr = m_pClient->put_ListenForIncomingSessions(RTCLM_BOTH); 
	
    if ( FAILED(hr) )
    {
		
        SAFE_RELEASE(m_pClient);
        return hr;
    }
	
	if (m_AVDlg)
		m_AVDlg.SetState (RTCSS_IDLE);
	return S_OK;
}

LRESULT CCSocketDemoDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message)
	{
	case WM_RTC_EVENT:
		OnRTCEvent (message, wParam, lParam);
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

HRESULT CCSocketDemoDlg::OnRTCEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
    IDispatch * pDisp = (IDispatch *)lParam;
    RTC_EVENT enEvent = (RTC_EVENT)wParam;
    HRESULT hr;
	
    switch ( wParam )
    {
	case RTCE_SESSION_STATE_CHANGE:
		{
			IRTCSessionStateChangeEvent * pEvent = NULL;
			
			
			hr = pDisp->QueryInterface( IID_IRTCSessionStateChangeEvent,
				(void **)&pEvent );
			if (SUCCEEDED(hr))
			{
				OnRTCSessionStateChangeEvent(pEvent);
				SAFE_RELEASE(pEvent);
			}              
		}
		break;
	case RTCE_MESSAGING:
		{
			IRTCMessagingEvent * pEvent = NULL;
			
			
			hr = pDisp->QueryInterface( IID_IRTCMessagingEvent,
				(void **)&pEvent );
			if (SUCCEEDED(hr))
			{
				OnRTCMessagingEvent(pEvent);
				SAFE_RELEASE(pEvent);
			}              
		}
		break;
	case RTCE_MEDIA:
		{
			IRTCMediaEvent * pEvent = NULL;
			
			hr = pDisp->QueryInterface( IID_IRTCMediaEvent,
				(void **)&pEvent );
			if (SUCCEEDED(hr))
			{
				OnRTCMediaEvent(pEvent);
				SAFE_RELEASE(pEvent);
			}
		}
		break;
	case RTCE_INTENSITY:
		{
			IRTCIntensityEvent * pEvent = NULL;
			
			hr = pDisp->QueryInterface( IID_IRTCIntensityEvent,
				(void **)&pEvent );
			if (SUCCEEDED(hr))
			{
				OnRTCIntensityEvent(pEvent);
				SAFE_RELEASE(pEvent);
			}
		}
		break;
	case RTCE_CLIENT:
		{
			IRTCClientEvent * pEvent = NULL;
			
			hr = pDisp->QueryInterface( IID_IRTCClientEvent,
				(void **)&pEvent );
			if (SUCCEEDED(hr))
			{
				OnRTCClientEvent(pEvent);
				SAFE_RELEASE(pEvent);
			}
		}
		break;
    }
    
    SAFE_RELEASE(pDisp);
    return S_OK;
}

void CCSocketDemoDlg::OnRTCSessionStateChangeEvent(IRTCSessionStateChangeEvent *pEvent)
{
    IRTCSession * pSession = NULL;
    RTC_SESSION_STATE enState;
    HRESULT hr;
    
	hr = pEvent->get_State(&enState);
    if (FAILED(hr))
    {
        
        return;
    }
    
	hr = pEvent->get_Session(&pSession);
    if (FAILED(hr))
    {
        
        return;
    }
    switch ( enState )
	{
	case RTCSS_INCOMING:
        {
			
            
            RTC_SESSION_TYPE enType;
            
			hr = pSession->get_Type(&enType);
            if (FAILED(hr))
            {
                
                SAFE_RELEASE(pSession);
                return;
            }            
            if (enType == RTCST_IM)
            {
                
                m_pClient->PlayRing(RTCRT_MESSAGE, VARIANT_TRUE);
            }
            else            
            {
                
                if ((m_AVDlg) && (m_AVDlg.GetState() != RTCSS_IDLE))
                {
                    
                    
                    pSession->Terminate(RTCTR_BUSY);
                    SAFE_RELEASE(pSession);
                    return;
                }
				
                
                IRTCEnumParticipants * pEnum = NULL;
                IRTCParticipant * pParticipant = NULL;
                hr = pSession->EnumerateParticipants(&pEnum);
                if (FAILED(hr))
                {
                    
                    SAFE_RELEASE(pSession);
                    return;
                }
                hr = pEnum->Next(1, &pParticipant, NULL);
                SAFE_RELEASE(pEnum);
                if (hr != S_OK)
                {
                    
                    SAFE_RELEASE(pSession);
                    return;
                }
                
                BSTR bstrURI = NULL;
                hr = pParticipant->get_UserURI(&bstrURI);
                if (FAILED(hr))
                {
                    
                    SAFE_RELEASE(pSession);
                    SAFE_RELEASE(pParticipant);
                    return;
                }
                
                BSTR bstrName = NULL;
                hr = pParticipant->get_Name(&bstrName);
                SAFE_RELEASE(pParticipant);
                if (FAILED(hr))
                {
                    
                    SAFE_FREE_STRING(bstrURI);
                    SAFE_RELEASE(pSession);
                    return;
                }
                
                m_pClient->PlayRing(RTCRT_PHONE, VARIANT_TRUE);
                
                BOOL fAccept;
				CIncomingDlg	cDlg;	   
				SESSION_DATA	pData;
				pData.bstrName = bstrName;
				pData.bstrURI = bstrURI;
				SetWindowLong ( m_hWnd, GWL_USERDATA, (LONG)&pData);
				
				
				fAccept = (cDlg.DoModal() == IDOK);
				
				SAFE_FREE_STRING(bstrURI);
				SAFE_FREE_STRING(bstrName);
				
                if (fAccept)
                {
                    
                    hr = pSession->Answer();
                    if (FAILED(hr))
                    {
                        
                        SAFE_RELEASE(pSession);
                        return;
                    }
                }
                else
                {
                    
                    pSession->Terminate(RTCTR_REJECT);
					SAFE_RELEASE(pSession);
                    return;
                }
            }  
            
            
            
            hr = AddSession(pSession, enType);
            if (FAILED(hr))
            {
                
                SAFE_RELEASE(pSession);
                return;
            }
        }        
		break;
	}
    
	if (m_AVDlg)
		m_AVDlg.SetState (enState);
}

void CCSocketDemoDlg::OnRTCMediaEvent(IRTCMediaEvent *pEvent)
{
    long lMediaType;
    RTC_MEDIA_EVENT_TYPE enType;
    RTC_MEDIA_EVENT_REASON enReason;
    HRESULT hr;
	hr = pEvent->get_MediaType(&lMediaType);
    if (FAILED(hr))
    {
        
        return;
    }
    hr = pEvent->get_EventType(&enType);			  
    if (FAILED(hr))
    {
        
        return;
    }
    hr = pEvent->get_EventReason(&enReason);
    if (FAILED(hr))
    {
        
        return;
    }
	if ((m_AVDlg) && (m_AVDlg.GetState () != RTCSS_IDLE))
    {
        
        m_AVDlg.DeliverMedia(lMediaType, enType, enReason);
    }
}

void CCSocketDemoDlg::OnRTCIntensityEvent(IRTCIntensityEvent *pEvent)
{
    RTC_AUDIO_DEVICE enDevice;
    long lLevel, lMin, lMax;
    HRESULT hr;
    
	hr = pEvent->get_Direction(&enDevice);
    if (FAILED(hr))
    {
        
        return;
    }
    hr = pEvent->get_Level(&lLevel);
    if (FAILED(hr))
    {
        
        return;
    }
    hr = pEvent->get_Min(&lMin);
    if (FAILED(hr))
    {
        
        return;
    }
    hr = pEvent->get_Max(&lMax);
    if (FAILED(hr))
    {
        
        return;
    }
    
    if ((lMax - lMin) == 0)
    {
        lLevel = 0;
    }
    else
    {
        lLevel = (lLevel - lMin) * 100 / (lMax - lMin);
    }
	if (m_AVDlg.GetState () != RTCSS_IDLE)
    {
        
        m_AVDlg.DeliverIntensity(enDevice, lLevel);
    }
}

void CCSocketDemoDlg::OnRTCClientEvent(IRTCClientEvent *pEvent)
{
    HRESULT hr;
    
    RTC_CLIENT_EVENT_TYPE enEventType;
    hr = pEvent->get_EventType(&enEventType);
    if (FAILED(hr))
    {
        
        return;
    }
    if ( enEventType == RTCCET_ASYNC_CLEANUP_DONE )
    {
        m_pClient->Shutdown();
		SAFE_RELEASE(m_pClient);
		
        
        DestroyWindow();
    }
    else
    {
        if (m_AVDlg.GetState() != RTCSS_IDLE)
        {
            
            m_AVDlg.DeliverClient(enEventType);
        }
    }
}

HRESULT CCSocketDemoDlg::AddSession(IRTCSession *pSession, RTC_SESSION_TYPE enType)
{
    
    BOOL fAVSession = (enType != RTCST_IM);
    
	
	if (fAVSession)
	{
		BOOL ret = m_AVDlg.Create (IDD_AVDLG,GetDesktopWindow());
		if (!ret)
		{
			MessageBox ( "Error Creating Dialog" );
		}
		m_AVDlg.ShowWindow (SW_SHOW);
		m_AVDlg.SetParentClient (m_pClient);
		m_AVDlg.SetSession (pSession);
	}
	return S_OK;
}

HRESULT CCSocketDemoDlg::OnRTCMessagingEvent(IRTCMessagingEvent *pEvent)
{
    IRTCSession * pSession = NULL;
    
    IRTCParticipant * pParticipant = NULL;
    RTC_MESSAGING_EVENT_TYPE enType;
    RTC_MESSAGING_USER_STATUS enStatus;
    BSTR bstrContentType = NULL;
    BSTR bstrMessage = NULL;
    HRESULT hr;
    hr = pEvent->get_Session(&pSession);
    if (FAILED(hr))
    {
        
        return S_FALSE;
    }
    
    hr = pEvent->get_EventType(&enType);
    if (FAILED(hr))
    {
        
        return S_FALSE;
    }
    hr = pEvent->get_Participant(&pParticipant);
    if (FAILED(hr))
    {
        
        return S_FALSE;
    }
    if (enType == RTCMSET_MESSAGE)
    {
        hr = pEvent->get_MessageHeader(&bstrContentType);
        if (FAILED(hr))
        {
            
            SAFE_RELEASE(pParticipant);
            return S_FALSE;
        }
        hr = pEvent->get_Message(&bstrMessage);
        if (FAILED(hr))
        {
            
            SAFE_RELEASE(pParticipant);
            SAFE_FREE_STRING(bstrContentType);
            return S_FALSE;
        }
        
        SAFE_FREE_STRING(bstrContentType);
        SAFE_FREE_STRING(bstrMessage);
    }
    else if (enType == RTCMSET_STATUS)
    {
        hr = pEvent->get_UserStatus(&enStatus);
        if (FAILED(hr))
        {
            
            return S_FALSE;
        }
    }
    SAFE_RELEASE(pParticipant); 
	
	return S_OK;
}

void CCSocketDemoDlg::OnUserVideochat() 
{
	// TODO: Add your command handler code here
	CListCtrl *lc=(CListCtrl*)GetDlgItem(IDC_LIST_CLIENT);
	
	UINT uSelectedCount = lc->GetSelectedCount();
	int  nItem = -1;
	CString ip;
	// Update all of the selected items.
	if (uSelectedCount > 0)
	{
		for (UINT i=0;i<uSelectedCount;i++)
		{
			nItem = lc->GetNextItem(nItem, LVNI_SELECTED);
			ip=lc->GetItemText(nItem,1);
			g_bstrAddr=ip.AllocSysString();
			MakeCall (RTCST_PC_TO_PC, g_bstrAddr);
		}
	}
}

void CCSocketDemoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}

void CCSocketDemoDlg::OnNotifyIcon(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)
	{
	case WM_LBUTTONDBLCLK:// 双击左键
		ShowWindow(SW_SHOWNORMAL);//显示主界面窗体
		SetForegroundWindow();
		if (theApp.isServer==0)
		{
			strcpy(nd.szTip, "Appler即时通讯");   
			nd.hIcon=m_hIcon;
			Shell_NotifyIcon(NIM_MODIFY, &nd);
			KillTimer(2);
		}
		break;
	case WM_RBUTTONDOWN://点击右键
		{
			CMenu pMenu;
			CMenu* pPopup;
			if (pMenu.LoadMenu(IDR_POPUPMENU)) //加载托盘的菜单栏       
				pPopup = pMenu.GetSubMenu(2);
			ASSERT(pPopup != NULL);
			CPoint Point;
			if (IsWindowVisible())
			{
				pPopup->EnableMenuItem(ID_POPUP_SHOW,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				pPopup->EnableMenuItem(ID_POPUP_TRAY,MF_BYCOMMAND | MF_ENABLED);
			}
			else
			{
				pPopup->EnableMenuItem(ID_POPUP_TRAY,MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
				pPopup->EnableMenuItem(ID_POPUP_SHOW,MF_BYCOMMAND | MF_ENABLED);
			}			
			GetCursorPos(&Point);
			pPopup->TrackPopupMenu(TPM_RIGHTALIGN|TPM_RIGHTBUTTON,Point.x,Point.y,this);
		}
		break;
	default:
		break;
	}
}

void CCSocketDemoDlg::OnPopupShow() 
{
	// TODO: Add your command handler code here
	ShowWindow(SW_SHOWNORMAL);
	this->SetForegroundWindow();
	if (theApp.isServer==0)
	{
		strcpy(nd.szTip, "Appler即时通讯");   
		nd.hIcon=m_hIcon;
		Shell_NotifyIcon(NIM_MODIFY, &nd);
		KillTimer(2);
	}
}

void CCSocketDemoDlg::OnPopupTray() 
{
	// TODO: Add your command handler code here
	ShowWindow(SW_HIDE);
}

void CCSocketDemoDlg::OnPopupExit() 
{
	// TODO: Add your command handler code here
	Shell_NotifyIcon(NIM_DELETE, &nd);
	::PostQuitMessage(0);
}

void CCSocketDemoDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent==1)
    {        
        if (::GetActiveWindow()==m_hWnd)
        {
			flashWindowCount=0;
            KillTimer(1);
        }
        else
        {
			if (flashWindowCount<=2)
			{
				FlashWindow(TRUE);
				flashWindowCount++;
			}
			else
			{
				flashWindowCount=0;
				KillTimer(1);
			}
            
        }        
    }
	else if (nIDEvent==2)
	{
		if (flashicon==1)
		{
			strcpy(nd.szTip, "Appler-你有新的消息");   
			nd.hIcon=m_redApple;
			Shell_NotifyIcon(NIM_MODIFY, &nd);
		}
		else
		{
			strcpy(nd.szTip, "Appler-你有新的消息");   
			nd.hIcon = m_hIcon;      
			Shell_NotifyIcon(NIM_MODIFY, &nd);
		}
		flashicon=!flashicon;
	}
	else{}

	CDialog::OnTimer(nIDEvent);
}

void CCSocketDemoDlg::OnEditCopy() 
{
	// TODO: Add your command handler code here
	CRichEditCtrl *rec=(CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_CONTENT);
	rec->Copy();
}

void CCSocketDemoDlg::OnEditClear() 
{
	// TODO: Add your command handler code here
	CRichEditCtrl *rec=(CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT_CONTENT);
	rec->SetReadOnly(FALSE);
	rec->SetSel(0,-1);
	rec->Clear();
	rec->SetReadOnly(TRUE);
}

void CCSocketDemoDlg::OnServerKick() 
{
	// TODO: Add your command handler code here
	CListCtrl* lc=(CListCtrl*)GetDlgItem(IDC_LIST_CLIENT);
	CMapStringToOb *mapSocket=&(((CCSocketDemoApp*)AfxGetApp())->mapSocket);
	
	UINT uSelectedCount = lc->GetSelectedCount();
	int  nItem = -1;
	CString buf,ip,port,key;
	int ret;

	if (theApp.isServer)
	{
		buf="<?Command Kick?>";
		if (uSelectedCount > 0)
		{
			if (MessageBox("确定要踢出所选用户吗？",NULL,MB_ICONQUESTION|MB_YESNO)==IDNO)
				return;
			for (UINT i=0;i<uSelectedCount;i++)
			{
				nItem = lc->GetNextItem(nItem, LVNI_SELECTED);
				ip=lc->GetItemText(nItem,1);
				port=lc->GetItemText(nItem,2);
				key.Format("%s%s",ip,port);
				CServerSocket* tempSocket;
				ret=mapSocket->Lookup(key,(CObject*&)tempSocket);
				if (ret)
					ret=tempSocket->Send(buf.GetBuffer(0),buf.GetLength()+1);
			}
		}
	}
}

LRESULT CCSocketDemoDlg::OnHotKey(WPARAM wParam,LPARAM lParam)
{
	OnPopupShow();
	return 1;
}