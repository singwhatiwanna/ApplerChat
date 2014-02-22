

#include "stdafx.h"
#include "rtccore.h"
#include "CSocketDemo.h"
#include "AVDlg.h"
#include "defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAVDlg dialog


CAVDlg::CAVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAVDlg::IDD, pParent)
{
	m_pParentClient = NULL;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//{{AFX_DATA_INIT(CAVDlg)
	//}}AFX_DATA_INIT
}
								   

void CAVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAVDlg)
	DDX_Control(pDX, IDC_SPEAKERMUTE, m_cSpeakerMute);
	DDX_Control(pDX, IDC_SPEAKER_BAR, m_cSpeakerLevel);
	DDX_Control(pDX, IDC_MIC_BAR, m_cMicLevel);
	DDX_Control(pDX, IDC_SPEAKER_SLIDER, m_cSpeakerSlider);
	DDX_Control(pDX, IDC_MICMUTE, m_cMicMute);
	DDX_Control(pDX, IDC_SPEAKER_TEXT, m_cSpeakerText);
	DDX_Control(pDX, IDC_MIC_TEXT, m_cMicText);
	DDX_Control(pDX, IDC_MIC_SLIDER, m_cMicSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAVDlg, CDialog)
	//{{AFX_MSG_MAP(CAVDlg)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SPEAKER_SLIDER, OnSpeakerSlider)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_MIC_SLIDER, OnMicSlider)
	ON_BN_CLICKED(IDC_SPEAKERMUTE, OnSpeakermute)
	ON_BN_CLICKED(IDC_MICMUTE, OnMicmute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CAVDlg::OnOK() 
{
	if (m_pSession)
	{
		HRESULT hr = m_pSession->Terminate(RTCTR_NORMAL);
	}

	CDialog::OnOK();
}


void CAVDlg::OnCancel ()
{
	if (m_pSession)
	{
		HRESULT hr = m_pSession->Terminate(RTCTR_NORMAL);
	}
	
	CDialog::OnCancel();
}


void CAVDlg::OnSpeakerSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	long lPos = m_cSpeakerSlider.GetPos ();
	DoVolume (RTCAD_SPEAKER, lPos);
	*pResult = 0;
}


void CAVDlg::OnMicSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	long lPos = m_cMicSlider.GetPos ();
	DoVolume (RTCAD_MICROPHONE, lPos);
	*pResult = 0;
}


void CAVDlg::OnMicmute() 
{
	if (m_cMicMute.IsDlgButtonChecked (IDC_MICMUTE) != 0)
		m_cMicSlider.EnableWindow (FALSE);
	else
		m_cMicSlider.EnableWindow (TRUE);
	
	DoMute (RTCAD_MICROPHONE);
}


void CAVDlg::OnSpeakermute() 
{
	if (IsDlgButtonChecked (IDC_SPEAKERMUTE) != 0)
		m_cSpeakerSlider.EnableWindow (FALSE);
	else
		m_cSpeakerSlider.EnableWindow (TRUE);
	
	DoMute (RTCAD_SPEAKER);
}


HRESULT CAVDlg::SetParentClient(IRTCClient *pClient)
{
	m_pParentClient = pClient;
	ShowAudio();
	return S_OK;
}


HRESULT CAVDlg::DoMute(RTC_AUDIO_DEVICE enDevice)
{
    IRTCClient * pClient = NULL;
    BOOL fMute = FALSE;	  
    HWND hWnd = NULL;
    HRESULT hr;

	if (m_pParentClient == NULL)
		return -1;

	fMute = IsDlgButtonChecked ( (enDevice == RTCAD_SPEAKER) ? IDC_SPEAKERMUTE : IDC_MICMUTE);

    hr = m_pParentClient->put_AudioMuted(enDevice, fMute ? VARIANT_TRUE : VARIANT_FALSE);

    if (FAILED(hr))
    {
        return hr;
    }
    return S_OK;
}


HRESULT CAVDlg::DoVolume(RTC_AUDIO_DEVICE enDevice, long lVolume)
{
    HRESULT hr;

	if (m_pParentClient == NULL)
		return -1;

    hr = m_pParentClient->put_Volume(enDevice, lVolume);

    if (FAILED(hr))
    {
        return hr;
    }

	return S_OK;
}


