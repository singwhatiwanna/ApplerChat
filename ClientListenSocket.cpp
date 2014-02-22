// ClientListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "CSocketDemo.h"
#include "ClientListenSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientListenSocket

CClientListenSocket::CClientListenSocket()
{
}

CClientListenSocket::~CClientListenSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientListenSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientListenSocket member functions
void CClientListenSocket::OnAccept(int nErrorCode)
{
	CString peerIp;
	UINT peerPort;
	CString key;
	CClientSvrSocket *rConnectedSocket=new CClientSvrSocket();
	
	int ret=Accept(*rConnectedSocket,NULL,NULL);
	//CMapStringToOb *clientMapSocket=&(((CCSocketDemoApp*)AfxGetApp())->clientMapSocket);
	if (ret)
	{
		rConnectedSocket->GetSockName(rConnectedSocket->localIp,peerPort);
		rConnectedSocket->GetPeerName(peerIp,peerPort);
		rConnectedSocket->thePeerIp=peerIp;
		rConnectedSocket->thePeerPort=peerPort;
		rConnectedSocket->pcwnd=AfxGetMainWnd();
	}
	HOSTENT* pHost;
	DWORD ip=inet_addr(peerIp.GetBuffer(0));  
	pHost=gethostbyaddr((LPSTR)&ip,4,AF_INET); 
	rConnectedSocket->host=pHost->h_name;
	
	rConnectedSocket->AsyncSelect(FD_READ|FD_CLOSE);
	//rConnectedSocket->Send(CString("<?PlainMsg?>:")+"[tcp server] welcome",64);
		
	CAsyncSocket::OnAccept(nErrorCode);
}
