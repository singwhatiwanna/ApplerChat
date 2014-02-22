// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "CSocketDemo.h"
#include "ListenSocket.h"
#include "CServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCSocketDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CListenSocket
CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CListenSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CListenSocket member functions

void CListenSocket::OnAccept(int nErrorCode)
{
	CString peerIp;
	UINT peerPort;
	CString key;
	CServerSocket *rConnectedSocket=new CServerSocket();
	
	int ret=Accept(*rConnectedSocket,NULL,NULL);
	CMapStringToOb *mapSocket=&(((CCSocketDemoApp*)AfxGetApp())->mapSocket);
	if (ret)
	{
		rConnectedSocket->GetPeerName(peerIp,peerPort);
		rConnectedSocket->thePeerIp=peerIp;
		rConnectedSocket->thePeerPort=peerPort;
		key.Format("%s%d",peerIp,peerPort);
		mapSocket->SetAt(key,rConnectedSocket);
	}
	else
		AfxMessageBox("接受客户端连接失败！",MB_ICONERROR);
	HOSTENT* pHost;
	DWORD ip=inet_addr(peerIp.GetBuffer(0));  
	pHost=gethostbyaddr((LPSTR)&ip,4,AF_INET); 
	CString csPort;
	csPort.Format("%d",peerPort);
	rConnectedSocket->host=pHost->h_name;
	
	rConnectedSocket->AsyncSelect(FD_READ|FD_CLOSE);
// 	rConnectedSocket->NotifyAll(pHost->h_name,peerIp,csPort,TRUE);//special notify all.
// 	rConnectedSocket->NotifyPeer();

	CListCtrl *lc=(CListCtrl*)pcwnd->GetDlgItem(IDC_LIST_CLIENT);
	int itemNumber=lc->GetItemCount();
	lc->InsertItem(itemNumber,key);
	lc->SetItemText(itemNumber,0,pHost->h_name);
	lc->SetItemText(itemNumber,1,peerIp);
	lc->SetItemText(itemNumber,2,csPort);

	NotifyAllClients();//上线通知

	Sleep(500);
	rConnectedSocket->Send(CString("<?PlainMsg?>:")+"欢迎",64);

	CAsyncSocket::OnAccept(nErrorCode);
}

void CListenSocket::NotifyAllClients()
{
	Sleep(1000);
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
		msg.Format("+%s %s %s",tempSocket->host,tempSocket->thePeerIp,port);
		rmsg+=msg;
	}
	for(pos = mapSocket->GetStartPosition(); pos!= NULL; )
	{
		mapSocket->GetNextAssoc(pos,key,(CObject*&)tempSocket );
		ret=tempSocket->Send(CString("<?Command update client list?>")+rmsg,256);
		while(ret==SOCKET_ERROR)
			ret=tempSocket->Send(CString("<?Command update client list?>")+rmsg,256);
	}
}