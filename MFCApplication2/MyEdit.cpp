// MyEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MyEdit.h"


// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{
	m_bkColor = 0xFFFFFF;
	m_r = true;
	m_tm = 100;
	//m_textColor = 0xA0A0A0;
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
ON_WM_PAINT()
END_MESSAGE_MAP()
void CMyEdit::SetBkColor(COLORREF color)
{
	m_bkColor = color;
}

void CMyEdit::SetTextColor(COLORREF color)
{
	m_textColor = color;
}
void CMyEdit::SetR(bool s)
{
	m_r = s;
}
void CMyEdit::Settm(int s)
{
	m_tm = s;
}


void CMyEdit::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	HDC hDestDC = dc.m_hDC;
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
	MapWindowPoints(GetParent(), &pt, 1);
	//	pParent->m_bkImage.BitBlt(hDC, rc, pt, SRCCOPY);
	UINT IDC;
	if (GetParent() == AfxGetMainWnd())
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
	nAlpha = m_tm;
	int nOffset = 0;

	HBRUSH hbr = CreateSolidBrush(m_bkColor);
	FillRect(hMaskDC, &rc, hbr);
	DeleteObject(hbr);

	BLENDFUNCTION blend;
	memset(&blend, 0, sizeof(blend));
	blend.BlendOp = AC_SRC_OVER;
	blend.SourceConstantAlpha = nAlpha; // 透明度 最大255
	HRGN hRgn = 0;
	if (m_r)
	{
		int R = 5;
	    hRgn = CreateRoundRectRgn(0, 0, nWindth, nHeight, R, R);
		SelectClipRgn(hDC, hRgn);
	}
	AlphaBlend(hDC, 0, 0, nWindth, nHeight, hMaskDC, 0, 0, nWindth, nHeight, blend);
	if (m_r)
	{
		SelectClipRgn(hDC, NULL);
		DeleteObject(hRgn);
	}
	CString strText;
	GetWindowText(strText);
	if (strText != _T("")){
		rc.InflateRect(-2, -2);
		rc.OffsetRect(nOffset, nOffset);
		HFONT hFont;
		hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
		::SetTextColor(hDC, m_textColor);

		if (GetPasswordChar() == 42) strText = "**********";
		::DrawText(hDC, strText, -1, &rc, DT_SINGLELINE  | DT_WORD_ELLIPSIS);
		::SelectObject(hDC, hOldFont);
		DeleteObject(hOldFont);
		DeleteObject(hFont);
	}
	BitBlt(hDestDC, 0, 0, nWindth, nHeight, hDC, 0, 0, SRCCOPY);
	//删除资源,释放内存-----------------------
	SelectObject(hDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteDC(hDC);
	SelectObject(hMaskDC, hOldMaskBitmap);
	DeleteObject(hMaskBitmap);
	DeleteObject(hOldMaskBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hMaskDC);
}

