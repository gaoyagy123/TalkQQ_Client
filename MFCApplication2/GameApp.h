#pragma once
#define WM_SHOWTASK     WM_USER + 2
#define UM_SOCK     WM_USER + 1
#include "MyButton.h"
#include "MyEdit.h"
#include "MyTreeCtrl.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "MFCApplication2Dlg.h"
#include "talktotalk.h"
#include <vector>
#include "Mswsock.h"
#include "MsgDiaglog.h"
#include "Psapi.h"
typedef struct SystemSpeaker {
	CString obj[1000][6];
	LONG num;
} SystemSpeaker;

class GameApp : public CDialogEx
{
	DECLARE_DYNAMIC(GameApp)

public:
	GameApp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~GameApp();
	void SetFontSize(UINT IDC, int Size);
	HTREEITEM AddItem(HTREEITEM hRoot, CString TXT, UINT ImageList, int No);
	HTREEITEM AddItemSearch(HTREEITEM hRoot, CString TXT, UINT ImageList, int No);
	void CreateImageList();
	void Wstartup();
	void WCleanup(LONG S);
	int Connect(HWND Hw);
	int SendMsg(CString head, CString User, CString MSG);
	void GetUserInfo();
	void InitUser(CString Msg);
	void AddFriend();
	void CreateImageHead();
	void SetHeadList();
	void SetControlEnabled(BOOL A);
	void Shinrk(int shinrkIcon);
	void SendPic(CString Header, ObjSend obj, CString Info);
	byte* Recibir(LONG S, long *Rev);
	void CheckNewFolder(CString strpath);
	long RevPic(byte *buff, long Rec);
	CString GetType(byte *buff);
	int SearchFriend(CString ComeUser);
	int NewRevFile(byte* buff);
	void myTransmitFile(SOCKET hSocket, HANDLE hFile, LPTRANSMIT_FILE_BUFFERS lpTransmitBuffers);
	int GetShinkId();
	int GetMsgHead(byte *buff);
	int CheckHead(msgHead Head);
	CString GetMsg(byte *buff, int Rec);
	void ShowSearchUser(CString Msg);
	void ShowFindUser(CString str);
	void ShowHideFind(bool s);
	void SearchmyFriend(CString Msg);
	void GetAdFriend(CString Msg);
	void ReciveFriend(CString Msg);
	bool ShowMsg();
	void ClearFriend();
	void SysSpeaker(CString Msg);
	CWnd* FindControlWnd(CWnd* ParentWnd, CString Title, int id);
	void GetMessageSock();
	static unsigned int __stdcall ServerThread(void* pvParam);


	enum { IDD = IDD_DIALOG1 };
	sockaddr_in Sock;
	CString ReMsg;
	NOTIFYICONDATA m_nid;
	CMyButton M_Button1;
	CMyButton G_Button3;
	CMyButton G_Button4;
	CMyButton TButton1;
	CMyButton TButton2;
	CMyButton TButton3;
	CMyTreeCtrl tlist1;
	HANDLE m_hThread;
	CStatic headicon;
	CStatic NickName;
	CStatic Gold;
	CMyEdit findedit;
	int myheadid;
	bool m_bIsIcon;
	CMFCApplication2App* App = (CMFCApplication2App *)AfxGetApp();
	CString MyNick;
	bool RevObj[100];
	int RevPicId;
	CFont myFont;
	CStatic numid;
	CTreeCtrl flist;
	SystemSpeaker System;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	

	LRESULT OnSock(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnStnClickedHeadbitmap();
	CTreeCtrl headlist;
	afx_msg void OnKillfocusTree3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSelchangedTree3(NMHDR *pNMHDR, LRESULT *pResult);
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);

	afx_msg void OnTvnSelchangingTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSetfocusEdit1();
	afx_msg void OnNMDblclkTree2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRclickTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void On1();
	afx_msg void OnBnClickedButton2();
};
