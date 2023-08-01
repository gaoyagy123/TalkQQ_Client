#pragma once


// CMyTreeCtrl 视图

class CMyTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNCREATE(CMyTreeCtrl)

public:
	CMyTreeCtrl();           // 动态创建所使用的受保护的构造函数
	virtual ~CMyTreeCtrl();

public:

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg void OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

