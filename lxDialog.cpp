//
//      自动改变控件位置和大小的对话框类
//      文件名：lxDialog.cpp
//      作者：StarLee(coolstarlee@sohu.com)
//

#include "stdafx.h"
#include "lxDialog.h"

//  表示可改变大小的图标ID
#ifndef OBM_SIZE
#define OBM_SIZE 32766
#endif

ClxDialog::ClxDialog(UINT nID, CWnd* pParent /*=NULL*/)
: CDialog(nID, pParent)
, m_iClientWidth(0)
, m_iClientHeight(0)
, m_iMinWidth(0)
, m_iMinHeight(0)
, m_pControlArray(NULL)
, m_iControlNumber(0)
, m_bShowSizeIcon(TRUE)
{}

BEGIN_MESSAGE_MAP(ClxDialog, CDialog)
ON_WM_SIZE()
ON_WM_SIZING()
END_MESSAGE_MAP()

BOOL ClxDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
	
    //  设置对话框为可变大小的
    ModifyStyle(0, WS_SIZEBOX);
	
    //  以对话框的初始大小作为对话框的宽度和高度的最小值
    CRect rectDlg;
    GetWindowRect(rectDlg);
    m_iMinWidth = rectDlg.Width();
    m_iMinHeight = rectDlg.Height();
	
    //  得到对话框client区域的大小
    CRect rectClient;
    GetClientRect(rectClient);
    m_iClientWidth = rectClient.Width();
    m_iClientHeight = rectClient.Height();
	
    //  Load图标
    m_bmpSizeIcon.LoadOEMBitmap(OBM_SIZE);
    m_bmpSizeIcon.GetBitmap(&m_bitmap);
	
    //  创建显示图标的静态控件并放在对话框右下角
    m_wndSizeIcon.Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, CRect(0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight), this, 0);
    m_wndSizeIcon.SetBitmap(m_bmpSizeIcon);
    m_wndSizeIcon.MoveWindow(m_iClientWidth - m_bitmap.bmWidth, m_iClientHeight - m_bitmap.bmHeight, m_bitmap.bmWidth, m_bitmap.bmHeight);
	
    //  显示图标
    m_wndSizeIcon.ShowWindow(m_bShowSizeIcon);
	
    return TRUE;
}

void ClxDialog::OnSize(UINT nType, int cx, int cy) 
{
    CDialog::OnSize(nType, cx, cy);
	
    //  对话框宽度和高度的增量 
    int iIncrementX = cx - m_iClientWidth;
    int iIncrementY = cy - m_iClientHeight;
	
    //  最小化时增量为0
    if (nType == SIZE_MINIMIZED)
    {
        iIncrementX = iIncrementY = 0;
    }
	
    for (int i = 0; i < m_iControlNumber; i++)
    {
        CWnd *pWndCtrl = NULL;
		
        int iId = m_pControlArray[i].iId;
        int iFlag = m_pControlArray[i].iFlag;
        int iPercent = m_pControlArray[i].iPercent;
		
        //  无效值
        if ((iPercent < 0) || (iPercent > 100))
            continue;
		
        //  得到控件指针
        pWndCtrl = GetDlgItem(iId);
        if ((NULL != pWndCtrl) && IsWindow(pWndCtrl->GetSafeHwnd()))
        {
            CRect rectCtrl;
            pWndCtrl->GetWindowRect(rectCtrl);
			
            ScreenToClient(rectCtrl);
			
            int iLeft = rectCtrl.left;
            int iTop = rectCtrl.top;
            int iWidth = rectCtrl.Width();
            int iHeight = rectCtrl.Height();
			
            switch (iFlag)
            {
            case MOVEX:  //  X方向移动
                iLeft += (iIncrementX * iPercent / 100);
                break;
				
            case MOVEY:  //  Y方向移动
                iTop += (iIncrementY * iPercent / 100);
                break;
				
            case MOVEXY:  //  X方向和Y方向同时移动
                iLeft += (iIncrementX * iPercent / 100);
                iTop += (iIncrementY * iPercent / 100);
                break;
				
            case ELASTICX:  //  X方向改变大小
                iWidth += (iIncrementX * iPercent / 100);
                break;
				
            case ELASTICY:  //  Y方向改变大小
                iHeight += (iIncrementY * iPercent / 100);
                break;
				
            case ELASTICXY:  //  X方向和Y方向同时改变大小
                iWidth += (iIncrementX * iPercent / 100);
                iHeight += (iIncrementY * iPercent / 100);
                break;
				
            default:
                ;
            }
			
            //  把控件移动到新位置
            pWndCtrl->MoveWindow(iLeft, iTop, iWidth, iHeight);
		}
    }
	
    //  把图标移动到对话框右下角
    if (IsWindow(m_wndSizeIcon.GetSafeHwnd()))
        m_wndSizeIcon.MoveWindow(cx - m_bitmap.bmWidth, cy - m_bitmap.bmHeight, m_bitmap.bmWidth, m_bitmap.bmHeight);
	
    //  记录对话框client区域的大小
    if (nType != SIZE_MINIMIZED)
    {
        m_iClientWidth = cx;
        m_iClientHeight = cy;
    }
}

void ClxDialog::OnSizing(UINT nSide, LPRECT lpRect)
{
    CDialog::OnSizing(nSide, lpRect);
	
    //  对话框不能小于初始大小
	
    int iWidth = lpRect->right - lpRect->left;
    int iHeight = lpRect->bottom - lpRect->top;
	
    if (iWidth <= m_iMinWidth)
        lpRect->right = lpRect->left + m_iMinWidth;
	
    if(iHeight <= m_iMinHeight)
        lpRect->bottom = lpRect->top + m_iMinHeight;
}

BOOL ClxDialog::SetControlProperty(PDLGCTLINFO lp, int nElements)
{
    //  设置控件数组信息
	
    if (NULL == lp)
        return FALSE;
	
    if (nElements <= 0)
        return FALSE;
	
    m_pControlArray = lp;
    m_iControlNumber = nElements;
	
    return TRUE;
}

void ClxDialog::ShowSizeIcon(BOOL bShow /*=TRUE*/)
{
    m_bShowSizeIcon = bShow;
}