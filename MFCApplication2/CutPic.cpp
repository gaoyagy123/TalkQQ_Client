// CutPic.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "CutPic.h"
#include "afxdialogex.h"


// CutPic 对话框

IMPLEMENT_DYNAMIC(CutPic, CDialogEx)

CutPic::CutPic(CWnd* pParent /*=NULL*/)
	: CDialogEx(CutPic::IDD, pParent)
{

}

CutPic::~CutPic()
{
}

void CutPic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICFDJ, mfdj);
}


BEGIN_MESSAGE_MAP(CutPic, CDialogEx)
	ON_BN_CLICKED(IDOK, &CutPic::OnBnClickedOk)
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CutPic 消息处理程序


void CutPic::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL CutPic::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int   cx = GetSystemMetrics(SM_CXSCREEN);
	int   cy = GetSystemMetrics(SM_CYSCREEN);
	//cx = 500;
	//cy = 500;
	SetWindowPos(&CWnd::wndTopMost, 0, 0, cx, cy, NULL);
	StartPoint.x = -1;
	StartPoint.y = -1;

	HDC DestDC = ::GetDC(NULL);
	HDC hDestDC = CreateCompatibleDC(DestDC);
    SrcBmp = ::CreateCompatibleBitmap(DestDC, cx, cy);
	HBITMAP B = (HBITMAP)SelectObject(hDestDC, SrcBmp);
	BitBlt(hDestDC, 0, 0, cx, cy, DestDC, 0, 0, SRCCOPY);
	SrcBmp = (HBITMAP)SelectObject(hDestDC, B);
	DeleteObject(B);
	DeleteDC(hDestDC);
	::ReleaseDC(NULL, DestDC);

	TBitMap = SetTM();

	SetBackgroundImage(TBitMap);
	//
	return TRUE;  
}

HBITMAP CutPic::SetTM()
{
	CRect rc;
	HWND DH = GetDesktopWindow()->m_hWnd;
	::GetClientRect(DH, rc);
	int nWindth = rc.Width();
	int nHeight = rc.Height();

	HDC DestDC = ::GetDC(DH);

	HDC hDestDC = CreateCompatibleDC(DestDC);
	HBITMAP TBitMap = ::CreateCompatibleBitmap(DestDC, nWindth, nHeight);
	HBITMAP B = (HBITMAP)SelectObject(hDestDC, TBitMap);

	HDC hDC = CreateCompatibleDC(hDestDC);//创建兼容DC,采用双缓冲画出
	HBITMAP hBitmap = CreateCompatibleBitmap(hDestDC, nWindth, nHeight);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);

	HDC hMaskDC = CreateCompatibleDC(hDestDC);
	HBITMAP hMaskBitmap = CreateCompatibleBitmap(hDestDC, nWindth, nHeight);
	HBITMAP hOldMaskBitmap = (HBITMAP)SelectObject(hMaskDC, hMaskBitmap);
	//-------------------------------------------------------------

	BitBlt(hDC, 0, 0, nWindth, nHeight, DestDC, 0, 0, SRCCOPY);

	HBRUSH hbr = CreateSolidBrush(0);
	FillRect(hMaskDC, &rc, hbr);
	DeleteObject(hbr);

	BLENDFUNCTION blend;
	memset(&blend, 0, sizeof(blend));
	blend.BlendOp = AC_SRC_OVER;
	blend.SourceConstantAlpha = 90; // 透明度 最大255
	AlphaBlend(hDC, 0, 0, nWindth, nHeight, hMaskDC, 0, 0, nWindth, nHeight, blend);

	BitBlt(hDestDC, 0, 0, nWindth, nHeight, hDC, 0, 0, SRCCOPY);

	//删除资源,释放内存-----------------------
	SelectObject(hDC, hOldBitmap);
	DeleteObject(hBitmap);
	DeleteObject(hOldBitmap);
	DeleteDC(hDC);

	SelectObject(hMaskDC, hOldMaskBitmap);
	DeleteObject(hMaskBitmap);
	DeleteObject(hOldMaskBitmap);
	DeleteDC(hMaskDC);

	TBitMap = (HBITMAP)SelectObject(hDestDC, B);
	DeleteObject(B);
	DeleteDC(hDestDC);
	::ReleaseDC(DH, DestDC);

	return TBitMap;
}

void CutPic::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (cutover) {
		InvalidateRect(NULL);
		cutover = false;
		gethw = true;
		return;
	}
	this->DestroyWindow();
	delete this;
}


