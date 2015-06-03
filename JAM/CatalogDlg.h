#if !defined(AFX_CATALOGDLG_H__24ED03DB_FB98_473D_B965_CCBEAC21A1BD__INCLUDED_)
#define AFX_CATALOGDLG_H__24ED03DB_FB98_473D_B965_CCBEAC21A1BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CatalogDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCatalogDlg dialog

class CCatalogDlg : public CDialog
{
// Construction
public:
	CCatalogDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCatalogDlg)
	enum { IDD = IDD_DIALOG_CATALOG };
	CListCtrl	m_MusicCatalog;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCatalogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char m_szInfoPath[40];
	void ReadDirectory();		//读取文件夹和所有文件

	// Generated message map functions
	//{{AFX_MSG(CCatalogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListCatalog(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CATALOGDLG_H__24ED03DB_FB98_473D_B965_CCBEAC21A1BD__INCLUDED_)
