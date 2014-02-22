/*********************************************************************************
*  Author         : orbit                                                        *
*  Description    : 这个文件定义CSMButton类，这是一个支持OwnerDraw的按钮类，     *
*  Date           : May 12, 2003                                                 *
*  Last-modified  : Nov 9, 2003                                                  *
*  Contact us     : inte2000@163.com,support@winmsg.com                          *
*  Web Page       : http://www.winmsg.com/cn/orbit.htm                           *
*                   http://blog.csdn.net/orbit/          (关于代码的更新)        *
*********************************************************************************/
#if !defined(AFX_SMBUTTON_H__971C2FCB_0C24_4BA0_BFC9_3204648F1CA2__INCLUDED_)
#define AFX_SMBUTTON_H__971C2FCB_0C24_4BA0_BFC9_3204648F1CA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SMButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSMButton window

class CSMButton : public CButton
{
// Construction
public:
	CSMButton();

// Attributes
public:

// Operations
public:
	void InitDefaultColor();
	void SetFlat(BOOL bState, BOOL bRepaint = FALSE);
	BOOL GetFlat();
	void SetFlatFocus(BOOL bDrawFlatFocus, BOOL bRepaint = FALSE);
	BOOL GetFlatFocus();
	void DrawBorder(BOOL bEnable);
	void SetActiveBgColor(COLORREF crNew, BOOL bRepaint = FALSE);
	void SetInactiveBgColor(COLORREF crNew, BOOL bRepaint = FALSE);
	void SetTextColor(COLORREF crNew, BOOL bRepaint = FALSE);
	void SetTextHightColor(COLORREF crNew, BOOL bRepaint = FALSE);
	void SetBorderColor(COLORREF crNew, BOOL bRepaint = FALSE);
	void SetButtonCursor(HCURSOR hCursor);
	void ResetWhenClose();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSMButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSMButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSMButton)
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
protected:
	BOOL m_bDefaultBtn;
	BOOL m_MouseOnButton;
	BOOL m_bAlwaysTrack;
	BOOL m_bIsFlat;			// Is a flat button?
	BOOL m_bDrawBorder;		// Draw border?
	BOOL m_bDrawFlatFocus;	// Draw focus rectangle for flat button?
	HCURSOR m_hBtnCursor;
	
	COLORREF m_crInactiveBg;
	COLORREF m_crActiveBg;
	COLORREF m_crText;
	COLORREF m_crTextHilight;
	COLORREF m_crBorder;

};

inline BOOL CSMButton::GetFlat()
{ return m_bIsFlat;}

inline void CSMButton::DrawBorder(BOOL bEnable)
{ m_bDrawBorder = bEnable; }

inline BOOL CSMButton::GetFlatFocus()
{	return m_bDrawFlatFocus; }

inline void CSMButton::SetButtonCursor(HCURSOR hCursor)
{ m_hBtnCursor = hCursor;}
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMBUTTON_H__971C2FCB_0C24_4BA0_BFC9_3204648F1CA2__INCLUDED_)
