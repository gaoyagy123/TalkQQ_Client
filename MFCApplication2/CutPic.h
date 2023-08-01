#pragma once
#include "talktotalk.h"
#include "afxwin.h"

// CutPic �Ի���

class CutPic : public CDialogEx
{
	DECLARE_DYNAMIC(CutPic)

public:
	CutPic(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CutPic();
	HBITMAP SetTM();
	CString SaveBmp();
	BOOL SaveBitMapToFile(HBITMAP hBitmap, CString lpFileName);
	void DrawFdj();
	void GetPointWindow(CPoint point);
	bool IsCoveredByOtherWindow(HWND hWnd);

// �Ի�������
	enum { IDD = IDD_CUTPIC };
	CPoint StartPoint, EndPoint, FDJPoint, MovePoint;
	HBITMAP TBitMap;
	HBITMAP SrcBmp;
	bool cut, cutover, gethw;
	RECT rect;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL DestroyWindow();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CStatic mfdj;
};