HRESULT CAVDlg::ShowAudio()
{
    VARIANT_BOOL fMute = FALSE;
    long lVolume = 0;
    long lMediaCaps = 0;
    HRESULT hr;

    if (m_pParentClient == NULL)
		return -1;

    hr = m_pParentClient->get_MediaCapabilities(&lMediaCaps);

    if (FAILED(hr))
    {
        return hr;
    }

    if (lMediaCaps & RTCMT_AUDIO_RECEIVE)
    {
        hr = m_pParentClient->get_AudioMuted(RTCAD_SPEAKER, &fMute);

        if (FAILED(hr))
        {
            return hr;
        }

        m_cSpeakerMute.SetCheck ( fMute ? BST_CHECKED : BST_UNCHECKED);

        hr = m_pParentClient->get_Volume(RTCAD_SPEAKER, &lVolume);

        if (FAILED(hr))
        {
            return hr;
        }

		m_cSpeakerSlider.SetPos (lVolume);
    }

    if (lMediaCaps & RTCMT_AUDIO_SEND)
    {
  
        hr = m_pParentClient->get_AudioMuted(RTCAD_MICROPHONE, &fMute);

        if (FAILED(hr))
        {
            return hr;
        }

        m_cMicMute.SetCheck ( fMute ? BST_CHECKED : BST_UNCHECKED );
   
        hr = m_pParentClient->get_Volume(RTCAD_MICROPHONE, &lVolume);

        if (FAILED(hr))
        {
            return hr;
        }

		m_cSpeakerSlider.SetPos (lVolume);
    }
    return S_OK;
}


HRESULT CAVDlg::ShowVideo(RTC_VIDEO_DEVICE enDevice, BOOL fShow)
{
    IVideoWindow * pVid = NULL;
    long lMediaCaps = 0;
    HWND hWnd = NULL;
    HRESULT hr;

    if (m_pParentClient == NULL)
	{
		return -1;
	}

    hr = m_pParentClient->get_MediaCapabilities(&lMediaCaps);

    if (FAILED(hr))
    {
        return hr;
    }

	hr = m_pParentClient->get_IVideoWindow(enDevice, &pVid);

    if (FAILED(hr))
    {
        return hr;
    }

	if (enDevice == RTCVD_PREVIEW)
    {          
        fShow = fShow && (lMediaCaps & RTCMT_VIDEO_SEND);
        m_fShowPrev = fShow;
        hWnd = m_hPrevVideoParent;

        ::ShowWindow(m_hPrevVideoParent, fShow ? SW_SHOW : SW_HIDE);

        HRGN hRegion;

        if (fShow)
        {
            POINT rgPoints[6] =
                    { 0, 0,
                      0, m_lRecvHeight,
                      m_lRecvWidth - m_lPrevWidth, m_lRecvHeight,
                      m_lRecvWidth - m_lPrevWidth, m_lRecvHeight - m_lPrevHeight,
                      m_lRecvWidth, m_lRecvHeight - m_lPrevHeight,
                      m_lRecvWidth, 0
                    };

            hRegion = CreatePolygonRgn(rgPoints, 6, ALTERNATE);
        }
        else
        {
            hRegion = CreateRectRgn(0, 0, m_lRecvWidth, m_lRecvHeight);
        }

        ::SetWindowRgn(m_hRecvVideoParent, hRegion, TRUE);
    }
    else
    {
        fShow = fShow && (lMediaCaps & RTCMT_VIDEO_RECEIVE);
        m_fShowRecv = fShow;
        hWnd = m_hRecvVideoParent;

        ::ShowWindow(m_hRecvVideoParent, SW_SHOW);
    }

    if ( fShow == TRUE )
    {
        pVid->put_WindowStyle( WS_CHILD |
                               WS_CLIPCHILDREN |
                               WS_CLIPSIBLINGS );
        
        pVid->put_Owner( (OAHWND)hWnd );

        RECT rc;
        ::GetClientRect(hWnd, &rc );  
        
        pVid->SetWindowPosition(
            rc.left,
            rc.top,
            rc.right,
            rc.bottom
            );

        pVid->put_Visible(-1);        
    }       

    SAFE_RELEASE(pVid);    

    return S_OK;
}

HRESULT CAVDlg::DeliverMedia(long lMediaType, RTC_MEDIA_EVENT_TYPE enType, 
							 RTC_MEDIA_EVENT_REASON enReason)
{
    RTC_VIDEO_DEVICE enVideo;
    BOOL fShow;
    HRESULT hr = S_OK;

    
    switch (lMediaType)
    {
    case RTCMT_VIDEO_SEND:
        enVideo = RTCVD_PREVIEW;
        break;

    case RTCMT_VIDEO_RECEIVE:
        enVideo = RTCVD_RECEIVE;
        break;

    case RTCMT_T120_SENDRECV:
		break;

	default:
        return S_OK;
    }

    switch (enType) 
    {
    case RTCMET_STARTED:
        fShow = TRUE;
        break;

    case RTCMET_STOPPED:
		::ShowWindow(m_hRecvVideoParent, SW_HIDE);
		::SetParent(m_hRecvVideoParent, NULL);

		::ShowWindow(m_hPrevVideoParent, SW_HIDE);
		::SetParent(m_hPrevVideoParent, NULL);

		SetState (RTCSS_IDLE);

		SAFE_RELEASE(m_pSession);

		DestroyWindow();
		return S_OK;

    case RTCMET_FAILED:
        fShow = FALSE;
        break;

    default:
        return S_OK;
    }

    hr = ShowVideo(enVideo, fShow);

    return hr;

}


