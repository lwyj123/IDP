// Game.cpp: implementation of the CGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Game.h"
#include "resource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGame::CGame()
{
	m_UserSpeed = 1.0;

	m_IsChoiceMenu =false;
	
    m_dbPicSize = 0.1;
	m_dbPlace = 0;
	m_IsMusic = false;
	m_BeatHeight = 0;
	m_IsGameStart = false;
	m_MoveSpeed = 0;
	m_PrintState.BeatState = 0;
	m_PrintState.CartoonState = true;
	m_PrintState.SeriesState =false;
	for (int i = 0; i < 7; i++)
	{
		m_PrintState.PrintKey[i] = false;
		m_PrintState.IsLongNote[i] = false;
	}
	InitGame();
}

CGame::~CGame()
{
	
}

void CGame::CreateNullBmp(CDC& pDC)
{
	CWindowDC dc(NULL);
	CBitmap DCBitmap;
	DCBitmap.CreateCompatibleBitmap(&dc, 800, 600);
	pDC.CreateCompatibleDC(NULL);
	pDC.SelectObject(&DCBitmap);
}

void CGame::LoadBMPToDC(CDC& pDC, UINT nIDResource)
{
	CBitmap DCBitmap;
	DCBitmap.LoadBitmap(nIDResource);   
	pDC.CreateCompatibleDC(NULL);
	pDC.SelectObject(&DCBitmap);
}

void CGame::ShowKeyArea(int State, int xPos, int yPos, int Width)
{
	double dbRed = 0;
	double dbGreen = 0;
	double dbBlue = 0;
	switch (State)			//根据按键设置起始颜色
	{
		case 1:
		case 3:
		case 5:
		case 7:
			dbRed = 240;
			dbGreen = 220;
			dbBlue = 100;
			break;

		case 2:
		case 6:
			dbRed = 165;
			dbGreen = 135;
			dbBlue = 225;
			break;

		case 4:
			dbRed = 255;
			dbGreen = 190;//190
			dbBlue = 155;//155
			break;
	}
	
	while (dbRed != 0 || dbGreen != 0 || dbBlue != 0)
	{
		CBrush CKeyBrush;
		CKeyBrush.CreateSolidBrush(RGB(dbRed, dbGreen, dbBlue)); // 设置画刷
		m_PicDC.L_PicDC.SelectObject(&CKeyBrush);
		CPen CKeyPen;
		CKeyPen.CreatePen(PS_NULL, 0, RGB(dbRed, dbGreen, dbBlue)); // 设置画笔
		m_PicDC.L_PicDC.SelectObject(&CKeyPen); 
		m_PicDC.L_PicDC.Rectangle(xPos, yPos, xPos+Width, yPos-3);

		if (dbRed >= 4)
		{
			dbRed = dbRed - 4;
		}
		else
		{
			dbRed = 0;
		}
		if (dbGreen >= 2)
		{
			dbGreen = dbGreen - 2;
		}
		else
		{
			dbGreen = 0;
		}
		if (dbBlue >= 2)
		{
			dbBlue = dbBlue - 2;
		}
		else
		{
			dbBlue = 0;
		}
		yPos = yPos - 2;
	}
}

//显示背景
void CGame::ShowBG(CDC* pDC)
{
	if (m_PrintState.CartoonState)
	{
		ShowCartoon();
	}
	else
	{
        static int nTime = 0;
		char szSpeed[20] = {0};

		sprintf(szSpeed, "Speed:%0.1lf", m_UserSpeed);

		m_PicDC.L_CartoonDC.DeleteTempMap();
		m_PicDC.L_PicDC.BitBlt(0, 0, 800, 600, &m_PicDC.L_PicArea, 0, 0, SRCCOPY);
		m_PicDC.L_PicDC.SetBkMode(TRANSPARENT); // 设置透明文字模式
		m_PicDC.L_PicDC.SetTextColor(RGB(255, 255, 255));// 设置文字颜色为白色
		m_PicDC.L_PicDC.TextOut(440, 538, m_InfoMusic.MusicName, 
						strlen(m_InfoMusic.MusicName)); // 打印歌曲名称
		m_PicDC.L_PicDC.TextOut( 340, 550, szSpeed, 
						strlen(szSpeed)); // 打印玩家选择的速度	
		ShowBeatArea();			//打印音符通道
        
        if (m_PrintState.BeatState != 0 || m_PrintState.SeriesState != 0)
		{     
			//打印的图象由小渐大			
			if (m_dbPicSize >= 1.0)
            {
                nTime++;
                if (nTime > 20)
                {
                    nTime = 0;
                    m_dbPicSize = 0.1;
                    m_PrintState.SeriesState = false;
                }
            }
            else
            {
                m_dbPicSize = m_dbPicSize + 0.3;
            }
		}
        
	}
	pDC ->BitBlt(0, 0, 800, 600, &m_PicDC.L_PicDC, 0, 0, SRCCOPY);
}

