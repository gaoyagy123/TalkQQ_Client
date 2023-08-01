// talktotalk.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "talktotalk.h"
#include "afxdialogex.h"


// talktotalk 对话框

IMPLEMENT_DYNAMIC(talktotalk, CDialogEx)

talktotalk::talktotalk(CWnd* pParent /*=NULL*/)
	: CDialogEx(talktotalk::IDD, pParent)
{

}

talktotalk::~talktotalk()
{
}

void talktotalk::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON8, mbutton1);
	DDX_Control(pDX, IDC_BUTTON1, mbutton2);
	DDX_Control(pDX, IDC_BUTTON4, mbutton3);
	DDX_Control(pDX, IDC_BUTTON3, mbutton4);
	DDX_Control(pDX, IDC_STATICTHEAD, talkhead);
	DDX_Control(pDX, IDC_STATICNICK, tname);
	DDX_Control(pDX, IDC_RICHEDIT24, text1);
	DDX_Control(pDX, IDC_RICHEDIT25, text2);
	DDX_Control(pDX, IDC_BUTTON2, facebq);
	DDX_Control(pDX, IDC_LIST1, mfacelist);
	DDX_Control(pDX, IDC_BUTTON9, mcutpic);
	DDX_Control(pDX, IDC_BUTTON10, mgetpic);
	DDX_Control(pDX, IDC_STATICNICK2, numid);
	DDX_Control(pDX, IDC_BUTTON11, mMax);
}


BEGIN_MESSAGE_MAP(talktotalk, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON3, &talktotalk::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &talktotalk::OnBnClickedButton4)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON8, &talktotalk::OnBnClickedButton8)
	ON_WM_CTLCOLOR()
	ON_EN_CHANGE(IDC_RICHEDIT25, &talktotalk::OnChangeRichedit25)
	ON_BN_CLICKED(IDC_BUTTON1, &talktotalk::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_RICHEDIT24, &talktotalk::OnEnChangeRichedit24)
	ON_EN_SETFOCUS(IDC_RICHEDIT25, &talktotalk::OnSetfocusRichedit25)
	ON_BN_CLICKED(IDC_BUTTON2, &talktotalk::OnBnClickedButton2)
	ON_NOTIFY(LVN_HOTTRACK, IDC_LIST1, &talktotalk::OnLvnHotTrackList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &talktotalk::OnNMClickList1)
	ON_NOTIFY(NM_KILLFOCUS, IDC_LIST1, &talktotalk::OnKillfocusList1)
	ON_BN_CLICKED(IDC_BUTTON9, &talktotalk::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &talktotalk::OnBnClickedButton10)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON11, &talktotalk::OnBnClickedButton11)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// talktotalk 消息处理程序


BOOL talktotalk::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	HBITMAP hBitmap = ::LoadBitmap(AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP2));
	SetBackgroundImage(hBitmap);

	facebq.SetmStye(IDB_BITMAP4);
	facebq.Settm(0);
	mcutpic.SetmStye(IDB_BITMAP5);
	mcutpic.Settm(0);
	mgetpic.SetmStye(IDB_BITMAP6);
	mgetpic.Settm(0);

	mbutton1.Settm(200);
	mbutton2.Settm(200);
	mbutton3.Settm(0);
	mbutton4.Settm(0);
	mMax.Settm(0);
	mbutton1.SetBkColor(RGB(220, 220, 220));
	mbutton2.SetBkColor(RGB(220, 220, 220));
	mbutton3.SetTextColor(RGB(220, 220, 220));
	mbutton4.SetTextColor(RGB(220, 220, 220));
	mMax.SetTextColor(RGB(220, 220, 220));
	SetFontSize(&mbutton4, 22);
	SetFontSize(&mbutton3, 22);

	text2.SetEventMask(text2.GetEventMask() | ENM_CHANGE );
	text1.SetEventMask(text2.GetEventMask() | ENM_CHANGE );
	text1.SetEndSel(true);

	CreateImageList();
	SetForegroundWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void talktotalk::InitUser()
{
	CString str;
	talkhead.ModifyStyle(0xF, SS_ICON | SS_CENTERIMAGE);
	int index, imageindex = 0;
	index = TalkId;
	imageindex = atoi(App->Friend[index][3]);
	talkhead.SetIcon(App->imagelisthead.ExtractIconA(imageindex));
	tname.SetWindowTextA(App->Friend[index][1]);
	int k = atoi(App->Friend[index][2]);
	str.Format("ID:%.8d", k);
	numid.SetWindowTextA(str);
	SetWindowTextA(App->Friend[index][1]);
	font.CreatePointFont(200, "MS Shell Dlg"); 
	tname.SetFont(&font);
}
void talktotalk::SetFontSize(CWnd *item, int Size)
{
	CFont * f;
	f = new CFont;
	f->CreateFont(Size,            // nHeight 
		Size,           // nWidth 
		0,           // nEscapement 
		0,           // nOrientation 
		FW_BOLD,     // nWeight 
		TRUE,        // bItalic 
		FALSE,       // bUnderline 
		0,           // cStrikeOut 
		ANSI_CHARSET,              // nCharSet 
		OUT_DEFAULT_PRECIS,        // nOutPrecision 
		CLIP_DEFAULT_PRECIS,       // nClipPrecision 
		DEFAULT_QUALITY,           // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("新宋体"));              // lpszFac

	item->SetFont(f);
	delete f;
}

void talktotalk::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}



