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
	void SetInfoMusicPath(const char* Path);		//���������Ϣ�ļ�·��
	void ReadInfoMusicFile();						//��ȡ������Ϣ�ļ�
	void ReadNoteFile(const double dbSpeed);		//��ȡ���ֽڵ��ļ�
	CMusicFile();
	virtual ~CMusicFile();

protected:
	double m_NoteNum;						//���ֵ��ܽ�����
	CMusicNoteList m_NoteList[7];
	char m_InfoMusicPath[40];
	InfoMusic m_InfoMusic;
};

#endif // !defined(AFX_MUSICFILE_H__520D23FD_9D72_49C8_89ED_A6748BE98970__INCLUDED_)
