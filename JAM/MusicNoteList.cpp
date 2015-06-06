// MusicNoteList.cpp: implementation of the CMusicNoteList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JAM.h"
#include "MusicNoteList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMusicNoteList::CMusicNoteList()
{

}

CMusicNoteList::~CMusicNoteList()
{

}

void CMusicNoteList::MoveNoteList(double Speed, PrintState& State) 
{
	if (!m_NoteInfoList.IsEmpty())
	{
		POSITION PosTemp = m_NoteInfoList.GetHeadPosition();
		while (PosTemp != NULL)
		{
			if (m_NoteInfoList.GetAt(PosTemp).NotePos.yPos > 520)
			{
				m_NoteInfoList.RemoveHead();
				PosTemp = m_NoteInfoList.GetHeadPosition();
				State.BeatState = 4;
				State.SeriesState = true;
			}
			else
			{
				m_NoteInfoList.GetAt(PosTemp).NotePos.yPos += Speed;	
				m_NoteInfoList.GetNext(PosTemp);	
			}
		}	
	}
}

void CMusicNoteList::PrintNoteList(PicDC& Pic, int PicHeight)
{
	if (!m_NoteInfoList.IsEmpty())
	{
		POSITION PosTemp = m_NoteInfoList.GetHeadPosition();
		while (PosTemp != NULL)
		{
			NotePoint TempPos = {0};
			NoteInfo Temp = m_NoteInfoList.GetAt(PosTemp);
			TempPos.xPos = Temp.NotePos.xPos - 5;
			TempPos.yPos = PicHeight - (473 - Temp.NotePos.yPos);
			if (Temp.NoteType == 1 || Temp.NoteType == 3)
			{				
				PrintNote(Pic, Temp.NoteMode, TempPos);
				m_NoteInfoList.GetNext(PosTemp);
			}
			else
			{
				m_NoteInfoList.GetNext(PosTemp);
				NoteInfo TempNext = m_NoteInfoList.GetAt(PosTemp);
				NotePoint TempNextPos ={0};
				TempNextPos.xPos = TempNext.NotePos.xPos - 5;
				TempNextPos.yPos = PicHeight - (473 - TempNext.NotePos.yPos);
				while (TempPos.yPos > TempNextPos.yPos)
				{
					PrintNote(Pic, Temp.NoteMode, TempPos);
					TempPos.yPos = TempPos.yPos - 7;
				}
			}	
		}	
	}
}



void CMusicNoteList::PrintNote(PicDC& Pic, int NoteMode, NotePoint Pos)
{
	switch (NoteMode)
	{
	case 1:
	case 3:	
	case 5:
	case 7:
		Pic.L_BeatArea.BitBlt((int)Pos.xPos, (int)Pos.yPos,
			28, 7, &Pic.L_PicNote[0], 0, 0, SRCCOPY);
		break;
	case 2:
	case 6:
		Pic.L_BeatArea.BitBlt((int)Pos.xPos, (int)Pos.yPos,
			22, 7, &Pic.L_PicNote[1], 0, 0, SRCCOPY);
		break;
	case 4:
		Pic.L_BeatArea.BitBlt((int)Pos.xPos, (int)Pos.yPos,
			32, 7, &Pic.L_PicNote[2], 0, 0, SRCCOPY);
		break;
	}		
}