void talktotalk::OnBnClickedButton3()
{	
	this->DestroyWindow();
	font.DeleteObject();
	delete this;
	// TODO:  在此添加控件通知处理程序代码
}


void talktotalk::OnBnClickedButton4()
{
	WINDOWPLACEMENT lwndpl;
	WINDOWPLACEMENT * lpwndpl;
	lpwndpl = &lwndpl;
	GetWindowPlacement(lpwndpl);
	lpwndpl->showCmd = SW_SHOWMINIMIZED;
	SetWindowPlacement(lpwndpl);
	// TODO:  在此添加控件通知处理程序代码
}


void talktotalk::OnBnClickedButton8()
{
	this->DestroyWindow();
	font.DeleteObject();
	delete this;
	// TODO:  在此添加控件通知处理程序代码
}


HBRUSH talktotalk::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC)
	{

		pDC->SetTextColor(RGB(0xE0, 0xE0, 0xE0));
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void talktotalk::OnChangeRichedit25()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	text2.InvalidateRect(NULL);
	
	text2.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	CString str;
	text2.GetWindowTextA(str);
	TRACE(str+"\n");
	text2.InserPic(str, 0);
}



void talktotalk::OnBnClickedButton1()
{
	SendTalk();
	// TODO:  在此添加控件通知处理程序代码
}

void talktotalk::SendTalk()
{
	CString str, target, selfstr;
	int index = TalkId;
	text2.GetWindowTextA(str);
	int obj = text2.GetPicInfo();
	str = text2.RecoverObj(str);
	if (str.IsEmpty() && obj == 0) return;
	if (str.GetLength() > MAX_SENDMSG_LENGTH)
	{
		AfxMessageBox("发送信息长度超出范围！\n");
		return;
	}
	target = App->Friend[index][0];
	selfstr = str;
	if (obj > 0) selfstr = selfstr + "/Slf";
	selfstr = SetStr(MyNick, selfstr);
	SetTalkFormat(selfstr);
	text2.SetWindowText("");
	if (obj > 0)
	{
		SendTalkPic(text1.objectSend, str);
		text1.objectSend.num = 0;
	}
	else
	{
		GameApp dlg;
		dlg.SendMsg("Tak", target, str);
	}
}
void talktotalk::OnEnChangeRichedit24()
{
	text1.InvalidateRect(NULL);
	text1.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
	CString str;
	text1.GetWindowTextA(str);
	int Headlen = text1.FindWcharL(str, "\t", text1.MaxLen) + 1;
	text1.InserPic(str, Headlen);
	text1.GetWindowTextA(str);
	LONG B = str.GetLength();
	text1.SetSel(B, B);
	text1.MaxLen = text1.GetWcharLen(str);
}

void talktotalk::SetTalkFormat(CString Str)
{
	LONG B;
	CString tstr;
	text1.GetWindowTextA(tstr);
	B = tstr.GetLength();
	text1.SetSel(B, B);
	text1.ReplaceSel(Str);
}
CString talktotalk::SetStr(CString Name, CString tmp)
{
	CString str;
	str = Name + ":\n" + "	";
	str = str+ tmp + "\n\n";
	return str;
}