void CutPic::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!cutover) {
		StartPoint = point;

		cut = true;
	}
	else if (PtInRect(&rect, point))
	{
		MovePoint = point;
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CutPic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (cutover) return;
	if (gethw)
	{
		cut = false;
		cutover = true;
		gethw = false;

		StartPoint.x = rect.left;
		StartPoint.y = rect.top;
		EndPoint.x = rect.right;
		EndPoint.y = rect.bottom;
		mfdj.ShowWindow(0);
		InvalidateRect(NULL);
		return;
	}
	EndPoint = point;
	cut = false;
	int w = abs(rect.right - rect.left);
	int h = abs(rect.bottom - rect.top);
	if (w > 1 && h > 1)
	{
		cutover = true;
		mfdj.ShowWindow(0);
	}
	else
		InvalidateRect(NULL);
	CDialog::OnLButtonUp(nFlags, point);
}


void CutPic::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!cutover)
	{
		FDJPoint = point;
		mfdj.ShowWindow(5);
		RECT R;
		mfdj.GetClientRect(&R);
		int a, b;
		int cx = GetSystemMetrics(SM_CXSCREEN);
		int cy = GetSystemMetrics(SM_CYSCREEN);
		a = point.x + 5;
		b = point.y + 25;
		if (a + R.right - R.left > cx) a = point.x - 5 + R.left - R.right;
		if (b + R.bottom - R.top > cy) b = point.y - 25 + R.left - R.right;
		mfdj.MoveWindow(a, b, R.right - R.left, R.bottom - R.top);
		if (nFlags == 0) GetPointWindow(point);
	}
	if (nFlags == MK_LBUTTON&&!cutover)
	{
		EndPoint = point;
		gethw = false;
		InvalidateRect(NULL);
	}
	else
	{
		if (PtInRect(&rect, point) && cutover)
		{
			SetClassLong(this->GetSafeHwnd(),
				GCL_HCURSOR,
				(LONG)LoadCursor(NULL, IDC_SIZEALL));
			if (nFlags == MK_LBUTTON)
			{
				int m = point.x - MovePoint.x;
				int n = point.y - MovePoint.y;
				MovePoint = point;
				StartPoint.x = StartPoint.x + m;
				StartPoint.y = StartPoint.y + n;
				EndPoint.x = EndPoint.x + m;
				EndPoint.y = EndPoint.y + n;
				InvalidateRect(NULL);
			}
		}
		else
		{
			SetClassLong(this->GetSafeHwnd(),
				GCL_HCURSOR,
				(LONG)LoadCursor(NULL, IDC_ARROW));
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}



BOOL CutPic::DestroyWindow()
{
	// TODO:  在此添加专用代码和/或调用基类
	DeleteObject(TBitMap);
	DeleteObject(SrcBmp);
	return CDialogEx::DestroyWindow();
}

void CutPic::GetPointWindow(CPoint point)
{
	HWND hw = 0;
	RECT rc;
	do
	{
		hw = ::FindWindowEx(NULL, hw, NULL, NULL);
		if (hw > 0 && ::IsWindowVisible(hw) && hw != this->m_hWnd)
		{
			::GetWindowRect(hw, &rc);
			int   cx = GetSystemMetrics(SM_CXSCREEN);
			int   cy = GetSystemMetrics(SM_CYSCREEN);
			if (rc.left == 0 && rc.top == 0 &&
				rc.right == cx && rc.bottom == cy) continue;
			if (PtInRect(&rc, point))
			{
				rect = rc;
				gethw = true;
				InvalidateRect(NULL);
				return;
			}
		}
	} while (hw > 0);
}

void CutPic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (mfdj.IsWindowVisible()) 
	{
		if (gethw)
		{
			CDC xdc;
			xdc.CreateCompatibleDC(&dc);
			HBITMAP old = (HBITMAP)xdc.SelectObject(SrcBmp);
			RECT wrc = rect;
			dc.BitBlt(wrc.left, wrc.top, wrc.right - wrc.left, wrc.bottom - wrc.top
				, &xdc, wrc.left, wrc.top, SRCCOPY);

			InflateRect(&wrc, 2, 2);
			dc.Draw3dRect(&wrc, RGB(00, 0xAE, 255), RGB(00, 0xAE, 255));
			for (int j = 2; j >= -2; j--)
			{
				InflateRect(&wrc, -1, -1);
				dc.Draw3dRect(&wrc, RGB(00, 0xAE, 255), RGB(00, 0xAE, 255));
			}
			SrcBmp = (HBITMAP)xdc.SelectObject(old);
			DeleteObject(old);
			xdc.DeleteDC();
		}
		DrawFdj();
	}
	if (!cut && !cutover) return;
	rect.left = StartPoint.x;
	rect.top = StartPoint.y;
	rect.right = EndPoint.x;
	rect.bottom = EndPoint.y;
	CDC xdc;
	xdc.CreateCompatibleDC(&dc);
	HBITMAP old = (HBITMAP)xdc.SelectObject(SrcBmp);

	dc.BitBlt(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top
		, &xdc, rect.left, rect.top, SRCCOPY);
	dc.Draw3dRect(&rect, RGB(00, 0xAE, 255), RGB(00, 0xAE, 255));
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;
	int wh = 2;
	for (int i = 1; i <= wh; i++)
	{
		dc.Draw3dRect(rect.left + w / 2 - i, rect.top - i + 1, 2 * i, 2 * i, RGB(00, 0xAE, 255), RGB(00, 0xAE, 255));
		dc.Draw3dRect(rect.left + w / 2 - i, rect.bottom - i - 1, 2 * i, 2 * i, RGB(00, 0xAE, 255), RGB(00, 0xAE, 255));
		dc.Draw3dRect(rect.left - i + 1, rect.top + h / 2 - i, 2 * i, 2 * i, RGB(00, 0xAE, 255), RGB(00, 0xAE, 255));
		dc.Draw3dRect(rect.right - i - 1, rect.top + h / 2 - i, 2 * i, 2 * i, RGB(00, 0xAE, 255), RGB(00, 0xAE, 255));
		
		dc.Draw3dRect(rect.left - i + 1, rect.top - i + 1 , 2 * i, 2 * i, RGB(00, 0xAE, 255), RGB(00, 0xAE, 255));
		dc.Draw3dRect(rect.right - i - 1, rect.top - i + 1 , 2 * i, 2 * i, RGB(00, 0xAE, 255), RGB(00, 0xAE, 255));
		dc.Draw3dRect(rect.left - i + 1, rect.bottom - i - 1, 2 * i, 2 * i, RGB(00, 0xAE, 255), RGB(00, 0xAE, 255));
		dc.Draw3dRect(rect.right - i - 1, rect.bottom - i - 1, 2 * i, 2 * i, RGB(00, 0xAE, 255), RGB(00, 0xAE, 255));
	}
	SrcBmp = (HBITMAP)xdc.SelectObject(old);
	DeleteObject(old);
	xdc.DeleteDC();
}
void CutPic::DrawFdj()
{
	CPaintDC dc(&mfdj);

	RECT FDJrc;
	mfdj.GetClientRect(&FDJrc);
	int w = FDJrc.right - FDJrc.left;
	int h = FDJrc.bottom - FDJrc.top;
	int d = 35;
	CDC xdc;
	xdc.CreateCompatibleDC(&dc);
	HBITMAP old = (HBITMAP)xdc.SelectObject(SrcBmp);

	HBRUSH hbr = CreateSolidBrush(0);
	FillRect(dc, &FDJrc, hbr);
	DeleteObject(hbr);

	RECT rect1 = FDJrc;
	rect1.bottom = rect1.bottom - d;
    hbr = CreateSolidBrush(RGB(255, 255, 255));
	FillRect(dc, &rect1, hbr);
	DeleteObject(hbr);

	int wh = 18, bord = 3;
	dc.StretchBlt(FDJrc.left + bord, FDJrc.top + bord, w - 2 * bord, h - d - 2 * bord
		, &xdc, FDJPoint.x - wh, FDJPoint.y - wh, 2 * wh, 2 * wh, SRCCOPY);
	int c= GetPixel(dc.m_hDC, FDJrc.right / 2, FDJrc.bottom / 2);
	SrcBmp = (HBITMAP)xdc.SelectObject(old);
	DeleteObject(old);
	xdc.DeleteDC();
	dc.Draw3dRect(&FDJrc, RGB(00, 0xAE, 0), RGB(00, 0xAE, 0));

	RECT re2, re3;
	re2.left = FDJrc.left + bord;
	re2.top = (FDJrc.bottom - d) / 2 - bord + 1;
	re2.right = FDJrc.right - bord;
	re2.bottom = (FDJrc.bottom - d) / 2 + bord - 1;

	re3.left = FDJrc.right / 2 - bord + 1;
	re3.top = FDJrc.top + bord;
	re3.right = FDJrc.right / 2 + bord - 1;
	re3.bottom = FDJrc.bottom - d - bord;

	hbr = CreateSolidBrush(RGB(00, 0xAE - 40 , 210));
	FillRect(dc, &re2, hbr);
	FillRect(dc, &re3, hbr);
	DeleteObject(hbr);

	RECT rc;
	rc.left = 2 ;
	rc.top = FDJrc.bottom - d;
	rc.right = FDJrc.right;
	rc.bottom = FDJrc.bottom;
	int W = abs(rect.right - rect.left);
	int H = abs(rect.bottom - rect.top);
	CString strText;
	strText.Format("%d * %d\nRGB:(%d,%d,%d)", W, H, GetRValue(c), GetGValue(c), GetBValue(c));

	HFONT hFont = (HFONT)SendMessage(WM_GETFONT);
	if (!hFont)
		hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	HFONT hOldFont = (HFONT)dc.SelectObject(hFont);
	dc.SetBkColor(0);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.DrawText(strText, -1, &rc, DT_WORD_ELLIPSIS);
	dc.SelectObject(hOldFont);
	DeleteObject(hFont);
	DeleteObject(hOldFont);

}
void CutPic::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (PtInRect(&rect, point))
	{

		talktotalk *dlg = (talktotalk *)GetParent();
		CreateDirectory(".Cache", NULL);
		CString str = SaveBmp();
		int i = dlg->text2.GetPicInfo();
		dlg->text1.objectSend.num = i + 1;
		dlg->text1.objectSend.obj[i].strpath = str;
		dlg->text1.objectSend.obj[i].Type = "bmp";
		long a, b;
		dlg->text2.GetSel(a, b);
		dlg->text1.objectSend.obj[i].Sel = a;
		dlg->text2.InserObjbyString(str, "bmp");
		SetClassLong(this->GetSafeHwnd(),
			GCL_HCURSOR,
			(LONG)LoadCursor(NULL, IDC_ARROW));
		this->DestroyWindow();
		delete this;
		return;
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}

