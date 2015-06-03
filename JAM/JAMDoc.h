// JAMDoc.h : interface of the CJAMDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JAMDOC_H__A0BF66BD_F46D_411A_8F64_DA118F45CD79__INCLUDED_)
#define AFX_JAMDOC_H__A0BF66BD_F46D_411A_8F64_DA118F45CD79__INCLUDED_

#include "Game.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CJAMDoc : public CDocument
{
protected: // create from serialization only
	CJAMDoc();
	DECLARE_DYNCREATE(CJAMDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJAMDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CGame CJam;
	virtual ~CJAMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	
// Generated message map functions
protected:
	//{{AFX_MSG(CJAMDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JAMDOC_H__A0BF66BD_F46D_411A_8F64_DA118F45CD79__INCLUDED_)
