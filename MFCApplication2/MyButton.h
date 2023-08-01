#pragma once


// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();
public:
	void SetBkColor(COLORREF color);
	void SetTextColor(COLORREF color);
	void SetmStye(int s);
	void Settm(int s);
	void SetDown(bool s);
	void SetR(bool s);
private:
	bool m_bOver;
	bool m_bDown;
	bool m_bDisable;
	BOOL m_bTracking;
	int m_tm;
	int m_Stye;
	COLORREF m_bkColor;
	COLORREF m_textColor;
	bool m_r;
protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnable(BOOL bEnable);
private:
	void ButtonInit();
	void DrawButton();
	void DrawButton(HDC hDestDC);
public:
};


