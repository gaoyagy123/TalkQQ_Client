// MyButton.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MyButton.h"
#include "MFCApplication2Dlg.h"

// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{
	m_bkColor = 0xFFFFFF;
	m_textColor = 0x000000;
	m_Stye = 0;
	m_tm = 100;
	m_r = true;
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_ENABLE()
END_MESSAGE_MAP()



// CMyButton 消息处理程序

void CMyButton::SetBkColor(COLORREF color)
{
	m_bkColor = color;
}
void CMyButton::SetmStye(int s)
{
	m_Stye = s;
}
void CMyButton::Settm(int s)
{
	m_tm = s;
}
void CMyButton::SetR(bool s)
{
	m_r = s;
}
void CMyButton::SetDown(bool s)
{
	m_bDown = s;
}
void CMyButton::SetTextColor(COLORREF color)
{
	m_textColor = color;
}

BOOL CMyButton::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bRet = CButton::PreCreateWindow(cs);
	ButtonInit();
	return bRet;
}

void CMyButton::PreSubclassWindow()
{
	CButton::PreSubclassWindow();
	ButtonInit();
}
void CMyButton::ButtonInit()
{
	m_bTracking = false;
	m_bOver = m_bDown = m_bDisable = false;
	m_bDisable = IsWindowEnabled() ? FALSE : TRUE;
	ModifyStyle(NULL, BS_OWNERDRAW);
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	DrawButton(lpDrawItemStruct->hDC);
}

void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bTracking)
	{
		m_bOver = TRUE;
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 50;
		m_bTracking =_TrackMouseEvent(&tme);
	}

	CButton::OnMouseMove(nFlags, point);
}

void CMyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bDown = TRUE;

	CButton::OnLButtonDown(nFlags, point);
}

void CMyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_Stye==0) 
	m_bDown = FALSE;
	CButton::OnLButtonUp(nFlags, point);
}
LRESULT CMyButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	m_bOver = FALSE;
	m_bTracking = FALSE;
	if (m_Stye != 1) m_bDown = FALSE;
	InvalidateRect(NULL, FALSE);
	return 0;
}

LRESULT CMyButton::OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	m_bOver = TRUE;
	InvalidateRect(NULL);
	return 0;
}
void CMyButton::DrawButton()
{
	HDC hDC = ::GetDC(m_hWnd);
	DrawButton(hDC);
	::ReleaseDC(m_hWnd, hDC);
}
void CMyButton::DrawButton(HDC hDestDC)
{
	CRect rc;
	GetClientRect(rc);
	int nWindth = rc.Width();
	int nHeight = rc.Height();
	HDC hDC = CreateCompatibleDC(hDestDC);//创建兼容DC,采用双缓冲画出
	HDC hMaskDC = CreateCompatibleDC(hDestDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hDestDC, nWindth, nHeight);
	HBITMAP hMaskBitmap = CreateCompatibleBitmap(hDestDC, nWindth, nHeight);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);
	HBITMAP hOldMaskBitmap = (HBITMAP)SelectObject(hMaskDC, hMaskBitmap);
	SetBkMode(hDC, TRANSPARENT);

	//把父窗口的背景图复制到按钮的DC上,实现视觉透明----------------
	CPoint pt(0, 0);
	MapWindowPoints(GetParent(), &pt,  1);
//	pParent->m_bkImage.BitBlt(hDC, rc, pt, SRCCOPY);
	UINT IDC;
	if (GetParent()== AfxGetMainWnd())
	{
		IDC = IDB_BITMAP1;
	}
	else
	{
		IDC = IDB_BITMAP2;
	}
	CImage	A;
	A.LoadFromResource(AfxGetInstanceHandle(), IDC);
	A.BitBlt(hDC, rc, pt, SRCCOPY);
	//-------------------------------------------------------------
	int nAlpha;
	if (m_Stye != 1)
		nAlpha = 100;
	else
		nAlpha = 0;
	int nOffset = 0;

	HBRUSH hbr = CreateSolidBrush(m_bkColor);
	FillRect(hMaskDC, &rc, hbr);
	DeleteObject(hbr);
	if (m_bDisable){
		nAlpha = 0;
	}
	else if (m_bDown){
		if (m_Stye != 1)
		{
			nAlpha = m_tm+80;
			nOffset = 1;
		}
		else
		{
			nAlpha = 50;
		}
	}
	else if (m_bOver){
		if (m_Stye != 1)
			nAlpha = m_tm+50;
		else
			nAlpha = 25;
	}
	else{
		if (m_Stye != 1)
			nAlpha = m_tm;
		else
			nAlpha = 0;
	}

	BLENDFUNCTION blend;
	memset(&blend, 0, sizeof(blend));
	blend.BlendOp = AC_SRC_OVER;
	blend.SourceConstantAlpha = nAlpha; // 透明度 最大255

	int R;
	if (m_Stye != 1 && m_r)
		R = 5;
	else
		R = 0;
	HRGN hRgn = CreateRoundRectRgn(0, 0, nWindth, nHeight, R, R);
	SelectClipRgn(hDC, hRgn);
	AlphaBlend(hDC, 0, 0, nWindth, nHeight, hMaskDC, 0, 0, nWindth, nHeight, blend);
	CString strText;
	GetWindowText(strText);
	if (strText != _T("")){
		rc.InflateRect(-2, -2);
		rc.OffsetRect(nOffset, nOffset);
		HFONT hFont;
		hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
		::SetTextColor(hDC, m_textColor);
		::DrawText(hDC, strText, -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_WORD_ELLIPSIS);
		::SelectObject(hDC, hOldFont);
		DeleteObject(hOldFont);
		DeleteObject(hFont);
	}
	SelectClipRgn(hDC, NULL);
	DeleteObject(hRgn);
	if (m_Stye > 1)
	{
		CBitmap FootballBMP;
		FootballBMP.LoadBitmap(m_Stye);

		BITMAP A;
		FootballBMP.GetBitmap(&A);
		CDC ImageDC;
		CDC pDC;
		pDC.Attach(hDC);
		ImageDC.CreateCompatibleDC(&pDC);
		CBitmap *pOldImageBMP = ImageDC.SelectObject(&FootballBMP);
		TransparentBlt(pDC.m_hDC, nWindth / 2 - A.bmWidth / 2, nHeight / 2 - A.bmHeight / 2,
			A.bmWidth, A.bmHeight, ImageDC.m_hDC, 0, 0, A.bmWidth, A.bmHeight, RGB(0xff, 0xff, 0xff));
		ImageDC.SelectObject(pOldImageBMP);

		BitBlt(hDestDC, 0, 0, nWindth, nHeight, pDC.m_hDC, 0, 0, SRCCOPY);

		//删除资源,释放内存-----------------------
		ImageDC.DeleteDC();
		pDC.DeleteDC();
		FootballBMP.DeleteObject();
		pOldImageBMP->DeleteObject();
	}
	else
	{
		//复制到控件的DC上------------------------
		BitBlt(hDestDC, 0, 0, nWindth, nHeight, hDC, 0, 0, SRCCOPY);
	}
	//删除资源,释放内存-----------------------
	SelectObject(hDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hDC);

	SelectObject(hMaskDC, hOldMaskBitmap);
	DeleteObject(hMaskBitmap);
	DeleteObject(hOldMaskBitmap);
	DeleteDC(hMaskDC);

}
void CMyButton::OnEnable(BOOL bEnable)
{
	CButton::OnEnable(bEnable);
	m_bDisable = IsWindowEnabled() ? FALSE : TRUE;
	DrawButton();
}

