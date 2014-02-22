#if !defined(AFX_CLIENTASYNCSOCKET_H__3788A6FE_29DB_4EBA_AEA8_973E2A0CB4AE__INCLUDED_)
#define AFX_CLIENTASYNCSOCKET_H__3788A6FE_29DB_4EBA_AEA8_973E2A0CB4AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientAsyncSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientAsyncSocket command target

class CClientSocket : public CAsyncSocket
{
// Attributes
public:
	int socketType;
	CWnd *pcwnd;
	CWnd *fileTran;
	CString host;
	CString localIp;
	CString localPort;
	CString thePeerIp;
	UINT thePeerPort;
	CString filePath;
	CString fileName;
	CFile destFile;
	DWORD fileLength;
	CString fileLen;
	int tag;
	int closed;
// Operations
public:
	CClientSocket();
	virtual ~CClientSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientAsyncSocket)
	//}}AFX_VIRTUAL
	void OnReceive(int nErrorCode);
	void OnAccept(int nErrorCode);
	void OnClose(int nErrorCode);
	void OnConnect(int nErrorCode);
	void OnSend(int nErrorCode);
	void UpdateClientList(CString msg,BOOL isAdd);
	// Generated message map functions
	//{{AFX_MSG(CClientAsyncSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTASYNCSOCKET_H__3788A6FE_29DB_4EBA_AEA8_973E2A0CB4AE__INCLUDED_)
