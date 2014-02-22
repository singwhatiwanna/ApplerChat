#if !defined(AFX_CLIENTSVRSOCKET_H__505A6707_4438_41CE_82D0_EF32CEC729B5__INCLUDED_)
#define AFX_CLIENTSVRSOCKET_H__505A6707_4438_41CE_82D0_EF32CEC729B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSvrSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSvrSocket command target

class CClientSvrSocket : public CAsyncSocket
{
// Attributes
public:
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
	CFile destFile;
	DWORD fileLength;
	CString fileLen;
	int tag;
	int closed;
// Operations
public:
	CClientSvrSocket();
	virtual ~CClientSvrSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSvrSocket)
	//}}AFX_VIRTUAL
	void OnReceive(int nErrorCode);
	void OnAccept(int nErrorCode);
	void OnClose(int nErrorCode);
	// Generated message map functions
	//{{AFX_MSG(CClientSvrSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSVRSOCKET_H__505A6707_4438_41CE_82D0_EF32CEC729B5__INCLUDED_)
