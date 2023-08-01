#pragma once
#include "GameApp.h"
#include "afxwin.h"
#include "MyButton.h"

// MsgDiaglog 对话框

class MsgDiaglog : public CDialogEx
{
	DECLARE_DYNAMIC(MsgDiaglog)

public:
	MsgDiaglog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MsgDiaglog();
	void InitUser();

// 对话框数据
	enum { IDD = IDD_MSG };
	CMFCApplication2App* App = (CMFCApplication2App *)AfxGetApp();
	int TalkId;
	CString MyNick;
	int IconId;
	CStatic talkhead;
	CStatic tname;
	CStatic exmsg;
	CEdit msg;
	CFont font;
	CMyButton mbutton1;
	CMyButton mbutton2;
	CMyButton mbutton3;
	int Type = 0;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

	afx_msg void OnBnClickedCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton3();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
