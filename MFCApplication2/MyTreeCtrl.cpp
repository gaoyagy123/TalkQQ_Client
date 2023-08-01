// MyTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MyTreeCtrl.h"


// CMyTreeCtrl

IMPLEMENT_DYNCREATE(CMyTreeCtrl, CTreeCtrl)

CMyTreeCtrl::CMyTreeCtrl()
{

}

CMyTreeCtrl::~CMyTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	ON_WM_PAINT()
//	ON_WM_ERASEBKGND()
//ON_WM_ERASEBKGND()
//ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, &CMyTreeCtrl::OnTvnItemexpanded)
//ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, &CMyTreeCtrl::OnTvnItemexpanded)
//ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, &CMyTreeCtrl::OnTvnItemexpanding)
//ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CMyTreeCtrl 诊断

#ifdef _DEBUG
void CMyTreeCtrl::AssertValid() const
{
	CTreeCtrl::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeCtrl::Dump(CDumpContext& dc) const
{
	CTreeCtrl::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyTreeCtrl 消息处理程序

	// MyTreeCtrl.cpp

void CMyTreeCtrl::OnPaint()
{
	CPaintDC dc(this); //创建显示设备DC
		
	CRect rcclient; // rcclient 用于存放树形控件的大小
	GetClientRect(&rcclient); //得到树形控件区域大小
	//在内存中创建兼容设备描述表

	CDC memdc; //创建内存设备DC
	memdc.CreateCompatibleDC(&dc); //建立与显示设备兼容DC
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rcclient.Width(), rcclient.Height());
	//调用函数CreateCompatibleBitmap 创建位图
	
	CBitmap *pOldbitmap = memdc.SelectObject(&bitmap); //位图句柄选入兼容DC
	//在内存CDC 对象上对TreeView 默认绘图，


	CWnd::DefWindowProc(WM_PAINT, (WPARAM)memdc.m_hDC, 0);

	CDC maskdc;
	maskdc.CreateCompatibleDC(&dc);
	CBitmap maskbitmap;
	maskbitmap.CreateBitmap(rcclient.Width(), rcclient.Height(), 1, 1, NULL); //创建单色位图
	CBitmap *pOldmaskbitmap = maskdc.SelectObject(&maskbitmap);
	maskdc.BitBlt(0, 0, rcclient.Width(), rcclient.Height(), &memdc, rcclient.left, rcclient.top, SRCCOPY);

	CPoint pt(0, 0);
	MapWindowPoints(GetParent(), &pt, 1);
	CImage	A;
	A.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP2);

	A.BitBlt(dc, rcclient, pt, SRCCOPY);
	//TransparentBlt(dc.m_hDC, 0, 0, rcclient.Width(), rcclient.Height(), memdc.m_hDC, 0, 0, rcclient.Width(), rcclient.Height(), RGB(0xff, 0xff, 0xff));
	
	//dc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(), &maskdc, pt.x, pt.y, SRCCOPY);

	//位图与默认背景进行与操作，合成背景图
	memdc.SetBkColor(RGB(0, 0, 0));
	memdc.SetTextColor(RGB(255, 255, 255));
	memdc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(),
		&maskdc, rcclient.left, rcclient.top, SRCAND);

	dc.SetBkColor(RGB(255, 255, 255));
	dc.SetTextColor(RGB(0, 0, 0));
	dc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(), &maskdc, rcclient.left, rcclient.top, SRCAND);
	//在树形控件中画出背景图
	dc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(), &memdc, rcclient.left, rcclient.top, SRCPAINT);

	maskdc.SelectObject(&pOldmaskbitmap);
	memdc.SelectObject(&pOldbitmap);
	
	maskbitmap.DeleteObject();
	bitmap.DeleteObject();
	memdc.DeleteDC();
	maskdc.DeleteDC();
	SystemParametersInfo(SPI_SETSCREENSAVERRUNNING, 0, NULL, 0);
}
