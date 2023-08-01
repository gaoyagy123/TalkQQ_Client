// MyTreeCtrl.cpp : ʵ���ļ�
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


// CMyTreeCtrl ���

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


// CMyTreeCtrl ��Ϣ�������

	// MyTreeCtrl.cpp

void CMyTreeCtrl::OnPaint()
{
	CPaintDC dc(this); //������ʾ�豸DC
		
	CRect rcclient; // rcclient ���ڴ�����οؼ��Ĵ�С
	GetClientRect(&rcclient); //�õ����οؼ������С
	//���ڴ��д��������豸������

	CDC memdc; //�����ڴ��豸DC
	memdc.CreateCompatibleDC(&dc); //��������ʾ�豸����DC
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, rcclient.Width(), rcclient.Height());
	//���ú���CreateCompatibleBitmap ����λͼ
	
	CBitmap *pOldbitmap = memdc.SelectObject(&bitmap); //λͼ���ѡ�����DC
	//���ڴ�CDC �����϶�TreeView Ĭ�ϻ�ͼ��


	CWnd::DefWindowProc(WM_PAINT, (WPARAM)memdc.m_hDC, 0);

	CDC maskdc;
	maskdc.CreateCompatibleDC(&dc);
	CBitmap maskbitmap;
	maskbitmap.CreateBitmap(rcclient.Width(), rcclient.Height(), 1, 1, NULL); //������ɫλͼ
	CBitmap *pOldmaskbitmap = maskdc.SelectObject(&maskbitmap);
	maskdc.BitBlt(0, 0, rcclient.Width(), rcclient.Height(), &memdc, rcclient.left, rcclient.top, SRCCOPY);

	CPoint pt(0, 0);
	MapWindowPoints(GetParent(), &pt, 1);
	CImage	A;
	A.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP2);

	A.BitBlt(dc, rcclient, pt, SRCCOPY);
	//TransparentBlt(dc.m_hDC, 0, 0, rcclient.Width(), rcclient.Height(), memdc.m_hDC, 0, 0, rcclient.Width(), rcclient.Height(), RGB(0xff, 0xff, 0xff));
	
	//dc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(), &maskdc, pt.x, pt.y, SRCCOPY);

	//λͼ��Ĭ�ϱ���������������ϳɱ���ͼ
	memdc.SetBkColor(RGB(0, 0, 0));
	memdc.SetTextColor(RGB(255, 255, 255));
	memdc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(),
		&maskdc, rcclient.left, rcclient.top, SRCAND);

	dc.SetBkColor(RGB(255, 255, 255));
	dc.SetTextColor(RGB(0, 0, 0));
	dc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(), &maskdc, rcclient.left, rcclient.top, SRCAND);
	//�����οؼ��л�������ͼ
	dc.BitBlt(rcclient.left, rcclient.top, rcclient.Width(), rcclient.Height(), &memdc, rcclient.left, rcclient.top, SRCPAINT);

	maskdc.SelectObject(&pOldmaskbitmap);
	memdc.SelectObject(&pOldbitmap);
	
	maskbitmap.DeleteObject();
	bitmap.DeleteObject();
	memdc.DeleteDC();
	maskdc.DeleteDC();
	SystemParametersInfo(SPI_SETSCREENSAVERRUNNING, 0, NULL, 0);
}
