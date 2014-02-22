#if !defined(AFX_CLIENTLISTENSOCKET_H__D1CE9789_96FD_4B08_8A7B_DF3EDB54E96D__INCLUDED_)
#define AFX_CLIENTLISTENSOCKET_H__D1CE9789_96FD_4B08_8A7B_DF3EDB54E96D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientListenSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientListenSocket command target

class CClientListenSocket : public CAsyncSocket
{
// Attributes
public:
	int socketType;
	CWnd *pcwnd;
	CString host;
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
// Operations
public:
	CClientListenSocket();
	virtual ~CClientListenSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientListenSocket)
	//}}AFX_VIRTUAL
	void OnAccept(int nErrorCode);
	// Generated message map functions
	//{{AFX_MSG(CClientListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTLISTENSOCKET_H__D1CE9789_96FD_4B08_8A7B_DF3EDB54E96D__INCLUDED_)
