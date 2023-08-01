#pragma once
#include "afxole.h"
#include "richole.h"

#import "ImageOle.dll" named_guids
#define FRM_TIMER_ID			2
#define MIN_FRM_DELAY				300
#define DIYFACE				1000
#define SELFFACE				1001
// CRichEdit
class CRichEdit : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CRichEdit)

public:
	CRichEdit();
	virtual ~CRichEdit();
	BOOL GetPic(REOBJECT FAR* pObject);
	void InserPic(int index);
	CString RecoverObj(CString Src);
	BOOL InserPic(CString Str, int headlen);
	int MyFind(CString Str, int iStart = 0, int *outindex = 0);
	int HasChineseChar(CString Cstr);
	int GetStrNum(CString Str, CString iStr, LONG Over);;
	int GetPicNum(CString str);
	bool CheckPic(CString str);
	int GetPicInfo();
	void InserGif(int index);
	int FindFirstObject(int cpMin, int nObjectCount);
	void SetEndSel(bool set);
	CString WcharLeft(CString str, int left);
	CString WcharMid(CString str, int mid);
	void InserObjbyString(CString strpat, CString Type, int Sel = -1);
	int GetWcharLen(CString Str);
	void InserDiyFace(int headlen, int k);
	void SelfDiyFace(int headlen, int k);
	int FindWcharL(CString Str, CString find, int start = 0);

public:
	CMFCApplication2App* App = (CMFCApplication2App *)AfxGetApp();
	IOleObject* m_pPicObj;
	int obj[1000][2];
	IRichEditOle* m_pRichEditOle;
	bool endsel;
	int MaxLen;
	ObjSend objectSend;
protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnEnChange();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


