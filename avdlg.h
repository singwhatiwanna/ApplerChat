#if !defined(AFX_AVDlg_H__D9E061D3_D2CA_4192_907B_00407DCDDA41__INCLUDED_)
#define AFX_AVDlg_H__D9E061D3_D2CA_4192_907B_00407DCDDA41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AVDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAVDlg dialog

class CAVDlg : public CDialog
{
// Construction
public:
	HICON m_hIcon;
	RTC_SESSION_STATE GetState();
	void SetState (RTC_SESSION_STATE enState);
	void SetSession (IRTCSession *pSession);
	HRESULT SetParentClient(IRTCClient *pClient);

	HRESULT DeliverClient(RTC_CLIENT_EVENT_TYPE enEventType);
	HRESULT DeliverIntensity(RTC_AUDIO_DEVICE enDevice, long lLevel);
	HRESULT DeliverMedia(long lMediaType, RTC_MEDIA_EVENT_TYPE enType, RTC_MEDIA_EVENT_REASON enReason);

	CAVDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAVDlg)
	enum { IDD = IDD_AVDLG };
	CButton	m_cSpeakerMute;
	CProgressCtrl	m_cSpeakerLevel;
	CProgressCtrl	m_cMicLevel;
	CSliderCtrl	m_cSpeakerSlider;
	CButton	m_cMicMute;
	CStatic	m_cSpeakerText;
	CStatic	m_cMicText;
	CSliderCtrl	m_cMicSlider;
	//}}AFX_DATA


private:
	RTC_SESSION_STATE m_rtcState;
	IRTCSession * m_pSession;
	RECT m_RecvWinRect;
	RECT m_PrevWinRect;
    HWND m_hRecvVideoParent;
    HWND m_hPrevVideoParent;

    BOOL m_fShowRecv;
    BOOL m_fShowPrev;
    long m_lRecvWidth;
    long m_lRecvHeight;
    long m_lPrevWidth;
    long m_lPrevHeight;

	IRTCClient * m_pParentClient;
	HRESULT ShowVideo(RTC_VIDEO_DEVICE enDevice, BOOL fShow);
	HRESULT ShowAudio();
	HRESULT DoVolume(RTC_AUDIO_DEVICE enDevice, long lVolume);
	HRESULT DoMute(RTC_AUDIO_DEVICE enDevice);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAVDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAVDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSpeakerSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMicSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpeakermute();
	afx_msg void OnMicmute();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAVDlg_H__D9E061D3_D2CA_4192_907B_00407DCDDA41__INCLUDED_)
