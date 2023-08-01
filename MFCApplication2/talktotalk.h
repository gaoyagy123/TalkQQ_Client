#pragma once
#include "MyButton.h"
#include "MFCApplication2.h"
#include "afxwin.h"
#include "GameApp.h"
#include "RichEdit.h"
#include "afxcmn.h"
#include "afxole.h"
#include "richole.h"
#include "CutPic.h"

class talktotalk : public CDialogEx
{
	DECLARE_DYNAMIC(talktotalk)

public:
	talktotalk(CWnd* pParent = NULL); 
	virtual ~talktotalk();
	void SetFontSize(CWnd *item, int Size);
	void InitUser();
	CString SetStr(CString Name, CString tmp);
	void SetTalkFormat(CString Str);
	void SendTalk();
	void InserPic(CString Str, CString Bq, CRichEdit TextBox);
	virtual BOOL OnInitDialog();
	void CreateImageList();
	void SetFaceList();
	void SendTalkPic(ObjSend obj, CString Info);

	enum { IDD = IDD_TALKTOTALK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö

	DECLARE_MESSAGE_MAP()
public:
	IOleObject* m_pPicObj;
	CMyButton mbutton1;
	CMyButton mbutton2;
	CMyButton mbutton3;
	CMyButton mbutton4;
	CStatic talkhead;
	CStatic tname;
	CFont font;
	CRichEdit text1;
	CRichEdit text2;
	CMyButton facebq;
	CImageList facelist;
	CListCtrl mfacelist;
	int TalkId;
	CString MyNick;
	CMyButton mMax;
	CMyButton mcutpic;
	CMyButton mgetpic;
	CStatic numid;
	bool m_bMaxSize;

	CMFCApplication2App* App = (CMFCApplication2App *)AfxGetApp();
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnChangeRichedit25();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeRichedit24();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSetfocusRichedit25();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLvnHotTrackList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton11();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};
