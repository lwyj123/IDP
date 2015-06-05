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

void CGame::BeatNote(NoteInfo Note, int State)
{
	if (Note.NoteType == 2)
	{
		this->m_PrintState.IsLongNote[State - 1] = true;
	}
	else
	{
		m_PrintState.IsLongNote[State - 1] = false;
	}
	//打击音符为COOL
	if (Note.NotePos.yPos >= 460 && Note.NotePos.yPos <= 500)	
	{
		m_PrintState.BeatState = 1;			
		m_ArtStat.Jam = m_ArtStat.Jam + 4;
		if (m_ArtStat.Jam >= 100)
		{
			m_ArtStat.Award = m_ArtStat.Award + 10;
			m_ArtStat.Jam = m_ArtStat.Jam -100;
		}
		
		m_ArtStat.nGrade = m_ArtStat.nGrade + m_ArtStat.Award + 200;
		m_ArtStat.CoolNum++;
		m_ArtStat.SeriesNum++;
        m_PrintState.SeriesState = true;
		if (m_ArtStat.SeriesNum > m_ArtStat.MaxSeriesNum)
		{
			m_ArtStat.MaxSeriesNum = m_ArtStat.SeriesNum;
		}
		BrushNote(Note);
	}
	//打击音符为GOOD
	if ((Note.NotePos.yPos < 460 && Note.NotePos.yPos >= 420) ||
		(Note.NotePos.yPos > 500 && Note.NotePos.yPos >= 510))	
	{
		m_PrintState.BeatState = 2;
		m_ArtStat.Jam = m_ArtStat.Jam + 2;
		if (m_ArtStat.Jam >= 100)
		{
			m_ArtStat.Award = m_ArtStat.Award + 10;
			m_ArtStat.Jam = m_ArtStat.Jam -100;
		}
		
		m_ArtStat.nGrade = m_ArtStat.nGrade + m_ArtStat.Award + 100;
		m_ArtStat.GoodNum++;
		m_ArtStat.SeriesNum++;
        m_PrintState.SeriesState = true;
		if (m_ArtStat.SeriesNum > m_ArtStat.MaxSeriesNum)
		{
			m_ArtStat.MaxSeriesNum = m_ArtStat.SeriesNum;
		}
		BrushNote(Note);
	}
	//打击音符为BAD
	if ((Note.NotePos.yPos < 420 && Note.NotePos.yPos >= 400) ||
		(Note.NotePos.yPos > 510 && Note.NotePos.yPos >= 520))
	{
		if (m_ArtStat.PillNum > 0)
		{
			m_PrintState.BeatState = 1;
			m_ArtStat.Jam = m_ArtStat.Jam + 4;
			if (m_ArtStat.Jam >= 100)
			{
				m_ArtStat.Award = m_ArtStat.Award + 10;
				m_ArtStat.Jam = m_ArtStat.Jam -100;
			}
			m_ArtStat.nGrade = m_ArtStat.nGrade + m_ArtStat.Award + 200;
			m_ArtStat.CoolNum++;
			m_ArtStat.SeriesNum++;
			if (m_ArtStat.SeriesNum > m_ArtStat.MaxSeriesNum)
			{
				m_ArtStat.MaxSeriesNum = m_ArtStat.SeriesNum;
			}
			m_ArtStat.PillNum--;
		}
		else
		{
			m_PrintState.BeatState = 3;
			m_ArtStat.Jam = 0;
			m_ArtStat.nGrade = m_ArtStat.nGrade + m_ArtStat.Award + 4;
			m_ArtStat.BadNum++;
			m_ArtStat.SeriesNum = -1;
		}
        m_PrintState.SeriesState = true;
		BrushNote(Note);
	}
	//打击音符为MISS
	if (Note.NotePos.yPos < 400)
	{
		m_PrintState.BeatState = 4;
		if(m_ArtStat.nGrade >= 10)
		{
			m_ArtStat.nGrade = m_ArtStat.nGrade - 10;
		}
		else
		{
			m_ArtStat.nGrade = 0;
		}
		m_ArtStat.MissNum++;
        m_PrintState.SeriesState = true;
		m_ArtStat.Jam = 0;
		m_ArtStat.Award = 0;
		m_ArtStat.SeriesNum = -1;
		BrushNote(Note);
	}

	if (m_ArtStat.SeriesNum%15 == 0 && m_ArtStat.SeriesNum != 0)
	{
		m_ArtStat.PillNum++;
		if (m_ArtStat.PillNum > 5)
		{
			m_ArtStat.PillNum = 5;
		}
	}
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
			dbGreen = 190;
			dbBlue = 155;
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
		ShowCharacter();
		ShowKeyDown();
		ShowBeatArea();
        ShowPill();
		if (m_PrintState.SeriesState)
		{
            ShowSeries();
		}
        
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
	LoadBMPToDC(m_PicDC.L_Character, IDB_BITMAP_CHARACTER);	
	LoadBMPToDC(m_PicDC.L_PicKey, IDB_BITMAP_KEYDOWN);	
	LoadBMPToDC(m_PicDC.L_Grade, IDB_BITMAP_GRADE);
	LoadBMPToDC(m_PicDC.L_Pill, IDB_BITMAP_PILL);
	LoadBMPToDC(m_PicDC.L_Series, IDB_BITMAP_SERIES);	
}

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
			m_NoteList[i].MoveNoteList(m_MoveSpeed, m_PrintState, m_ArtStat);
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

