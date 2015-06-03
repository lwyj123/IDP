// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "JAM.h"
#include "JAMDoc.h"
#include "CatalogDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_MUSIC_EXIT, OnMusicExit)
	ON_COMMAND(ID_MUSIC_OPEN, OnMusicOpen)
	ON_COMMAND(ID_MUSIC_START, OnMusicStart)
	ON_COMMAND(ID_SET_ADDSPEED, OnSetAddspeed)
	ON_COMMAND(ID_SET_SUBSPEED, OnSetSubspeed)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU			//设置窗体样式
				| WS_VISIBLE | WS_MINIMIZEBOX;
	cs.cx = 800;
	cs.cy = 648;
	cs.x = 100;
	cs.y = 50;
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnMusicExit() 
{
	// TODO: Add your command handler code here
	DestroyWindow();
}

void CMainFrame::OnMusicOpen() 
{
	// TODO: Add your command handler code here
	CJAMDoc* pDoc = (CJAMDoc*)GetActiveDocument();
	pDoc->CJam.GameKeyDown(VK_ESCAPE);
	CCatalogDlg aboutDlg;
	aboutDlg.DoModal();
}

void CMainFrame::OnMusicStart() 
{
	// TODO: Add your command handler code here
	CJAMDoc* pDoc = (CJAMDoc*)GetActiveDocument();
	pDoc->CJam.GameKeyDown(VK_ESCAPE);
	pDoc->CJam.GameStart();
}

void CMainFrame::OnSetAddspeed() 
{
	// TODO: Add your command handler code here
	CJAMDoc* pDoc = (CJAMDoc*)GetActiveDocument();
	pDoc->CJam.GameKeyDown(VK_ESCAPE);
	pDoc->CJam.SetUserSpeed(true);
}

void CMainFrame::OnSetSubspeed() 
{
	// TODO: Add your command handler code here
	CJAMDoc* pDoc = (CJAMDoc*)GetActiveDocument();
	pDoc->CJam.GameKeyDown(VK_ESCAPE);
	pDoc->CJam.SetUserSpeed(false);
}
