#if !defined(AFX_LISTENSOCKET_H__216639FF_99A2_4648_8233_A46891B9C5C7__INCLUDED_)
#define AFX_LISTENSOCKET_H__216639FF_99A2_4648_8233_A46891B9C5C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

class CListenSocket : public CAsyncSocket
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
	CListenSocket();
	virtual ~CListenSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	//}}AFX_VIRTUAL
	void OnAccept(int nErrorCode);
	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	void NotifyAllClients();
// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__216639FF_99A2_4648_8233_A46891B9C5C7__INCLUDED_)