void CGame::GameKeyDown(UINT nChar)
{
	switch (nChar)
	{
	case VK_ESCAPE:
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
	m_ArtStat.Award = 0;
	m_ArtStat.BadNum = 0;
	m_ArtStat.CoolNum = 0;
	m_ArtStat.GoodNum = 0;
	m_ArtStat.MissNum = 0;
	m_ArtStat.Jam = 0;
	m_ArtStat.MaxSeriesNum = 0;
	m_ArtStat.nGrade = 0;
	m_ArtStat.PillNum = 0;
	m_ArtStat.SeriesNum = 0;
}

void CGame::PrintBeatArea()
{
	ClearNote();
	SetNoteSpace();
	ReadNoteFile(m_UserSpeed);
	CreateBeatArea();
	PrintNote();
}

void CGame::ShowCharacter()
{
	static int nCharacter = 0;
	static int nI = 0;		//控制人物变化速度
	COLORREF nColor = m_PicDC.L_Character.GetPixel(0, 0); // 获取透明色

	::TransparentBlt(m_PicDC.L_PicDC.GetSafeHdc(), // 目标DC
					400, 200,
					119, 148,
					m_PicDC.L_Character.GetSafeHdc(), // 源DC
					nCharacter*121, 0, 
					119, 148,
					nColor); // 透明色
	if (nI == 1)
	{
		nCharacter++;
		nI = 0;
	}
	else
	{
		nI++;
	}

	if (nCharacter > 20 )
	{
		nCharacter = 0;
	}
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

void CGame::ShowKeyDown()
{
	if (m_PrintState.PrintKey[0])
	{
		m_PicDC.L_PicDC.BitBlt(3, 486, 30, 47, &m_PicDC.L_PicKey, 0, 0, SRCCOPY);
		ShowKeyArea(1, 4, 480, 30);
	}
	if (m_PrintState.PrintKey[1])
	{
		m_PicDC.L_PicDC.BitBlt(33, 486, 22, 47, &m_PicDC.L_PicKey, 30, 0, SRCCOPY);
		ShowKeyArea(2, 34, 480, 22);
	}
	if (m_PrintState.PrintKey[2])
	{
		m_PicDC.L_PicDC.BitBlt(55, 486, 28, 47, &m_PicDC.L_PicKey, 52, 0, SRCCOPY);
		ShowKeyArea(3, 56, 480, 28);
	}
	if (m_PrintState.PrintKey[3])
	{
		m_PicDC.L_PicDC.BitBlt(83, 486, 32, 47, &m_PicDC.L_PicKey, 80, 0, SRCCOPY);
		ShowKeyArea(4, 84, 480, 32);
	}
	if (m_PrintState.PrintKey[4])
	{
		m_PicDC.L_PicDC.BitBlt(115, 486, 28, 47, &m_PicDC.L_PicKey, 112, 0, SRCCOPY);
		ShowKeyArea(5, 116, 480, 28);
	}
	if (m_PrintState.PrintKey[5])
	{
		m_PicDC.L_PicDC.BitBlt(143, 486, 22, 47, &m_PicDC.L_PicKey, 140, 0, SRCCOPY);
		ShowKeyArea(6, 144, 480, 22);
	}
	if (m_PrintState.PrintKey[6])
	{
		m_PicDC.L_PicDC.BitBlt(165, 486, 30, 47, &m_PicDC.L_PicKey, 162, 0, SRCCOPY);
		ShowKeyArea(7, 166, 480, 30);
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
			BeatNote(Note, State);
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
				BeatNote(Note, State);
				m_NoteList[State - 1].m_NoteInfoList.RemoveHead();		
			}
			m_PrintState.IsLongNote[State - 1] = false;
		}
	}
}

void CGame::PrintNum(int Num, CDC& PicDC, int Height, int Width, int xPos, int yPos)
{
	int Temp = 0;
	int nI = 0;
	int nJ = 0;
	int nNum = 0;
	Temp = Num;
	//统计位数
	while((Temp = Temp/10)!=0)
	{
		nJ++;
		nNum++;
	}
	Temp = Num;

	for (;nJ >= 0; nJ--)
	{
		nI = Temp%10;
		COLORREF nColor = PicDC.GetPixel(0, 0); // 获取透明色
		::TransparentBlt(m_PicDC.L_PicDC.GetSafeHdc(), // 目标DC
						1+xPos-(nNum-nJ)*Width, yPos,
						Width, Height,
						PicDC.GetSafeHdc(), // 源DC
						Width*nI, 0, 
						Width, Height,
						nColor); // 透明色

		Temp = Temp/10;
	}
}

void CGame::ShowSeries()
{
	int Temp = 0;
	int nI = 0;
	int nJ = 0;
	int nNum = 0;
	Temp = m_ArtStat.SeriesNum;
	//统计位数
	while((Temp = Temp/10)!=0)
	{
		nJ++;
		nNum++;
	}
	Temp = m_ArtStat.SeriesNum;

	for (;nJ >= 0; nJ--)
	{
		nI = Temp%10;
		if(nI != 0 || nNum != 0)
		{
			COLORREF nColor = m_PicDC.L_Series.GetPixel(1, 1); // 获取透明色
            ::TransparentBlt(m_PicDC.L_PicDC.GetSafeHdc(), // 目标DC
							80-nNum*22+44*nJ+(int)((44*(1-m_dbPicSize))/2), 220+(int)((68*(1-m_dbPicSize))/2),
							(int)(44*m_dbPicSize), (int)(68*m_dbPicSize),
							m_PicDC.L_Series.GetSafeHdc(), // 源DC
							44*nI, 0, 
							44, 68,
							nColor); // 透明色
		}
		Temp = Temp/10;
    }
}

void CGame::ShowPill()
{
    if (m_ArtStat.PillNum > 0)
	{
		for (int i=0; i<m_ArtStat.PillNum; i++)
		{
			m_PicDC.L_PicDC.BitBlt(200, 2+(30+1)*(4-i),
                                    30, 30, 
                                    &m_PicDC.L_Pill, 
                                    0, 0, SRCCOPY);
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
