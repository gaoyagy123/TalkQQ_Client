#pragma once
#include "MFCApplication2Dlg.h"
// RegWnd �Ի���

class RegWnd : public CDialogEx
{
	DECLARE_DYNAMIC(RegWnd)

public:
	RegWnd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RegWnd();
	BOOL CheckNum(CString str);
// �Ի�������
	enum { IDD = IDD_REGWND };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4();
	afx_msg LRESULT OnSock(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton5();
//	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
