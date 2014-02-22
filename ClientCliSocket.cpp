// ClientCliSocket.cpp : implementation file
//

#include "stdafx.h"
#include "CSocketDemo.h"
#include "ClientCliSocket.h"
#include "SendFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientCliSocket

CClientCliSocket::CClientCliSocket()
{
	pcwnd=AfxGetApp()->GetMainWnd();tag=1;goon=1;
	CString localHost;
	gethostname(localHost.GetBuffer(128),128);//get local ipaddress and hostname
	localHost.ReleaseBuffer();
	struct hostent* pHost;
	pHost=gethostbyname(localHost);
	localIp=inet_ntoa(*(struct in_addr*)pHost->h_addr_list[0]);
	fileTran=NULL;
}

CClientCliSocket::~CClientCliSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientCliSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientCliSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientCliSocket member functions
void CClientCliSocket::OnReceive(int nErrorCode)
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

	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientCliSocket::OnClose(int nErrorCode)
{
	Close();

	CAsyncSocket::OnClose(nErrorCode);
}

void CClientCliSocket::OnConnect(int nErrorCode)
{
	UINT port;
	CString csPeerPort;
	if (nErrorCode==0)
	{
		pcwnd=AfxGetApp()->GetMainWnd();
		GetSockName(localIp,port);
		GetPeerName(thePeerIp,thePeerPort);
		Send(CString("<?Request FILETRANSFER?>:"+fileName+":"+fileLen),512);
		pcwnd->GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	}
	else
	{
		AfxMessageBox("连接服务器失败");
		Close();
	}
}

void CClientCliSocket::TransferFile(CString path)
{
	char *buf=new char[128];
	byte *contents=new byte[PACKAGESIZE];
	memset(contents,0,PACKAGESIZE);
	int total=-1;
// 	srcFile.Open(path,CFile::modeRead|CFile::typeBinary,NULL);
// 	remainder=srcFile.GetLength();

// 	CFile file;
// 	file.Open(path,CFile::modeRead|CFile::typeBinary,NULL);
	
	DWORD len=file.GetLength();
	DWORD block=0;
// 	DWORD remainder=len;
	
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
	//if (file.GetPosition()>=len)
// 	if (remainder<=0)
// 	{
// 		Send("<?FileStop?>",256);
// 		goon=0;
// 		file.Close();
// 		AfxMessageBox("发送完毕.");
// 	}
}

void CClientCliSocket::OnSend(int nErrorCode)
{
	CAsyncSocket::OnSend(nErrorCode);
}