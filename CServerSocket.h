#if !defined(AFX_MYASYNCSOCKET_H__F84F74F0_87E0_401D_BE67_6B3CF8A3149E__INCLUDED_)
#define AFX_MYASYNCSOCKET_H__F84F74F0_87E0_401D_BE67_6B3CF8A3149E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CServerSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CServerSocket command target

class CServerSocket : public CAsyncSocket
{
// Attributes
public:
	int socketType;
	CWnd *pcwnd;
	CWnd *fileTran;
	CString host;
	CString localIp;
	CString thePeerIp;
	UINT thePeerPort;
	CString filePath;
	CString fileName;
	CFile srcFile;
	CFile file;
	int tag;
	int goon;
// 	byte *contents;
	DWORD remainder;
	int already;
// Operations
public:
	CServerSocket();
	virtual ~CServerSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSocket)
	//}}AFX_VIRTUAL
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
	void OnConnect(int nErrorCode);
	void UpdateClientList();
	void TransferFile(CString path);
	void OnSend(int nErrorCode);
	void NotifyPeer();
	void NotifyAll(CString host,CString ip,CString port,BOOL enter=TRUE);
	void NotifyAllMembers();
	// Generated message map functions
	//{{AFX_MSG(CServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYASYNCSOCKET_H__F84F74F0_87E0_401D_BE67_6B3CF8A3149E__INCLUDED_)
