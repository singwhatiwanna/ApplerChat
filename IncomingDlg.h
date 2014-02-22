#if !defined(AFX_INCOMINGDLG_H__1A69C695_49E1_4175_9726_9420AFB9DFE7__INCLUDED_)
#define AFX_INCOMINGDLG_H__1A69C695_49E1_4175_9726_9420AFB9DFE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IncomingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIncomingDlg dialog

class CIncomingDlg : public CDialog
{
// Construction
public:
	CIncomingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIncomingDlg)
	enum { IDD = IDD_INCOMING_CALL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIncomingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIncomingDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INCOMINGDLG_H__1A69C695_49E1_4175_9726_9420AFB9DFE7__INCLUDED_)
