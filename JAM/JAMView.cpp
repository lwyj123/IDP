// JAMView.cpp : implementation of the CJAMView class
//

#include "stdafx.h"
#include "JAM.h"
#include "JAMDoc.h"
#include "JAMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJAMView

IMPLEMENT_DYNCREATE(CJAMView, CView)

BEGIN_MESSAGE_MAP(CJAMView, CView)
	//{{AFX_MSG_MAP(CJAMView)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJAMView construction/destruction

CJAMView::CJAMView()
{
	// TODO: add construction code here

}

CJAMView::~CJAMView()
{
}

BOOL CJAMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CJAMView drawing

void CJAMView::OnDraw(CDC* pDC)
{
	CJAMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDoc->CJam.ShowBG(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CJAMView diagnostics

#ifdef _DEBUG
void CJAMView::AssertValid() const
{
	CView::AssertValid();
}

void CJAMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJAMDoc* CJAMView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJAMDoc)));
	return (CJAMDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJAMView message handlers

void CJAMView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CJAMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->CJam.MoveNote();
	Invalidate(FALSE);
	CView::OnTimer(nIDEvent);
}

int CJAMView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CJAMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->CJam.InitializationDC();
	SetTimer(1, 50, NULL);
	return 0;
}

void CJAMView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CJAMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->CJam.GameKeyDown(nChar);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CJAMView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CJAMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->CJam.GameKeyUp(nChar);
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CJAMView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (point.x < 800 && point.x > 750 && point.y > 555 && point.y< 565)
	{
		PostQuitMessage(0);			//ÍË³ö³ÌÐò
	}
	CView::OnLButtonDown(nFlags, point);
}
