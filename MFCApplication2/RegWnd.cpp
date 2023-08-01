// RegWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "RegWnd.h"
#include "afxdialogex.h"

CString Aname, Apasswd;
int RS;
// RegWnd �Ի���

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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	//if (m_gif.Load(MAKEINTRESOURCE(IDR_GIF1), _T("GIF")))
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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


// RegWnd ��Ϣ�������



void RegWnd::OnBnClickedButton4()
{
	RegWnd::OnCancel();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
			ReMsg = "��½�ɹ�";
		}
		else if (Msg == "LoginFaild-2")
		{
			ReMsg = "�������";
		}
		else if (Msg == "LoginFaild-1")
		{
			ReMsg = "�û�������";
		}
		else if (Msg == "RegFaild")
		{
			ReMsg = "ע��ʧ��";
		}
		else if (Msg == "RegSucess")
		{
			ReMsg = "ע��ɹ�";
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
		AfxMessageBox((CString)"��δ��д��Ϣ��");
		return;
	}
	if (Passwd.Trim() != RePasswd.Trim())
	{
		AfxMessageBox((CString)"����ȷ�ϲ���ȷ��");
		return;
	}
	if (Uname.Trim().GetLength() < 4 || Passwd.Trim().GetLength() < 4
		|| RePasswd.Trim().GetLength() < 4 || Nick.Trim().GetLength() < 4
		|| Tname.Trim().GetLength() < 4)
	{
		AfxMessageBox((CString)"��Ϣ����4-16λ��");
		return;
	}
	if (Uname.Trim().GetLength() > 16 || Passwd.Trim().GetLength()> 16
		|| RePasswd.Trim().GetLength() > 16 || Nick.Trim().GetLength() > 16
		|| Tname.Trim().GetLength() > 16)
	{
		AfxMessageBox((CString)"��Ϣ����4-16λ��");
		return;
	}
	if (Tid.Trim().GetLength() != 18)
	{
		AfxMessageBox((CString)"���֤��Ϣ����ȷ��");
		return;
	}
	if (CheckNum(Tid) == FALSE)
	{
		AfxMessageBox((CString)"���֤��Ϣ����ȷ��");
		return;
	}
	MSG = Uname + "|" + Passwd + "|" + Nick + "|" + Tname + "|" + Tid;
	CMFCApplication2Dlg Dlg;
	Aname = Uname;
	Apasswd = Passwd;
	RS = Dlg.SendLogin(MSG, this->m_hWnd);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	return;
}


BOOL RegWnd::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
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
