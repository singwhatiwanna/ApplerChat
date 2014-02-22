#if !defined(AFX_CHATSOCKET_H__13E6012E_8AB4_4B05_B3F7_6EF0A73DA82C__INCLUDED_)
#define AFX_CHATSOCKET_H__13E6012E_8AB4_4B05_B3F7_6EF0A73DA82C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CChatSocket command target

class CChatSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CChatSocket();
	virtual ~CChatSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatSocket)
	//}}AFX_VIRTUAL
	void OnReceive(int nErrorCode);
	void OnClose(int nErrorCode);
	// Generated message map functions
	//{{AFX_MSG(CChatSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSOCKET_H__13E6012E_8AB4_4B05_B3F7_6EF0A73DA82C__INCLUDED_)
