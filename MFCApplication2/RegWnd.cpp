// RegWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "RegWnd.h"
#include "afxdialogex.h"

CString Aname, Apasswd;
int RS;
// RegWnd 对话框

IMPLEMENT_DYNAMIC(RegWnd, CDialogEx)

RegWnd::RegWnd(CWnd* pParent /*=NULL*/)
	: CDialogEx(RegWnd::IDD, pParent)
{

}

RegWnd::~RegWnd()
{
}
BOOL RegWnd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//if (m_gif.Load(MAKEINTRESOURCE(IDR_GIF1), _T("GIF")))
	// TODO:  在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void RegWnd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RegWnd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON4, &RegWnd::OnBnClickedButton4)
	ON_MESSAGE(UM_SOCK, OnSock)
	ON_BN_CLICKED(IDC_BUTTON5, &RegWnd::OnBnClickedButton5)
//	ON_WM_PAINT()
END_MESSAGE_MAP()


// RegWnd 消息处理程序



void RegWnd::OnBnClickedButton4()
{
	RegWnd::OnCancel();
	// TODO:  在此添加控件通知处理程序代码
}

BOOL RegWnd::CheckNum(CString str)
{
	bool bNumFlag = true;
	bool bFloatFlag = false;
	for (int i = 0; i<str.GetLength(); i++)
	{
		if (((int)str.GetAt(i) >= 48 && (int)str.GetAt(i) <= 57))continue;
		else if (str.GetAt(i) == '.')
		{
			if (bFloatFlag)
			{
				bNumFlag = false;
				break;
			}
			else
			{
				bFloatFlag = true;
				continue;
			}

		}
		else
		{
			bNumFlag = false;
			break;
		}
	}
	return bNumFlag;
}
LRESULT RegWnd::OnSock(WPARAM wParam, LPARAM lParam)
{
	CMFCApplication2Dlg Dlg;
	switch (LOWORD(lParam))
	{
	case FD_READ:
		CString Msg = Dlg.Recibir(RS);
		CString ReMsg;
		if (Msg == "LoginSucess")
		{
			ReMsg = "登陆成功";
		}
		else if (Msg == "LoginFaild-2")
		{
			ReMsg = "密码错误";
		}
		else if (Msg == "LoginFaild-1")
		{
			ReMsg = "用户名错误";
		}
		else if (Msg == "RegFaild")
		{
			ReMsg = "注册失败";
		}
		else if (Msg == "RegSucess")
		{
			ReMsg = "注册成功";
		}
		//
		AfxMessageBox(ReMsg);
		if (Msg == "RegSucess")
		{
			AfxGetMainWnd()->GetDlgItem(IDC_EDIT1)->SetWindowText(Aname);
			AfxGetMainWnd()->GetDlgItem(IDC_EDIT2)->SetWindowText(Apasswd);
			RegWnd::OnOK();

		}
	}
	return 1;
}

void RegWnd::OnBnClickedButton5()
{
	CString Uname, Passwd, RePasswd, Nick, Tname, Tid, MSG;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Uname);

	GetDlgItem(IDC_EDIT2)->GetWindowText(Passwd);
	GetDlgItem(IDC_EDIT3)->GetWindowText(RePasswd);

	GetDlgItem(IDC_EDIT4)->GetWindowText(Nick);
	GetDlgItem(IDC_EDIT5)->GetWindowText(Tname);

	GetDlgItem(IDC_EDIT6)->GetWindowText(Tid);
	if (Uname.Trim() == "" || Passwd.Trim() == "" || RePasswd.Trim() == ""
		|| Nick.Trim() == "" || Tname.Trim() == "" || Tid.Trim() == "")
	{
		AfxMessageBox((CString)"有未填写信息！");
		return;
	}
	if (Passwd.Trim() != RePasswd.Trim())
	{
		AfxMessageBox((CString)"密码确认不正确！");
		return;
	}
	if (Uname.Trim().GetLength() < 4 || Passwd.Trim().GetLength() < 4
		|| RePasswd.Trim().GetLength() < 4 || Nick.Trim().GetLength() < 4
		|| Tname.Trim().GetLength() < 4)
	{
		AfxMessageBox((CString)"信息长度4-16位！");
		return;
	}
	if (Uname.Trim().GetLength() > 16 || Passwd.Trim().GetLength()> 16
		|| RePasswd.Trim().GetLength() > 16 || Nick.Trim().GetLength() > 16
		|| Tname.Trim().GetLength() > 16)
	{
		AfxMessageBox((CString)"信息长度4-16位！");
		return;
	}
	if (Tid.Trim().GetLength() != 18)
	{
		AfxMessageBox((CString)"身份证信息不正确！");
		return;
	}
	if (CheckNum(Tid) == FALSE)
	{
		AfxMessageBox((CString)"身份证信息不正确！");
		return;
	}
	MSG = Uname + "|" + Passwd + "|" + Nick + "|" + Tname + "|" + Tid;
	CMFCApplication2Dlg Dlg;
	Aname = Uname;
	Apasswd = Passwd;
	RS = Dlg.SendLogin(MSG, this->m_hWnd);
	// TODO:  在此添加控件通知处理程序代码
	return;
}


BOOL RegWnd::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{

		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;
		case VK_ESCAPE:
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
