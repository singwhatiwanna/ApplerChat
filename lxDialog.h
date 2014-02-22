//
//      自动改变控件位置和大小的对话框类
//      文件名：lxDialog.h
//      作者：StarLee(coolstarlee@sohu.com)
//

class ClxDialog : public CDialog
{
public:
    ClxDialog(UINT nID, CWnd* pParent = NULL);
	
    typedef struct _dlgControlTag 
    {
        int iId;
        int iFlag;
        int iPercent;
    } DLGCTLINFO, *PDLGCTLINFO;
	
    enum
    {
        MOVEX = 0,
			MOVEY,
			MOVEXY,
			ELASTICX,
			ELASTICY,
			ELASTICXY
    };
	
    //  设置控件信息
    BOOL SetControlProperty(PDLGCTLINFO lp, int nElements);
	
    //  是否在对话框右下角显示表示可改变大小的图标
    void ShowSizeIcon(BOOL bShow = TRUE);
	
protected:
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSizing(UINT nSide, LPRECT lpRect);
    DECLARE_MESSAGE_MAP()
		
private:
    int m_iClientWidth;  //  对话框client区域的宽度
    int m_iClientHeight;  //  对话框client区域的高度
    int m_iMinWidth;  //  对话框的最小宽度
    int m_iMinHeight;  //  对话框的最小高度
    PDLGCTLINFO m_pControlArray;  //  控件信息数组指针
    int m_iControlNumber;  //  设置控件信息的控件个数
    BOOL m_bShowSizeIcon;  //  是否显示表示可改变大小的图标
    CStatic m_wndSizeIcon;  //  放图标的静态控件
    //  保存图标的bitmap
    CBitmap m_bmpSizeIcon; 
    BITMAP m_bitmap; 
};