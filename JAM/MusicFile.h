// MusicFile.h: interface for the CMusicFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUSICFILE_H__520D23FD_9D72_49C8_89ED_A6748BE98970__INCLUDED_)
#define AFX_MUSICFILE_H__520D23FD_9D72_49C8_89ED_A6748BE98970__INCLUDED_

#include "MusicNoteList.h"	// Added by ClassView
#include "Define.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMusicFile 
{
public:
	void SetInfoMusicPath(const char* Path);		//获得音乐信息文件路径
	void ReadInfoMusicFile();						//读取音乐信息文件
	void ReadNoteFile(const double dbSpeed);		//读取音乐节点文件
	CMusicFile();
	virtual ~CMusicFile();

protected:
	double m_NoteNum;						//音乐的总节拍数
	CMusicNoteList m_NoteList[7];
	char m_InfoMusicPath[40];
	InfoMusic m_InfoMusic;
};

#endif // !defined(AFX_MUSICFILE_H__520D23FD_9D72_49C8_89ED_A6748BE98970__INCLUDED_)