CString CutPic::SaveBmp()
{
	CDC *hdc = GetDC();
	CDC xdc, dc;
	dc.CreateCompatibleDC(hdc);
	xdc.CreateCompatibleDC(&dc);
	HBITMAP hbitmap;
	hbitmap = CreateCompatibleBitmap(hdc->m_hDC, rect.right - rect.left, rect.bottom - rect.top);
	HBITMAP old = (HBITMAP)xdc.SelectObject(SrcBmp);
	HBITMAP oldbitmap = (HBITMAP)dc.SelectObject(hbitmap);
	dc.BitBlt(0, 0, rect.right - rect.left, rect.bottom - rect.top
		, &xdc, rect.left, rect.top, SRCCOPY);

	CString lpszFilePah;
	int SJS;
	ULONG RND;
	SJS = rand() % 10000;
	RND = GetTickCount();

	lpszFilePah.Format(".Cache\\%d&%d&%d.bmp", RND, SJS, 1002);
	hbitmap = (HBITMAP)dc.SelectObject(oldbitmap);
	SaveBitMapToFile(hbitmap, lpszFilePah);

	SrcBmp = (HBITMAP)xdc.SelectObject(old);
	DeleteObject(old);
	DeleteObject(oldbitmap);
	DeleteObject(hbitmap);
	xdc.DeleteDC();
	dc.DeleteDC();
	hdc->ReleaseOutputDC();

	return lpszFilePah;
}

