#pragma once


// CMyTreeCtrl ��ͼ

class CMyTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNCREATE(CMyTreeCtrl)

public:
	CMyTreeCtrl();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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

