// ChatSocket.cpp : implementation file
//

#include "stdafx.h"
#include "CSocketDemo.h"
#include "ChatSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatSocket

CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CChatSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CChatSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CChatSocket member functions

void CChatSocket::OnReceive(int nErrorCode)
{
	CString host,ip;
	UINT port;
	CString buf,text;
	CString _fileName;
	byte* mybuf=new byte[1024*10];
	int total=ReceiveFrom(mybuf,1024*10,ip,port);
	buf.Format("%s",mybuf);
	int isTxtMsg=1;


	if (AfxGetMainWnd()->IsWindowVisible()==FALSE)
		AfxGetMainWnd()->SetTimer(2,800,NULL);//flash icon
	else
		AfxGetMainWnd()->SetTimer(1,800,NULL);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_MSG),AfxGetInstanceHandle(),SND_RESOURCE|SND_ASYNC|SND_NOWAIT);

	if (isTxtMsg==0)
	{
		delete[] mybuf;
		buf.Empty();
		return;
	}


	CRichEditCtrl *m_RichEdit1;
	CWnd *pcwnd=AfxGetApp()->GetMainWnd();
	m_RichEdit1=(CRichEditCtrl*)pcwnd->GetDlgItem(IDC_RICHEDIT_CONTENT);
	SOCKADDR_IN addrFrom;
	int len=sizeof(SOCKADDR);
	CString msg;
	HOSTENT *pHost;
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
	
	//ReceiveFrom(buf.GetBuffer(2056),2056,(SOCKADDR*)&addrFrom,&len);

	DWORD peerIP=inet_addr(ip.GetBuffer(0));  
	pHost=gethostbyaddr((LPSTR)&peerIP,4,AF_INET); 

	buf=buf.Right(buf.GetLength()-13);

	CTime time=CTime::GetCurrentTime();
	CString currentTime;
	currentTime.Format("          %02d:%02d:%02d",time.GetHour(),time.GetMinute(),time.GetSecond());

	host.Format("%s%s",pHost->h_name,currentTime);
	msg.Format("\r\n  %s\r\n",buf);

	cf.yHeight = 13*13;//文字高度
	cf.crTextColor = RGB(0,110,254); //文字颜色
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

	delete[] mybuf;
	buf.Empty();

	CAsyncSocket::OnReceive(nErrorCode);
}

void CChatSocket::OnClose(int nErrorCode)
{
	Close();
	
	CAsyncSocket::OnClose(nErrorCode);
}
