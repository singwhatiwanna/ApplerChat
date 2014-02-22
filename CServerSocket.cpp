// CServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "CSocketDemo.h"
#include "CServerSocket.h"
#include "CSocketDemoDlg.h"
#include "SendFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCSocketDemoApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CServerSocket

CServerSocket::CServerSocket()
{
	pcwnd=AfxGetApp()->GetMainWnd();tag=1;goon=1;
	CString localHost;
	gethostname(localHost.GetBuffer(128),128);//get local ipaddress and hostname
	localHost.ReleaseBuffer();
	struct hostent* pHost;
	pHost=gethostbyname(localHost);
	localIp=inet_ntoa(*(struct in_addr*)pHost->h_addr_list[0]);
	fileTran=NULL;
	already=0;
}

CServerSocket::~CServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CServerSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CServerSocket member functions
void CServerSocket::OnReceive(int nErrorCode)
{
	CString host,ip;UINT port;
	CString buf,text;
	CString _fileName;
	Receive(buf.GetBuffer(2056),2056);
	buf.ReleaseBuffer();
	GetPeerName(ip,port);


	if(buf.Find("<?Response FILETRANSFER?>:ACCEPT")>-1)
	{
		//AfxMessageBox("对方同意接收");
		file.Open(filePath,CFile::modeRead|CFile::typeBinary,NULL);
		remainder=file.GetLength();
		CString csRemainder;
		csRemainder.Format("%u",remainder);
		if (!fileTran)
		{
			CSendFileDlg *sfDlg=new CSendFileDlg(SOCKETTYPESERVER,this);
			sfDlg->Create(IDD_SENDFILE_DIALOG,CWnd::FromHandle(::GetDesktopWindow()));
			fileTran=sfDlg;
			fileTran->ShowWindow(SW_SHOW);
		}
		fileTran->SetDlgItemText(IDC_STATIC_SRCA,localIp);
		fileTran->SetDlgItemText(IDC_STATIC_DESA,thePeerIp);
		fileTran->SetDlgItemText(IDC_STATIC_FINFO,fileName+"\n大小: "+csRemainder+" 字节");
		CProgressCtrl *proSF=(CProgressCtrl*)fileTran->GetDlgItem(IDC_PROGRESS_TRANFILE);
		proSF->SetRange32(0,remainder);
		proSF->SetPos(0);


		TransferFile(filePath);
		return;
	}
	else if (buf.Find("<?Response FILETRANSFER?>:REFUSE")>-1)
	{
		AfxMessageBox("对方不同意接收该文件.",MB_ICONWARNING);
		return;
	}
	else if (buf.Find("<?FileContinue?>")>-1)
	{
		if (remainder<=0)
		{
			if (tag==0)
			{
				return;
			}
			tag=0;
			Send("<?FileStop?>",256);
			file.Close();
			AfxMessageBox("发送已完成.",MB_ICONINFORMATION);
			tag=1;
		}
		else
		{
			TransferFile(filePath);
		}
		return;
	}
	else{}


	CRichEditCtrl *m_RichEdit1;
	pcwnd=AfxGetApp()->GetMainWnd();
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

	int pos=buf.GetLength();
	buf=buf.Right(pos-13);

	CTime time=CTime::GetCurrentTime();
	CString currentTime;
	currentTime.Format("          %02d:%02d:%02d",time.GetHour(),time.GetMinute(),time.GetSecond());
	
	host.Format("%s%s",pHost->h_name,currentTime);
	msg.Format("  \r\n  %s\r\n",buf);

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

	CAsyncSocket::OnReceive(nErrorCode);
}

void CServerSocket::OnClose(int nErrorCode)
{
	CString key,temp;
	key.Format("%s%d",thePeerIp,thePeerPort);
	temp.Format("%d",thePeerPort);
	CMapStringToOb *mapSocket=&(((CCSocketDemoApp*)AfxGetApp())->mapSocket);
	if (mapSocket->GetCount()>0)
	{
		mapSocket->RemoveKey(key);
	}
	UpdateClientList();//solve the exit message.
	theApp.NotifyAll("null",thePeerIp,temp,FALSE);

	Close();
	CAsyncSocket::OnClose(nErrorCode);
}

void CServerSocket::OnConnect(int nErrorCode)
{
	CAsyncSocket::OnConnect(nErrorCode);
}

