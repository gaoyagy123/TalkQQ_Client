// MsgDiaglog.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MsgDiaglog.h"
#include "afxdialogex.h"


// MsgDiaglog 对话框

IMPLEMENT_DYNAMIC(MsgDiaglog, CDialogEx)

MsgDiaglog::MsgDiaglog(CWnd* pParent /*=NULL*/)
	: CDialogEx(MsgDiaglog::IDD, pParent)
{

}

MsgDiaglog::~MsgDiaglog()
{
}

void MsgDiaglog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICTHEAD, talkhead);
	DDX_Control(pDX, IDC_STATICNICK, tname);
	DDX_Control(pDX, IDC_STATICNICK3, exmsg);
	DDX_Control(pDX, IDC_EDIT1, msg);
	DDX_Control(pDX, IDC_BUTTON3, mbutton1);
	DDX_Control(pDX, IDOK, mbutton2);
	DDX_Control(pDX, IDCANCEL, mbutton3);
}


BEGIN_MESSAGE_MAP(MsgDiaglog, CDialogEx)
	ON_BN_CLICKED(IDOK, &MsgDiaglog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MsgDiaglog::OnBnClickedCancel)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON3, &MsgDiaglog::OnBnClickedButton3)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// MsgDiaglog 消息处理程序


BOOL MsgDiaglog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HBITMAP hBitmap = ::LoadBitmap(AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP2));
	SetBackgroundImage(hBitmap);

	mbutton1.Settm(0);
	mbutton2.SetBkColor(RGB(220, 220, 220));
	mbutton3.SetBkColor(RGB(220, 220, 220));
	mbutton1.SetTextColor(RGB(220, 220, 220));
	mbutton2.Settm(200);
	mbutton3.Settm(200);
	this->ShowWindow(5);
	return TRUE; 
}
void MsgDiaglog::InitUser()
{
	CString str;
	talkhead.ModifyStyle(0xF, SS_ICON | SS_CENTERIMAGE);
	talkhead.SetIcon(App->imagelisthead.ExtractIconA(IconId));
	tname.SetWindowTextA(MyNick);
	font.CreatePointFont(100, "MS Shell Dlg");
	tname.SetFont(&font);
	if (Type == 1)
	{
		mbutton2.SetWindowTextA("接受邀请");
		mbutton3.SetWindowTextA("拒绝邀请");
	}
	else if (Type == 0)
	{
		mbutton2.SetWindowTextA("邀请好友");
	}
}

void MsgDiaglog::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str;
	GameApp dlg;
	if (Type == 0)
	{
		CString istr;
		msg.GetWindowTextA(istr);
		str.Format("%d|%s", TalkId, istr);
		dlg.SendMsg("AdF", App->MyName, str);
	}
	else if (Type == 1)
	{
		str.Format("%d|1", TalkId);
		dlg.SendMsg("AdR", App->MyName, str);
	}
	font.DeleteObject();
	this->DestroyWindow();
	delete this;
}

void MsgDiaglog::OnBnClickedCancel()
{
	if (Type == 1)
	{
		CString str;
		GameApp dlg;
		str.Format("%d|0", TalkId);
		dlg.SendMsg("AdR", App->MyName, str);
	}
	font.DeleteObject();
	this->DestroyWindow();
	delete this;
}


HBRUSH MsgDiaglog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void MsgDiaglog::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRgn m_rgn;
	CRect rc;
	GetWindowRect(&rc); //获得窗口矩形
	rc -= rc.TopLeft();
	m_rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 8, 8); //根据窗口矩形创建一个圆角矩形
	SetWindowRgn(m_rgn, TRUE);
	DeleteObject(m_rgn);
}


void MsgDiaglog::OnBnClickedButton3()
{
	font.DeleteObject();
	this->DestroyWindow();
	delete this;
	// TODO:  在此添加控件通知处理程序代码
}


void MsgDiaglog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}
