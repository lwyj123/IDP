// MusicNoteList.h: interface for the CMusicNoteList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSICNOTELIST_H__3B039074_8A06_46C2_8D60_174B1BDF2D60__INCLUDED_)
#define AFX_MUSICNOTELIST_H__3B039074_8A06_46C2_8D60_174B1BDF2D60__INCLUDED_

#include "Define.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMusicNoteList  
{
public:
	void PrintNoteList(PicDC& Pic, int PicHeight);				//打印音符
	void MoveNoteList(double Speed, PrintState& State, ArtStat& Art);//移动音符
	CMusicNoteList();
	virtual ~CMusicNoteList();
	CList<NoteInfo, NoteInfo&> m_NoteInfoList;

protected:
	void PrintNote(PicDC& Pic, int NoteMode, NotePoint Pos);	//打印单个音符
};

#endif // !defined(AFX_MUSICNOTELIST_H__3B039074_8A06_46C2_8D60_174B1BDF2D60__INCLUDED_)
