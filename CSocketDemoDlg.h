// CSocketDemoDlg.h : header file
//

#if !defined(AFX_CSOCKETDEMODLG_H__B74D7CAF_95E5_428C_8B3C_2A84A45A4D79__INCLUDED_)
#define AFX_CSOCKETDEMODLG_H__B74D7CAF_95E5_428C_8B3C_2A84A45A4D79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CServerSocket.h"
#include "lxDialog.h"
#include "SMButton.h"
#include "ClientSocket.h"
#include "ListenSocket.h"
#include "RTCEvents.h"
#include "AVDlg.h"


#define WM_NOTIFYICON (WM_USER+1)
/////////////////////////////////////////////////////////////////////////////
// CCSocketDemoDlg dialog


class CCSocketDemoDlg : public ClxDialog
{
// Construction
public:
	CCSocketDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCSocketDemoDlg)
	enum { IDD = IDD_CSOCKETDEMO_DIALOG };
	CSMButton m_btnSend;
	CSMButton m_btnMinmize;
	CSMButton m_btnMaxmize;
	CSMButton m_btnEstab;
	CSMButton m_btnConnect;
	CSMButton m_btnClose;
	CSMButton m_btnAbout;
	NOTIFYICONDATA nd;
	int flashicon;
	int flashWindowCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSocketDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	public:
		CListenSocket m_listenSocket;				//server socket
		CClientSocket m_clientSocket;			//client socket
		CServerSocket* temp_socket;					//server send file
		CChatSocket m_chatSocket;
		CClientListenSocket m_clientListenSocket;
		CClientSvrSocket m_clientSvrSocket;
		CImageList imageList;
		CString fileName;
		CString filePath;
		int isMax;//指示窗体是否是最大化状态
		BOOL InitAsyncSocket();
		BOOL InitClientAsyncSocket();
		void TransferFileBetweenClient();
// Implementation
protected:
	HICON m_hIcon;
	HICON m_redApple;
	// Generated message map functions
	//{{AFX_MSG(CCSocketDemoDlg)
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSend(int type=SENDTEXTMSG,int responseTo=RESPONSETOSERVER);
	afx_msg void OnButtonEstab();
	afx_msg void OnButtonConnect();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonClose();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnButtonAbout();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnButtonMaxmize();
	afx_msg void OnButtonMinimize();
	afx_msg void OnUserSendfile();
	afx_msg void OnUserVideochat();
	afx_msg void OnClose();
	afx_msg void OnNotifyIcon(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPopupSgChat();
	afx_msg void OnPopupShow();
	afx_msg void OnPopupTray();
	afx_msg void OnPopupExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnServerKick();
	LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HRESULT OnRTCMessagingEvent (IRTCMessagingEvent *pEvent);
	CAVDlg m_AVDlg;
	HRESULT AddSession(IRTCSession *pSession, RTC_SESSION_TYPE enType);
	IRTCParticipant * m_Participant;
	HRESULT MakeCall(RTC_SESSION_TYPE enType, BSTR bstrURI);
	void OnRTCClientEvent(IRTCClientEvent *pEvent);
	void OnRTCIntensityEvent(IRTCIntensityEvent *pEvent);
	void OnRTCMediaEvent(IRTCMediaEvent *pEvent);
	void OnRTCSessionStateChangeEvent(IRTCSessionStateChangeEvent *pEvent);
	HRESULT OnRTCEvent (UINT message, WPARAM wParam, LPARAM lParam);
	CRTCEvents * m_pEvents;
	IRTCClient * m_pClient;
	HRESULT InitRTCClient();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSOCKETDEMODLG_H__B74D7CAF_95E5_428C_8B3C_2A84A45A4D79__INCLUDED_)
