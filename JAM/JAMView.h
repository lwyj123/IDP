// JAMView.h : interface of the CJAMView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JAMVIEW_H__0F115209_A919_4D55_A2D9_1D9F7D48375E__INCLUDED_)
#define AFX_JAMVIEW_H__0F115209_A919_4D55_A2D9_1D9F7D48375E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CJAMView : public CView
{
protected: // create from serialization only
	CJAMView();
	DECLARE_DYNCREATE(CJAMView)

// Attributes
public:
	CJAMDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJAMView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJAMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJAMView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in JAMView.cpp
inline CJAMDoc* CJAMView::GetDocument()
   { return (CJAMDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JAMVIEW_H__0F115209_A919_4D55_A2D9_1D9F7D48375E__INCLUDED_)