void CServerSocket::UpdateClientList()
{
	CMapStringToOb *mapSocket=&(((CCSocketDemoApp*)AfxGetApp())->mapSocket);
	POSITION pos;
	CString key;
	CServerSocket* tempSocket;
	int itemNumber;
	CString port;
	CListCtrl *lc=(CListCtrl*)pcwnd->GetDlgItem(IDC_LIST_CLIENT);
	lc->DeleteAllItems();

	for(pos = mapSocket->GetStartPosition(); pos!= NULL; )
	{
		mapSocket->GetNextAssoc(pos,key,(CObject*&)tempSocket );
		port.Format("%d",tempSocket->thePeerPort);

		itemNumber=lc->GetItemCount();
		
		lc->InsertItem(itemNumber,key);
		lc->SetItemText(itemNumber,0,tempSocket->host);
		lc->SetItemText(itemNumber,1,tempSocket->thePeerIp);
		lc->SetItemText(itemNumber,2,port);
	}	
}

void CServerSocket::TransferFile(CString path)
{
	char *buf=new char[128];
	byte *contents=new byte[PACKAGESIZE];
	memset(contents,0,PACKAGESIZE);
	int total=-1;
	
	DWORD len=file.GetLength();
	DWORD block=0;
	
	if(file.GetPosition()<len)
	{
		block=(remainder<PACKAGESIZE)?remainder:PACKAGESIZE;
		file.Read(contents,block);
		total=Send(contents,block);
		for (int i=0;total==SOCKET_ERROR && i<3;i++)
		{
			total=Send(contents,block);
		}
		remainder-=total;
		file.Seek(total-block,CFile::current);
		CProgressCtrl *proSF=(CProgressCtrl*)fileTran->GetDlgItem(IDC_PROGRESS_TRANFILE);
		proSF->SetPos(proSF->GetPos()+total);
		CString status;
		status.Format("已发送%u 字节中的%d 字节",len,proSF->GetPos());
		fileTran->SetDlgItemText(IDC_STATIC_STATUS,status);
	}
	delete[] buf;
	delete[] contents;
}

void CServerSocket::OnSend(int nErrorCode)
{
	CAsyncSocket::OnSend(nErrorCode);
}

void CServerSocket::NotifyPeer()
{
	CMapStringToOb *mapSocket=&(((CCSocketDemoApp*)AfxGetApp())->mapSocket);
	POSITION pos;
	CString key;
	CServerSocket* tempSocket;
	CString host,ip,port,msg,rmsg;
	int ret;

	for(pos = mapSocket->GetStartPosition(); pos!= NULL; )
	{
		mapSocket->GetNextAssoc(pos,key,(CObject*&)tempSocket );
		port.Format("%d",tempSocket->thePeerPort);
		if (thePeerIp==tempSocket->thePeerIp && thePeerPort==tempSocket->thePeerPort)
		{
			continue;
		}
		msg.Format("+%s %s %s",tempSocket->host,tempSocket->thePeerIp,port);
		rmsg+=msg;
	}
	ret=Send(CString("<?Command update client list?>")+rmsg,2048);
	while(ret==SOCKET_ERROR)
		ret=Send(CString("<?Command update client list?>")+rmsg,2048);
}

void CServerSocket::NotifyAll(CString host,CString ip,CString port,BOOL enter/* =TRUE */)
{
	CMapStringToOb *mapSocket=&(((CCSocketDemoApp*)AfxGetApp())->mapSocket);
	POSITION pos;
	CString key;
	CServerSocket* tempSocket;
	CString msg;
	int ret;
	if(enter)	msg.Format("+%s %s %s",host,ip,port);
	else	msg.Format("#%s %s %s",host,ip,port);
	
	for(pos = mapSocket->GetStartPosition(); pos!= NULL; )
	{
		mapSocket->GetNextAssoc(pos,key,(CObject*&)tempSocket );
		ret=tempSocket->Send(CString("<?Command update client list?>")+msg,512);
		while(ret==SOCKET_ERROR)
			ret=tempSocket->Send(CString("<?Command update client list?>")+msg,512);
	}
}

void CServerSocket::NotifyAllMembers()
{
	CMapStringToOb *mapSocket=&(((CCSocketDemoApp*)AfxGetApp())->mapSocket);
	POSITION pos,pos1;
	CString key;
	CServerSocket* tempSocket;
	CString host,ip,port,msg,rmsg;
	int ret;

	for(pos = mapSocket->GetStartPosition(); pos!= NULL; )
	{
		mapSocket->GetNextAssoc(pos,key,(CObject*&)tempSocket );
		port.Format("%d",tempSocket->thePeerPort);
		msg.Format("+%s %s %s",tempSocket->host,tempSocket->thePeerIp,port);
		rmsg+=msg;
	}
	for(pos = mapSocket->GetStartPosition(); pos!= NULL; )
	{
		mapSocket->GetNextAssoc(pos,key,(CObject*&)tempSocket );
		ret=tempSocket->Send(CString("<?Command update client list?>")+rmsg,2048);
		while(ret==SOCKET_ERROR)
			ret=tempSocket->Send(CString("<?Command update client list?>")+rmsg,2048);
	}
}