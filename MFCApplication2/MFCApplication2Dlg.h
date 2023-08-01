
// MFCApplication2Dlg.h : ͷ�ļ�
//

#pragma once
#include "MyEdit.h"
#include <vector>
#include "GameApp.h"
#include "RegWnd.h"
#include "PictureEx.h"
#include "afxwin.h"
#include "MyButton.h"
#include "MFCApplication2.h"
#define UM_SOCK     WM_USER + 1
#pragma warning (disable: 4996)
// CMFCApplication2Dlg �Ի���
class CMFCApplication2Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	void Wstartup();
	void WCleanup(LONG S);
	CString GetTime();
	CString Recibirs(LONG S);
	std::vector<CString> Split(CString strLine,CString Plit);
	int Instr(CString str1,CString str2);
	int CMon(CString A);
	int SendLogin(CString MSG, HWND Hw);
	int SetIni(CString KeyValue, CString KeyName, CString  KeyGroup, CString PathName);
	CString GetIni(CString KeyName, CString KeyGroup, CString PathName);
	void SetiniSet(CString Name, CString Value);
	CString ReadIniSet(CString Name);
	void ReadIni();
	int CalcCount(CString strPathName);
	int CalcCountVs(CString Tname, CString strPathName);
	char* CStringToChar(CString Tmp);
	CString Recibir(LONG S);

// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧

	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnSock(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();
	CPictureEx m_pic;
	CStatic m_ctrlPicture;
	CMyButton m_Button1;
	CMyButton m_Button2;
	CMyButton m_Button3;
	CMyButton m_Button4;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStnClickedStatic1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetfocusEdit1();
	afx_msg void OnSetfocusButton2();
	sockaddr_in Sock;
	SOCKET S;
	CMyEdit useredit;
	CMyEdit pswdedit;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

