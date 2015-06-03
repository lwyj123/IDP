// JAMDoc.cpp : implementation of the CJAMDoc class
//

#include "stdafx.h"
#include "JAM.h"

#include "JAMDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJAMDoc

IMPLEMENT_DYNCREATE(CJAMDoc, CDocument)

BEGIN_MESSAGE_MAP(CJAMDoc, CDocument)
	//{{AFX_MSG_MAP(CJAMDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJAMDoc construction/destruction

CJAMDoc::CJAMDoc()
{
	// TODO: add one-time construction code here

}

CJAMDoc::~CJAMDoc()
{
}

BOOL CJAMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CJAMDoc serialization

void CJAMDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CJAMDoc diagnostics

#ifdef _DEBUG
void CJAMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJAMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJAMDoc commands