BOOL CutPic::SaveBitMapToFile(HBITMAP hBitmap, CString lpFileName)
{
	HDC		hDC;		//设备描述表       
	int		iBits;		//当前显示分辨率下每个像素所占字节数   
	WORD	wBitCount;	//位图中每个像素所占字节数   
	DWORD	dwPaletteSize = 0,//定义调色板大小，位图中像素字节大小，位图文件大小，写入文件字节数
		dwBmBitsSize,
		dwDIBSize,
		dwWritten;
	BITMAP	Bitmap;
	BITMAPFILEHEADER	bmfHdr;	//位图属性结构
	BITMAPINFOHEADER	bi;		//位图文件头结构                
	LPBITMAPINFOHEADER	lpbi;	//位图信息头结构           
	HANDLE	fh, hDib, hPal, hOldPal = NULL;//指向位图信息头结构,定义文件，分配内存句柄，调色板句柄
	//计算位图文件每个像素所占字节数   
	hDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL)*GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else if (iBits <= 24)
		wBitCount = 24;
	else
		wBitCount = 32;
	//计算调色板大小   
	if (wBitCount <= 8)
		dwPaletteSize = (1 << wBitCount)*sizeof(RGBQUAD);

	//设置位图信息头结构
	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap.bmWidth;
	bi.biHeight = Bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	dwBmBitsSize = ((Bitmap.bmWidth*wBitCount + 31) / 32) * 4 * Bitmap.bmHeight;

	//为位图内容分配内存   
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	//   处理调色板         
	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = ::GetDC(NULL);
		hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}

	//   获取该调色板下新的像素值   
	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
		(LPSTR)lpbi + sizeof(BITMAPINFOHEADER)+dwPaletteSize,
		(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

	//恢复调色板         
	if (hOldPal)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal, TRUE);
		RealizePalette(hDC);
		::ReleaseDC(NULL, hDC);
	}

	//创建位图文件           
	fh = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (fh == INVALID_HANDLE_VALUE)
		return   FALSE;

	//   设置位图文件头   
	bmfHdr.bfType = 0x4D42;//   "BM"   
	dwDIBSize = sizeof(BITMAPFILEHEADER)+
		sizeof(BITMAPINFOHEADER)+
		dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+
		(DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;

	//   写入位图文件头
	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	//   写入位图文件其余内容
	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);

	//消除内存分配
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return   TRUE;
}