HRESULT CAVDlg::DeliverIntensity(RTC_AUDIO_DEVICE enDevice, long lLevel)
{
    switch(enDevice)
    {
    case RTCAD_SPEAKER:
		m_cSpeakerLevel.SetPos (lLevel);
        break;

    case RTCAD_MICROPHONE:
		m_cMicLevel.SetPos (lLevel);
        break;
    }

    return S_OK;
}


HRESULT CAVDlg::DeliverClient(RTC_CLIENT_EVENT_TYPE enEventType)
{
    switch(enEventType)
    {
    case RTCCET_VOLUME_CHANGE:
        
        ShowAudio();
        break;

    case RTCCET_DEVICE_CHANGE:
      
        ShowAudio();
        ShowVideo(RTCVD_PREVIEW, m_fShowPrev);
        ShowVideo(RTCVD_RECEIVE, m_fShowRecv);
        break;
    }

    return S_OK;
}


BOOL CAVDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon,TRUE);
	SetIcon(m_hIcon,FALSE);

	int OFFSETX = 10;
	int OFFSETY = 50;

    RECT rcWnd;
    const int SIZE_EDGE = 5;
    const int TEXT_HEIGHT = 16;
    const int LEVEL_HEIGHT = 10;
    const int VOL_HEIGHT = 20;   

    ::GetClientRect(m_hWnd, &rcWnd);    
	
	m_pParentClient = NULL;
    
    float fAspectRatio = (float)QCIF_CY_SIZE/(float)QCIF_CX_SIZE;
    m_lRecvWidth = rcWnd.right - rcWnd.left - 2*SIZE_EDGE;
    m_lRecvHeight = (long)(fAspectRatio * (float)m_lRecvWidth);
	
    m_lPrevWidth = QQCIF_CX_SIZE;
    m_lPrevHeight = QQCIF_CY_SIZE;

    RECT rcRecvVid;

    rcRecvVid.left = rcWnd.left + SIZE_EDGE; 
    rcRecvVid.right = rcWnd.left + m_lRecvWidth + SIZE_EDGE;
    rcRecvVid.top = rcWnd.top + SIZE_EDGE;
    rcRecvVid.bottom = rcWnd.top + m_lRecvHeight + SIZE_EDGE;
    
    RECT rcPrevVid;

    rcPrevVid.left = rcRecvVid.right - m_lPrevWidth; 
    rcPrevVid.right = rcRecvVid.right;
    rcPrevVid.top = rcRecvVid.bottom - m_lPrevHeight;
    rcPrevVid.bottom = rcRecvVid.bottom;         

	m_hRecvVideoParent = NULL;
	m_hPrevVideoParent = NULL;

	m_cSpeakerSlider.SetRangeMax (0xffff);
	m_cMicSlider.SetRangeMax (0xffff);

    if (m_hRecvVideoParent == NULL)
    {
        m_hRecvVideoParent = CreateWindowExW(
            WS_EX_CLIENTEDGE,
            L"STATIC",
            NULL,
            WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
			rcRecvVid.left, rcRecvVid.top,
			m_lRecvWidth, m_lRecvHeight,
            m_hWnd,
            NULL,
            GetModuleHandle(NULL),
            NULL);
    
        if ( !m_hRecvVideoParent )
        {
            return -1;
        }
    }
    else
    {
        if (!::SetParent(m_hRecvVideoParent, m_hWnd))
        {
            // SetParent failed
            return -1;
        }
    }

	if (m_hPrevVideoParent == NULL)
    {
        m_hPrevVideoParent = CreateWindowExW(
            WS_EX_CLIENTEDGE,
            L"STATIC",
            NULL,
            WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
			rcPrevVid.left, rcPrevVid.top,
			m_lPrevWidth, m_lPrevHeight,
            m_hWnd,
            NULL,
            GetModuleHandle(NULL),
            NULL);
    
        if ( !m_hPrevVideoParent )
        {
            return -1;
        }
    }
    else
    {
        if (!::SetParent(m_hPrevVideoParent, m_hWnd))
        {
            return -1;
        }
    }

	return TRUE;  
}


void CAVDlg::SetSession(IRTCSession *pSession)
{
	m_pSession = pSession;
}


void CAVDlg::SetState(RTC_SESSION_STATE enState)
{
	m_rtcState = enState;
}


RTC_SESSION_STATE CAVDlg::GetState()
{
	return m_rtcState;
}
