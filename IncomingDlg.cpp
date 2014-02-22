

#include "stdafx.h"
#include "CSocketDemo.h"
#include "defines.h"

#include "IncomingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIncomingDlg dialog


CIncomingDlg::CIncomingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIncomingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIncomingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CIncomingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIncomingDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIncomingDlg, CDialog)
	//{{AFX_MSG_MAP(CIncomingDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIncomingDlg message handlers

BOOL CIncomingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SESSION_DATA	*pData;

	pData = (SESSION_DATA *)GetWindowLong (::GetWindow(m_hWnd, GW_OWNER), GWL_USERDATA);

	// Display the caller name and ID.
	SetDlgItemTextW (m_hWnd, IDC_CALLERNAME, pData->bstrName);
	SetDlgItemTextW (m_hWnd, IDC_CALLERID, pData->bstrURI);
	CString str;
	GetDlgItemText(IDC_CALLERID,str);
	str=str.Right(str.GetLength()-4);
	SetDlgItemText(IDC_CALLERID,str.GetBuffer(0));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
