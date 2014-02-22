#if !defined(AFX_SENDFILEDLG_H__987721B3_21D3_4C9A_8EB6_E10A8C07E731__INCLUDED_)
#define AFX_SENDFILEDLG_H__987721B3_21D3_4C9A_8EB6_E10A8C07E731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendFileDlg dialog

class CSendFileDlg : public CDialog
{
// Construction
public:
	CSendFileDlg(int _socketType,CAsyncSocket *attachedSocket,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendFileDlg)
	enum { IDD = IDD_SENDFILE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	int socketType;
	CAsyncSocket *attachedSocket;
	// Generated message map functions
	//{{AFX_MSG(CSendFileDlg)
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDFILEDLG_H__987721B3_21D3_4C9A_8EB6_E10A8C07E731__INCLUDED_)