void CGame::InitializationDC()
{
	CreateNullBmp(m_PicDC.L_PicDC);
	LoadBMPToDC(m_PicDC.L_PicArea, IDB_BITMAP_BG);
	LoadBMPToDC(m_PicDC.L_CartoonDC, IDB_BITMAP_OPEN);
	LoadBMPToDC(m_PicDC.L_PicNote[0], IDB_BITMAP_KEY_0);
	LoadBMPToDC(m_PicDC.L_PicNote[1], IDB_BITMAP_KEY_1);
	LoadBMPToDC(m_PicDC.L_PicNote[2], IDB_BITMAP_KEY_2);
}

//播放开头动画
void CGame::ShowCartoon()					
{
	static int i =0;
	static int j = 0; 
	m_PicDC.L_PicDC.StretchBlt(0, 0, 800, 600, 
							&m_PicDC.L_CartoonDC, 
							200*i, 150*j, 200, 150,
							SRCCOPY);
	i++;
	if (i > 5)
	{
		i = 0;
		j++;
	}
	if (j > 16)
	{
		m_PrintState.CartoonState = false;
	}
}

void CGame::MoveNote()
{
	if (m_IsGameStart)
	{
		for (int i = 0; i < 7; i++)
		{
			m_NoteList[i].MoveNoteList(m_MoveSpeed, m_PrintState);
		}
	}
}

void CGame::SetUserSpeed(bool IsAddSpeed)
{
	if (!m_IsGameStart)
	{
		if (IsAddSpeed)
		{
			if (m_UserSpeed < 3)
			{
				m_UserSpeed = m_UserSpeed + 1;
				if (m_IsMusic)
				{
					PrintBeatArea();
				}
			}
		}
		else
		{
			if (m_UserSpeed > 1)
			{
				m_UserSpeed = m_UserSpeed - 1;
				if (m_IsMusic)
				{
					PrintBeatArea();
				}
			}
		}
	}
}

void CGame::SetNoteSpace()
{
	m_MoveSpeed = (m_InfoMusic.MusicSpeed/10)*m_UserSpeed;
}

void CGame::GameStart()
{
	if (m_InfoMusic.MusicFilePath[0] != 0)
	{
		InitGame();
		//停止播放音乐
		::PlaySound(NULL,NULL,SND_PURGE);
		if (!m_IsChoiceMenu)
		{
			ClearNote();

			ReadNoteFile(m_UserSpeed);
			CreateBeatArea();
			PrintNote();	
		}
		::PlaySound(m_InfoMusic.MusicFilePath, NULL, 
						SND_ASYNC|SND_FILENAME); //放声音
		m_IsGameStart = true;
		m_IsMusic = true;
		m_IsChoiceMenu = false;
	}
	else
	{
		::AfxMessageBox("你还没有选择歌曲,请选择后再开始!",
				MB_OK | MB_ICONINFORMATION,NULL);
	}
}

void CGame::PrintNote()
{
	for (int i = 0; i < 7; i++)
	{
		m_NoteList[i].PrintNoteList(m_PicDC, m_BeatHeight);
	}
	m_dbPlace = m_BeatHeight - 481;
}

//按下游戏按键 
void CGame::GameKeyDown(UINT nChar)			
{
	switch (nChar)
	{
	case VK_ESCAPE:								//跳过动画
		m_PrintState.CartoonState = false;			
		break;

	case 83:	
		KeyDownBeat(1);		
		break;

	case 68:
		KeyDownBeat(2);	
		break;

	case 70:
		KeyDownBeat(3);	
		break;

	case VK_SPACE:
		KeyDownBeat(4);	
		break;

	case 74:
		KeyDownBeat(5);	 
		break;

	case 75:
		KeyDownBeat(6);	
		break;

	case 76:
		KeyDownBeat(7);	
		break;	
	}
}

