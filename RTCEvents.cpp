
#include "stdafx.h"
#include "CSocketDemo.h"
#include "RTCEvents.h"
#include "rtccore_i.c"
#include "rtccore.h"
#include "defines.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



CRTCEvents::CRTCEvents()
{
	m_dwRefCount = 0;
	m_dwCookie = 0;
	m_hWnd = NULL;
}

CRTCEvents::~CRTCEvents()
{

}

ULONG STDMETHODCALLTYPE CRTCEvents::AddRef()
{
    m_dwRefCount++;
    return m_dwRefCount;
}


ULONG STDMETHODCALLTYPE CRTCEvents::Release()
{
    m_dwRefCount--;

    if ( 0 == m_dwRefCount)
    {
        delete this;
    }

    return m_dwRefCount;
}


HRESULT STDMETHODCALLTYPE CRTCEvents::QueryInterface(REFIID iid, void **ppvObject)
{
    if (iid == IID_IRTCEventNotification)
    {
        *ppvObject = (void *)this;
        AddRef();
        return S_OK;
    }

    if (iid == IID_IUnknown)
    {
        *ppvObject = (void *)this;
        AddRef();
        return S_OK;
    }
	return E_NOINTERFACE;
}


HRESULT CRTCEvents::Advise(IRTCClient *pClient, HWND hWnd)
{
	IConnectionPointContainer * pCPC = NULL;
	IConnectionPoint * pCP = NULL;
    HRESULT hr;

   
	hr = pClient->QueryInterface(IID_IConnectionPointContainer, (void**)&pCPC);

	if (SUCCEEDED(hr))
    {
        
		hr = pCPC->FindConnectionPoint(IID_IRTCEventNotification, &pCP);

        SAFE_RELEASE(pCPC);

        if (SUCCEEDED(hr))
        {
            
		    hr = pCP->Advise(this, &m_dwCookie);

            SAFE_RELEASE(pCP);
        }
    }

   
    m_hWnd = hWnd;
	
	return hr;
}


HRESULT CRTCEvents::Unadvise(IRTCClient *pClient)
{
	IConnectionPointContainer * pCPC = NULL;
	IConnectionPoint * pCP = NULL;
    HRESULT hr;

    if (m_dwCookie)
    {
        
	    hr = pClient->QueryInterface(IID_IConnectionPointContainer, (void**)&pCPC);

	    if (SUCCEEDED(hr))
        {
            
		    hr = pCPC->FindConnectionPoint(IID_IRTCEventNotification, &pCP);

            SAFE_RELEASE(pCPC);

            if (SUCCEEDED(hr))
            {
               
		        hr = pCP->Unadvise(m_dwCookie);

                SAFE_RELEASE(pCP);
            }
        }
    }

	return hr;
}


HRESULT STDMETHODCALLTYPE CRTCEvents::Event(RTC_EVENT enEvent, IDispatch *pDisp)
{
	
    pDisp->AddRef();

  
    PostMessage( m_hWnd, WM_RTC_EVENT, (WPARAM)enEvent, (LPARAM)pDisp );

    return S_OK;
}