BOOL talktotalk::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
			{
				text2.SetSel(-1, -1);
				text2.ReplaceSel(_T("\n"));
				//text2.SetFocus();
			}
			else
			{
				SendTalk();
				return TRUE;
			}
		case VK_ESCAPE:
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void talktotalk::OnSetfocusRichedit25()
{
	//tmpedit.SetFocus();
	// TODO:  在此添加控件通知处理程序代码
}

void talktotalk::OnBnClickedButton2()
{
	if (!mfacelist.IsWindowVisible())
	{
		RECT ac;
		CRect rc;
		GetWindowRect(&ac);
		CPoint pt(0, 0);
		facebq.MapWindowPoints(this, &pt, 1);
		mfacelist.GetWindowRect(&rc);
		int w = 28 * 15 - 10, h = 27 * 6;
		mfacelist.MoveWindow(pt.x, pt.y - h , w, h);
		mfacelist.SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE);
		mfacelist.ShowWindow(5);
		mfacelist.SetFocus();
		mfacelist.ModifyStyleEx(0, WS_EX_COMPOSITED, 0);
	}
	else
	{
		mfacelist.ShowWindow(0);
	}
}

void talktotalk::SetFaceList()
{
	int k = 0;
	LV_ITEM item = { 0 };
	for (int j = 0; j <= 14; j++)
	{
		mfacelist.InsertColumn(j, _T(""), LVCFMT_CENTER, 27, j);
	}
	for (int i = 0; i <= 5; i++)
	{
		mfacelist.InsertItem(i,"");
		for (int j = 0; j <= 14; j++)
		{
			item.mask = LVIF_IMAGE;
			item.iItem = i;
			item.iSubItem = j;
			item.iImage = k;
			k++;
			mfacelist.SetItem(&item);
		}
	}
}
void talktotalk::CreateImageList()
{
	facelist.Create(25, 25, ILC_COLOR32 | ILC_MASK, 2, 2);
	for (int i = 282; i <= 369; i++)
	{
		facelist.Add(AfxGetApp()->LoadIconA(i));
	}

	mfacelist.SetImageList(&facelist, LVSIL_SMALL);
	mfacelist.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES | LVS_EX_TRACKSELECT );

	SetFaceList();

}


void talktotalk::OnLvnHotTrackList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if (pNMLV->iItem != -1 || pNMLV->iSubItem != -1)
	{
		CString strtemp;
		int h = pNMLV->ptAction.y;
		h = h / 27;
		strtemp.Format(_T("%d"), h * 15 + pNMLV->iSubItem);
		if (strtemp.GetLength() != 2)
			strtemp = "/i0" + strtemp;
		else
			strtemp = "/i" + strtemp;
		//AfxMessageBox(strtemp);
		int index = h * 15 + pNMLV->iSubItem;
		//CDC* dc = mfacelist.GetDC();
		//	CRect rect;
		//mfacelist.GetClientRect(rect);

		//dc->Draw3dRect(rect, RGB(255, 0, 0), RGB(0, 255, 0));
	}
	*pResult = 0;
}


void talktotalk::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMItemActivate->iItem != -1 || pNMItemActivate->iSubItem != -1)
	{
		CString strtemp;
		int h = pNMItemActivate->ptAction.y;
		h = h / 27;
		strtemp.Format(_T("%d"), h * 15 + pNMListView->iSubItem);
		if (strtemp.GetLength() != 2)
			strtemp = "/i0" + strtemp;
		else
			strtemp = "/i" + strtemp;
		//AfxMessageBox(strtemp);
		int index = h * 15 + pNMListView->iSubItem;
		text2.ReplaceSel(strtemp);
		mfacelist.ShowWindow(0);
	}
	*pResult = 0;
}


void talktotalk::OnKillfocusList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	mfacelist.ShowWindow(0);
	*pResult = 0;
}


void talktotalk::OnBnClickedButton9()
{
	CFileDialog fileDlg(true,
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST,
		_T("所有图片(*.bmp;*.gif;*.jpg)|*.bmp;*.gif;*.jpg||"));
	if (fileDlg.DoModal() == IDOK)
	{
		CString	FilePathName = fileDlg.GetPathName();
		//
		int i = text2.GetPicInfo();
		text1.objectSend.num = i + 1;
		text1.objectSend.obj[i].strpath = FilePathName;
		text1.objectSend.obj[i].Type = fileDlg.GetFileExt();
		long a, b;
		text2.GetSel(a, b);
		text1.objectSend.obj[i].Sel = a;
		text2.InserObjbyString(FilePathName, fileDlg.GetFileExt());
	}
}