void CGame::CreateBeatArea()
{
	if (m_NoteNum != 0)
	{
		m_PicDC.L_BeatArea.DeleteDC();
		m_BeatHeight = 0;
		m_BeatHeight = (int)((m_NoteNum * 96 + 473)*m_UserSpeed);
		CWindowDC dc(NULL);
		CBitmap DCBitmap;
		DCBitmap.CreateCompatibleBitmap(&dc, 190, m_BeatHeight);
		m_PicDC.L_BeatArea.CreateCompatibleDC(NULL);
		m_PicDC.L_BeatArea.SelectObject(&DCBitmap);
	}
}

void CGame::ShowBeatArea()
{
	if (m_IsMusic)
	{
		COLORREF nColor = m_PicDC.L_BeatArea.GetPixel(0, 0);

		::TransparentBlt(m_PicDC.L_PicDC.GetSafeHdc(), // 目标DC
					5, 0, 190, 480, 
					m_PicDC.L_BeatArea.GetSafeHdc(), // 源DC
					0, (int)(m_dbPlace -7*(m_UserSpeed - 1)), 
					190, 480,
					nColor); // 透明色

		if (m_IsGameStart == true)
		{
			if (m_dbPlace > 0)
			{
				m_dbPlace = m_dbPlace - m_MoveSpeed;
			}
			else
			{
				m_PicDC.L_BeatArea.DeleteDC();
				m_dbPlace = m_BeatHeight - 480;
				m_IsGameStart = false;
				m_IsMusic = false;
			}
		}
	}
}


double CGame::GetUserSpeed()
{
	return m_UserSpeed;
}

void CGame::ClearNote()
{
	for (int i = 0; i < 7; i++)
	{
		m_NoteList[i].m_NoteInfoList.RemoveAll();
	}
}

void CGame::InitGame()
{

}

void CGame::PrintBeatArea()
{
	ClearNote();
	SetNoteSpace();
	ReadNoteFile(m_UserSpeed);
	CreateBeatArea();
	PrintNote();
}

void CGame::GameKeyUp(UINT nChar)
{
	switch (nChar)
	{
	case 83:	
		KeyUpBeat(1);
		break;

	case 68:
		KeyUpBeat(2);
		break;

	case 70:
		KeyUpBeat(3);
		break;

	case VK_SPACE:
		KeyUpBeat(4);
		break;

	case 74:
		KeyUpBeat(5);
		break;
	case 75:
		KeyUpBeat(6);
		break;

	case 76:
		KeyUpBeat(7);
		break;	
	}
}

void CGame::KeyDownBeat(int State)
{
	m_PrintState.PrintKey[State - 1] = true;
	if (!m_NoteList[State - 1].m_NoteInfoList.IsEmpty())
	{
		NoteInfo Note = m_NoteList[State - 1].m_NoteInfoList.GetHead();
		if (Note.NotePos.yPos >= 380 && Note.NotePos.yPos <= 520)
		{
            m_dbPicSize = 0.1;
			m_NoteList[State - 1].m_NoteInfoList.RemoveHead();
		}
	}
}

void CGame::KeyUpBeat(int State)
{
	m_PrintState.PrintKey[State - 1] = false;
	if (m_PrintState.IsLongNote[State - 1])
	{
		if (!m_NoteList[State - 1].m_NoteInfoList.IsEmpty())
		{
			NoteInfo  Note = m_NoteList[State - 1].m_NoteInfoList.GetHead();
			if (Note.NotePos.yPos <= 520)
			{
                m_dbPicSize = 0.1;
				m_NoteList[State - 1].m_NoteInfoList.RemoveHead();		
			}
			m_PrintState.IsLongNote[State - 1] = false;
		}
	}
}

void CGame::BrushNote(NoteInfo Note)
{
	NotePoint Temp = {0};
	int Width = 0;
	CBrush NoteBrush;
	CPen NotePen;

	switch (Note.NoteMode)			
	{
		case 1:
		case 3:
		case 5:
		case 7:
			Width = 29;
			break;

		case 2:
		case 6:
			Width = 23;
			break;

		case 4:
			Width = 33;
			break;
	}
	Temp.xPos = Note.NotePos.xPos - 5;
	Temp.yPos = m_dbPlace + Note.NotePos.yPos + 8;
		
	NoteBrush.CreateSolidBrush(RGB(0, 0, 0)); // 设置画刷
	m_PicDC.L_BeatArea.SelectObject(&NoteBrush);

	NotePen.CreatePen(PS_NULL, 0, RGB(0, 0, 0)); // 设置画笔
	m_PicDC.L_BeatArea.SelectObject(&NotePen); 
	m_PicDC.L_BeatArea.Rectangle((int)Temp.xPos, (int)Temp.yPos, 
						(int)Temp.xPos + Width, (int)(Temp.yPos + 9));

}
