#pragma once

// CMyEdit

class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:
	CMyEdit();
	virtual ~CMyEdit();
	void SetBkColor(COLORREF color);
	void SetTextColor(COLORREF color);
	void SetR(bool s);
	void Settm(int s);

	COLORREF m_bkColor;
	COLORREF m_textColor;
	bool m_r;
	int m_tm;
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
};


