// MusicFile.cpp: implementation of the CMusicFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "JAM.h"
#include "MusicFile.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMusicFile::CMusicFile()				
{
	m_NoteNum = 0;							
	m_InfoMusicPath[0] = 0;					//音乐信息的的文件名
	m_InfoMusic.FristNote = 0;				//第一个音符出现的时间（拍数）
	m_InfoMusic.MusicFilePath[0] = 0;		//音频文件的路径
	m_InfoMusic.MusicName[0] = 0;			//音乐的名字
	m_InfoMusic.MusicSpeed = 0;				//音乐的速度
	m_InfoMusic.NoteFilePath[0] = 0;		//乐谱音符文件的路径
	m_InfoMusic.NoteNum = 0;				
}

CMusicFile::~CMusicFile()
{

}

void CMusicFile::ReadInfoMusicFile()
{
	ifstream fin;
	fin.open(m_InfoMusicPath);
	fin >> m_InfoMusic.MusicName >> m_InfoMusic.MusicSpeed
		>> m_InfoMusic.NoteNum >> m_InfoMusic.FristNote 
		>> m_InfoMusic.NoteFilePath >> m_InfoMusic.MusicFilePath;
	if (fin.bad())
		{
			::AfxMessageBox("音乐信息文件出错!",MB_OK | MB_ICONINFORMATION,NULL);
		}
}


/*

*Summary: read the informatin of Note file

*Parameters:

*     dbSpeed: the speed of falling *    

*Return : true is non

*/
void CMusicFile::ReadNoteFile(const double dbSpeed)				
{
	int			nMode = 0;			//音符样式，为按键位置
	int			nType = 0;			//音符类型，为1则短音符，为2则长音符
	//如果nMode和nType 是多个数，例如23 与12  说明 第二位和第三位音符同时出现且第三位音符为长音符

	double		dbNext = 0;			//下个音符间隔的节拍数
	double		Interval = 0;		//音符间隔
	ifstream fin;
	if (m_InfoMusic.NoteFilePath != NULL)
	{
		fin.open(m_InfoMusic.NoteFilePath);
		while (!fin.eof())
		{
			fin >> nMode >> nType >> dbNext;
			if (fin.good())
			{
				NoteInfo NoteTemp = {0};
				double NotePos = 473 - (((Interval+m_InfoMusic.FristNote)						//这个改变音符开始位置，数值错的话对不上声音
						*96)*dbSpeed);
				while (nMode != 0)
				{	
					NoteTemp.NoteType = (nType%10);
					NoteTemp.NoteMode = (nMode%10);
					NoteTemp.NotePos.yPos = NotePos;
					switch (NoteTemp.NoteMode)					//音符分为7个，分别对应7个位置，这里xpos是各个种类的音符要生成的x轴坐标
					{
					case 1:
						NoteTemp.NotePos.xPos = 5;
						break;
					case 2:
						NoteTemp.NotePos.xPos = 33;
						break;
					case 3:
						NoteTemp.NotePos.xPos = 55;
						break;
					case 4:
						NoteTemp.NotePos.xPos = 83;
						break;
					case 5:
						NoteTemp.NotePos.xPos = 115;
						break;
					case 6:
						NoteTemp.NotePos.xPos = 143;
						break;
					case 7:
						NoteTemp.NotePos.xPos = 165;
						break;
					}
					nType = nType/10;	
					nMode = nMode/10;
					m_NoteList[NoteTemp.NoteMode - 1].m_NoteInfoList.AddTail(NoteTemp);
				}
				if (dbNext != -1)
				{
					Interval = Interval + dbNext;
				}
			}
			m_NoteNum = Interval + m_InfoMusic.FristNote;
	//		else
	//		{
	//			::AfxMessageBox("音符文件出错!",MB_OK | MB_ICONINFORMATION,NULL);
	//			break;
	//		}
		}
	}
	else
	{
		::AfxMessageBox("您还没有选择音乐!",MB_OK | MB_ICONINFORMATION,NULL);
		exit(0);
	}
}


/*

*Summary: set the informatin of music path

*Parameters:

*     Path: the path of the file *    

*Return : true is non

*/
void CMusicFile::SetInfoMusicPath(const char* Path)
{
	strcpy(m_InfoMusicPath, Path);
}


