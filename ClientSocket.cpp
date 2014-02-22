// ClientAsyncSocket.cpp : implementation file
//

#include "stdafx.h"
#include "CSocketDemo.h"
#include "ClientSocket.h"
#include "CServerSocket.h"
#include "SendFileDlg.h"
#include "CSocketDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSocket

CClientSocket::CClientSocket()
{
	tag=0;
	closed=0;
	fileTran=NULL;
}

CClientSocket::~CClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSocket member functions
void CClientSocket::OnReceive(int nErrorCode)
{
	CString ip;UINT port;
	CString buf,text;
	CString _fileName;
	byte* mybuf=new byte[PACKAGESIZE];
	//Receive(buf.GetBuffer(2056),2056);
	int total=Receive(mybuf,PACKAGESIZE);
	buf.Format("%s",mybuf);
	GetPeerName(ip,port);
	int isTxtMsg=0;

	if (buf.Find("<?Request FILETRANSFER?>")>-1)
	{
		closed=0;
		int pos=buf.Find(":");
		int posEnd=buf.Find(":",pos+1);
		//_fileName=buf.Right(buf.GetLength()-pos-1);
		_fileName=buf.Mid(pos+1,posEnd-pos-1);
		fileLen=buf.Mid(posEnd+1,buf.GetLength()-posEnd-1);
		fileLength=atol(fileLen.GetBuffer(0));
		fileName=_fileName;
		CString request;
		request.Format("来自%s的用户向你发送文件%s，是否接收？",ip,_fileName);
		int ret=MessageBox(pcwnd->GetSafeHwnd(),request,"文件发送请求",MB_ICONQUESTION|MB_YESNO);
		if (ret==IDYES)
		{
			CString suffix=fileName.Right(fileName.GetLength()-fileName.ReverseFind('.')-1);
			CFileDialog dlg(FALSE,suffix,fileName);
			dlg.m_ofn.lpstrTitle="请选择保存位置";
			dlg.m_ofn.lpstrFilter="所有文件类型(*.*)\0*.*\0\0";
			if (IDOK==dlg.DoModal())
			{
				filePath=dlg.GetPathName();
				fileName=dlg.GetFileName();
				destFile.Open(filePath,CFile::modeWrite|CFile::modeNoTruncate|CFile::modeCreate|CFile::typeBinary,NULL);
				if (!fileTran)
				{
					CSendFileDlg *sfDlg=new CSendFileDlg(SOCKETTYPECLIENT,this);
					sfDlg->Create(IDD_SENDFILE_DIALOG,CWnd::FromHandle(::GetDesktopWindow()));
					fileTran=sfDlg;
					fileTran->ShowWindow(SW_SHOW);
 				}
				fileTran->SetDlgItemText(IDC_STATIC_SRCA,thePeerIp);
				fileTran->SetDlgItemText(IDC_STATIC_DESA,localIp);
				fileTran->SetDlgItemText(IDC_STATIC_FINFO,fileName+"\n大小: "+fileLen+" 字节");
				CProgressCtrl *proSF=(CProgressCtrl*)fileTran->GetDlgItem(IDC_PROGRESS_TRANFILE);
				proSF->SetRange32(0,fileLength);
				proSF->SetPos(0);
				Send("<?Response FILETRANSFER?>:ACCEPT",256);
			}
			else
				Send("<?Response FILETRANSFER?>:REFUSE",256);
		}
		else
		{
			Send("<?Response FILETRANSFER?>:REFUSE",256);
		}
	}
	else if (buf.Find("<?PlainMsg?>")>-1)
	{
		tag=1;isTxtMsg=1;
	}
	else if (buf.Find("<?FileStop?>")>-1)
	{
		if (closed==0)
		{
			destFile.Flush();
			destFile.Close();
			closed=1;
		}
	}
	else if (buf.Find("<?Command update client list?>")>-1)
	{
		int tag=1;
		int pos1,pos2;
		BOOL isAdd=FALSE;
		if (buf.Find("<?Command update client list?>+")>-1)
			isAdd=TRUE;
		if (isAdd)//redraw the client list
		{
			CListCtrl *lc=(CListCtrl*)AfxGetMainWnd()->GetDlgItem(IDC_LIST_CLIENT);
			lc->DeleteAllItems();
		}

		buf.Replace('#','+');
		CString sztemp;
		while(tag)
		{
			pos1=buf.Find("+");
			pos2=buf.Find("+",pos1+1);
			if (pos1==-1)
				break;
			if(pos2==-1)
			{
				pos2=buf.GetLength();
				tag=0;
			}
			sztemp=buf.Mid(pos1+1,pos2-pos1-1);
			buf=buf.Right(buf.GetLength()-pos2);
			UpdateClientList(CString("<?Command update client list?>")+sztemp,isAdd);
		}
	}
	else if (buf.Find("<?Command Kick?>")>-1)
	{
		AfxMessageBox("你已被服务器踢出，\n点击 确定 结束程序。",MB_ICONINFORMATION);
		CCSocketDemoDlg *ccd=(CCSocketDemoDlg*)AfxGetMainWnd();
		NOTIFYICONDATA *_nd=&(ccd->nd);
		Shell_NotifyIcon(NIM_DELETE, _nd);
		::PostQuitMessage(0);
	}
	else
	{
		destFile.SeekToEnd();
		destFile.Write(mybuf,total);
		//destFile.Flush();
		CProgressCtrl *proSF=(CProgressCtrl*)fileTran->GetDlgItem(IDC_PROGRESS_TRANFILE);
		proSF->SetPos(proSF->GetPos()+total);
		CString status;
		status.Format("已接收%u 字节中的%d 字节",fileLength,proSF->GetPos());
		fileTran->SetDlgItemText(IDC_STATIC_STATUS,status);
		if (fileLength==proSF->GetPos() &&closed==0)
		{
			destFile.Flush();
			destFile.Close();
			closed=1;
		}
		Send("<?FileContinue?>",256);
	}


	if (isTxtMsg==0)
	{
		delete[] mybuf;
		buf.Empty();
		return;
	}
	if (AfxGetMainWnd()->IsWindowVisible()==FALSE)
		AfxGetMainWnd()->SetTimer(2,800,NULL);//flash icon
	else
		AfxGetMainWnd()->SetTimer(1,800,NULL);//flash window
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_MSG),AfxGetInstanceHandle(),SND_RESOURCE|SND_ASYNC|SND_NOWAIT);

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

	buf=buf.Right(buf.GetLength()-13);

	CTime time=CTime::GetCurrentTime();
	CString currentTime;
	currentTime.Format("          %02d:%02d:%02d",time.GetHour(),time.GetMinute(),time.GetSecond());

	host.Format("[系统消息] %s%s",pHost->h_name,currentTime);
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