void talktotalk::SendTalkPic(ObjSend obj, CString Info)
{
	CString target = App->Friend[TalkId][0];
	GameApp dlg;
	dlg.SendPic(target, obj, Info);
}


void talktotalk::OnBnClickedButton10()
{
	CutPic *dlg = new CutPic;
	dlg->Create(IDD_CUTPIC, this);
	dlg->ShowWindow(SW_SHOW);
	// TODO:  在此添加控件通知处理程序代码
}


void talktotalk::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRgn m_rgn;
	CRect rc;
	GetWindowRect(&rc); //获得窗口矩形
	rc -= rc.TopLeft();
	m_rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 8, 8); //根据窗口矩形创建一个圆角矩形
	SetWindowRgn(m_rgn, TRUE);
	DeleteObject(m_rgn);
	// TODO:  在此处添加消息处理程序代码
}


void talktotalk::OnBnClickedButton11()
{

	CRect tc, rc, t2, m1, m2, m3, m4, m5;
	CRect p1, p2, p3;
	GetWindowRect(&rc);
	text1.GetWindowRect(&tc);
	text2.GetWindowRect(&t2);
	mbutton1.GetWindowRect(&m1);
	mbutton2.GetWindowRect(&m2);
	mbutton3.GetWindowRect(&m3);
	mbutton4.GetWindowRect(&m4);
	mMax.GetWindowRect(&m5);
	facebq.GetWindowRect(&p1);
	mcutpic.GetWindowRect(&p2);
	mgetpic.GetWindowRect(&p3);
	ScreenToClient(&tc);
	ScreenToClient(&t2);
	ScreenToClient(&m1);
	ScreenToClient(&m2);
	ScreenToClient(&m3);
	ScreenToClient(&m4);
	ScreenToClient(&m5);
	ScreenToClient(&p1);
	ScreenToClient(&p2);
	ScreenToClient(&p3);
	int cx = rc.Width() - tc.right;
	int cy = rc.Height() - tc.bottom;
	int t2top = rc.Height() - t2.top;
	int mtop = rc.Height() - m1.top;
	int m1left = rc.Width() - m1.left;
	int m2left = rc.Width() - m2.left;
	int m3left = rc.Width() - m3.left;
	int m4left = rc.Width() - m4.left;
	int m5left = rc.Width() - m5.left;
	int p1top = rc.Height() - p1.top;
	int p2top = rc.Height() - p2.top;
	int p3top = rc.Height() - p3.top;

	ShowWindow(m_bMaxSize ? SW_RESTORE : SW_MAXIMIZE);
	if (m_bMaxSize)
	{
		ShowWindow(SW_RESTORE);
	}
	else
	{
		CRect rc;
		SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
		MoveWindow(&rc);
	}
	m_bMaxSize = !m_bMaxSize;

	GetWindowRect(&rc);
	text1.MoveWindow(tc.left, tc.top, rc.Width() - cx, rc.Height() - cy - tc.top);
	text2.MoveWindow(t2.left, rc.Height() - t2top, rc.Width() - cx, t2.Height());
	mbutton1.MoveWindow(rc.Width() - m1left, rc.Height() - mtop, m1.Width(), m1.Height());
	mbutton2.MoveWindow(rc.Width() - m2left, rc.Height() - mtop, m2.Width(), m2.Height());
	mbutton3.MoveWindow(rc.Width() - m3left, m3.top, m3.Width(), m3.Height());
	mbutton4.MoveWindow(rc.Width() - m4left, m4.top, m4.Width(), m4.Height());
	mMax.MoveWindow(rc.Width() - m5left, m5.top, m5.Width(), m5.Height());
	facebq.MoveWindow(p1.left, rc.Height() - p1top, p1.Width(), p1.Height());
	mcutpic.MoveWindow(p2.left, rc.Height() - p2top, p2.Width(), p2.Height());
	mgetpic.MoveWindow(p3.left, rc.Height() - p3top, p3.Width(), p3.Height());
}


void talktotalk::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	OnBnClickedButton11();
	CDialogEx::OnLButtonDblClk(nFlags, point);
}
