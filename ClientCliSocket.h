#if !defined(AFX_CLIENTCLISOCKET_H__B7497DDD_0B69_43DE_8E77_5115F6F8BCDD__INCLUDED_)
#define AFX_CLIENTCLISOCKET_H__B7497DDD_0B69_43DE_8E77_5115F6F8BCDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientCliSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientCliSocket command target

class CClientCliSocket : public CAsyncSocket
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
	CString fileLen;
	CFile srcFile;
	CFile file;
	int tag;
	int goon;
	// 	byte *contents;
	DWORD remainder;
// Operations
public:
	CClientCliSocket();
	virtual ~CClientCliSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientCliSocket)
	//}}AFX_VIRTUAL
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
	void OnConnect(int nErrorCode);
	void TransferFile(CString path);
	void OnSend(int nErrorCode);
	// Generated message map functions
	//{{AFX_MSG(CClientCliSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTCLISOCKET_H__B7497DDD_0B69_43DE_8E77_5115F6F8BCDD__INCLUDED_)