void CClientSocket::OnAccept(int nErrorCode)
{
	CAsyncSocket::OnAccept(nErrorCode);
}

void CClientSocket::OnConnect(int nErrorCode)
{
	UINT port;
	CString csPeerPort;
	pcwnd=AfxGetApp()->GetMainWnd();
	if (nErrorCode==0)
	{
		GetSockName(localIp,port);
		GetPeerName(thePeerIp,thePeerPort);
		csPeerPort.Format("%d",thePeerPort);
		localPort.Format("%u",port);
		CString msg;
		msg.Format("<?PlainMsg?>:%s comes in",localIp);
		Send(msg.GetBuffer(0),msg.GetLength()+1);
		pcwnd->GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
		pcwnd->SetDlgItemText(IDC_BUTTON_CONNECT,"连接已建立");

		/*CListCtrl *lc=(CListCtrl*)pcwnd->GetDlgItem(IDC_LIST_CLIENT);
		int itemNumber=lc->GetItemCount();
		
		lc->InsertItem(itemNumber,NULL);
		lc->SetItemText(itemNumber,0,"TCP服务器");
		lc->SetItemText(itemNumber,1,thePeerIp);
		lc->SetItemText(itemNumber,2,csPeerPort);*/
	}
	else
	{
		AfxMessageBox("连接服务器失败",MB_ICONWARNING);
		Close();

		CCSocketDemoDlg* acd=(CCSocketDemoDlg*)pcwnd;
		acd->m_clientListenSocket.Close();
		acd->m_chatSocket.Close();

		pcwnd->GetDlgItem(IDC_IPADDRESS1)->EnableWindow(TRUE);
		pcwnd->GetDlgItem(IDC_BUTTON_ESTAB)->EnableWindow(TRUE);
		pcwnd->GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
		pcwnd->SetDlgItemText(IDC_BUTTON_CONNECT,"连接服务器");
	}

	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
	Close();

	CAsyncSocket::OnClose(nErrorCode);
}

void CClientSocket::OnSend(int nErrorCode)
{
	CAsyncSocket::OnSend(nErrorCode);
}

void CClientSocket::UpdateClientList(CString msg,BOOL isAdd)
{
	int itemNumber,columnNumber;
	CString host,ip,port,temp;
	CListCtrl *lc=(CListCtrl*)pcwnd->GetDlgItem(IDC_LIST_CLIENT);
	int pos1=strlen("<?Command update client list?>");
	int pos2=msg.Find(" ",pos1);
	host=msg.Mid(pos1,pos2-pos1);
	temp=msg.Right(msg.GetLength()-pos2-1);
	pos2=temp.Find(" ");
	ip=temp.Mid(0,pos2);
	port=temp.Right(temp.GetLength()-pos2-1);
	//if (msg.Find("<?Command update client list?>+")>-1)
	if(isAdd)
	{
		itemNumber=lc->GetItemCount();
		if((ip+port)==(localIp+localPort))
		{
			itemNumber=0;
			lc->InsertItem(itemNumber,ip+port,1);
		}
		else
			lc->InsertItem(itemNumber,ip+port,0);
		lc->SetItemText(itemNumber,0,host);
		lc->SetItemText(itemNumber,1,ip);
		lc->SetItemText(itemNumber,2,port);
	}
	else
	{
		itemNumber=lc->GetItemCount();
		columnNumber=3;
		CString tip,tport;
		for (int i=0;i<itemNumber;i++)
		{
			tip=lc->GetItemText(i,1);
			tport=lc->GetItemText(i,2);
			if (tip==ip && tport==port)
			{
				int ret=lc->DeleteItem(i);
				ASSERT(ret);
				break;
			}
		}
	}
}
