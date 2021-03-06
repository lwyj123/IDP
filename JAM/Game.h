// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__9CE0EC3C_DF6A_4F7C_B534_26285FB8871E__INCLUDED_)
#define AFX_GAME_H__9CE0EC3C_DF6A_4F7C_B534_26285FB8871E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MusicFile.h"
#include "Define.h"	// Added by ClassView

class CGame : public CMusicFile  
{
public:
	bool m_IsMusic;									//是否选择了音乐
	bool m_IsChoiceMenu;							//是否从对话框打开了歌曲
	bool m_IsGameStart;							//是否开始演奏

	void PrintBeatArea();							//打印音符区
	void InitGame();								//初始化游戏
	void ClearNote();								//清空音符
	double GetUserSpeed();							//返回玩家游戏速度
	void GameKeyDown(UINT nChar);							//游戏时按下键盘
	void GameStart();										//开始游戏		
	void SetUserSpeed(bool IsAddSpeed);						//获得玩家选择速度
	void MoveNote();										//移动音符
	void InitializationDC();								//初始化DC
	void ShowBG(CDC* pDC);									//打印背景
	CGame();
	virtual ~CGame();

protected:
	void ShowBeatArea();							//打印音符打击区
	void ShowCartoon();								//打印开场动画
	void LoadBMPToDC(CDC& pDC, UINT nIDResource);					//加载图片
	void CreateNullBmp(CDC& pDC);									//创建空图
	void SetNoteSpace();									//获得音符间距
	void CreateBeatArea();							//创建音符打击区
	void PrintNote();								//打印音符

	PrintState m_PrintState;
	PicDC m_PicDC;
    double m_dbPicSize;
	int m_BeatHeight;								//音符打击区高度，即画布总长度
	double m_MoveSpeed;								//移动距离
	double m_UserSpeed;							//玩家选择的速度
	double m_dbPlace;							//打印音符区的位置
};

#endif // !defined(AFX_GAME_H__9CE0EC3C_DF6A_4F7C_B534_26285FB8871E__INCLUDED_)
