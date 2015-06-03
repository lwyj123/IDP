// CatalogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "jam.h"
#include "CatalogDlg.h"
#include "JAMDoc.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCatalogDlg dialog


CCatalogDlg::CCatalogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCatalogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCatalogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCatalogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCatalogDlg)
	DDX_Control(pDX, IDC_LIST_CATALOG, m_MusicCatalog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCatalogDlg, CDialog)
	//{{AFX_MSG_MAP(CCatalogDlg)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CATALOG, OnClickListCatalog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCatalogDlg message handlers

BOOL CCatalogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_szInfoPath[0] = 0;
	
	CFrameWnd* pWnd = (CFrameWnd*)::AfxGetMainWnd();
	CJAMDoc* pDoc = (CJAMDoc*)pWnd->GetActiveDocument();
	if (pDoc->CJam.m_IsGameStart)
	{
		pDoc->CJam.m_IsGameStart = false;
		//停止播放音乐
		::PlaySound(NULL,NULL,SND_PURGE);
	}
	ReadDirectory();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCatalogDlg::ReadDirectory()
{
	char szBuffer[80] = {0};
	struct _finddata_t fd;
	strcpy(szBuffer, "music\\");
	strcat(szBuffer, "*.jon");
	long iHandle = _findfirst(szBuffer, &fd);
	if (iHandle == -1)
		return;

	LV_COLUMN  lvColumn;
	char       szString[4][20] = {"文件路径","歌曲名称", "歌曲速度", "音符数"};
	//empty the list
	m_MusicCatalog.DeleteAllItems();
	//initialize the columns
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 140;

	for(int i = 0; i < 4; i++)
	{
	    lvColumn.pszText = szString[i];
		m_MusicCatalog.InsertColumn(i, &lvColumn);
	}
	int j = 0;
	do
	{
		if (!(fd.attrib & _A_SUBDIR)) // 文件夹
		{
			char szMusicFile[40] = {0};
			strcpy(szBuffer, "music\\");
			strcat(szBuffer, fd.name);
			strcpy(szMusicFile, szBuffer);
			
			char szMusicName[30] = {0};
			double MusicSpeed = 0;
			int NoteNum = 0;

			ifstream fin;
			fin.open(szMusicFile);
			fin >> szMusicName >> MusicSpeed
				>> NoteNum;
			fin.close();
			
			LVITEM root = {0};
			root.mask = LVIF_TEXT;
			root.iItem = j;

			root.iSubItem = 0;
			root.pszText = szMusicFile;		
			m_MusicCatalog.InsertItem(&root);

			root.iSubItem = 1;
			root.pszText = szMusicName;
			m_MusicCatalog.SetItem(&root);
			
			char Temp[10] = {0};
			sprintf(Temp,"%.2lf BPM",MusicSpeed);
			root.iSubItem = 2;
			root.pszText = Temp;
			m_MusicCatalog.SetItem(&root);

			sprintf(Temp,"%d",NoteNum);
			root.iSubItem = 3;
			root.pszText = Temp;
			m_MusicCatalog.SetItem(&root);
			
			j++;
		}
	} while (_findnext(iHandle, &fd) != - 1);

	_findclose(iHandle);
}

void CCatalogDlg::OnClickListCatalog(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nItem = m_MusicCatalog.GetSelectionMark();
	m_MusicCatalog.GetItemText(nItem, 0, m_szInfoPath, 40);
	*pResult = 0;
}

void CCatalogDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (m_szInfoPath[0] != 0)
	{
		CFrameWnd* pWnd = (CFrameWnd*)::AfxGetMainWnd();
		CJAMDoc* pDoc = (CJAMDoc*)pWnd->GetActiveDocument();
		pDoc->CJam.SetInfoMusicPath(m_szInfoPath);
		pDoc->CJam.ReadInfoMusicFile();
		pDoc->CJam.PrintBeatArea();
		pDoc->CJam.m_IsChoiceMenu = true;
		pDoc->CJam.m_IsMusic = true;	
	}
	else
	{
		::AfxMessageBox("你还没有选择歌曲,请选择!",
				MB_OK | MB_ICONINFORMATION,NULL);
		return;
	}
	CDialog::OnOK();
}
