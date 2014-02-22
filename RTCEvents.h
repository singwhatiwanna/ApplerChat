// RTCEvents.h: interface for the CRTCEvents class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTCEVENTS_H__1B406531_61BA_444E_9FF1_AC02153DC39B__INCLUDED_)
#define AFX_RTCEVENTS_H__1B406531_61BA_444E_9FF1_AC02153DC39B__INCLUDED_

#include "rtccore.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRTCEvents : public IRTCEventNotification  
{
public:
	HRESULT STDMETHODCALLTYPE Event(RTC_EVENT enEvent, IDispatch *pDisp);
	HRESULT Unadvise(IRTCClient *pClient);
	HRESULT Advise(IRTCClient *pClient, HWND hWnd);
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **ppvObject);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	CRTCEvents();
	virtual ~CRTCEvents();

private:
	HWND m_hWnd;
	DWORD m_dwCookie;
	DWORD m_dwRefCount;
};

#endif // !defined(AFX_RTCEVENTS_H__1B406531_61BA_444E_9FF1_AC02153DC39B__INCLUDED_)
