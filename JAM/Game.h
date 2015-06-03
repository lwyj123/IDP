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
	bool m_IsMusic;									//�Ƿ�ѡ��������
	bool m_IsChoiceMenu;							//�Ƿ�ӶԻ�����˸���
	bool m_IsGameStart;							//�Ƿ�ʼ����

	void PrintBeatArea();							//��ӡ������
	void InitGame();								//��ʼ����Ϸ
	void ClearNote();								//�������
	double GetUserSpeed();							//���������Ϸ�ٶ�
	void GameKeyDown(UINT nChar);							//��Ϸʱ���¼���
	void GameKeyUp(UINT nChar);								//��Ϸʱ�ſ�����
	void GameStart();										//��ʼ��Ϸ		
	void SetUserSpeed(bool IsAddSpeed);						//������ѡ���ٶ�
	void MoveNote();										//�ƶ�����
	void InitializationDC();								//��ʼ��DC
	void ShowBG(CDC* pDC);									//��ӡ����
	CGame();
	virtual ~CGame();

protected:
	void BrushNote(NoteInfo Note);					//ˢ������
	void ShowPill();								//��ӡҩ��
	void ShowBeatState();					//��ӡ���������״̬
	void ShowSeries();								//��ӡ������
	void ShowArtStat();								//��ӡ����ͳ��
	void PrintNum(int Num, CDC& PicDC, int Height, int Width, int xPos, int yPos);
	void KeyUpBeat(int State);
	void KeyDownBeat(int State);
	void ShowKeyDown();								//��ӡ���̰���ͼƬ
	void ShowCharacter();							//��ӡ���ﶯ��
	void ShowBeatArea();							//��ӡ���������
	void BeatNote(NoteInfo Note ,int State);						//�������
	void ShowCartoon();								//��ӡ��������
	void ShowKeyArea(int State, int xPos, int yPos,int Width);		//��ӡ��������
	void LoadBMPToDC(CDC& pDC, UINT nIDResource);					//����ͼƬ
	void CreateNullBmp(CDC& pDC);									//������ͼ
	void SetNoteSpace();									//����������
	void CreateBeatArea();							//�������������
	void PrintNote();								//��ӡ����

	PrintState m_PrintState;
	PicDC m_PicDC;
	ArtStat m_ArtStat;
    double m_dbPicSize;
	int m_BeatHeight;								//����������߶�
	double m_MoveSpeed;								//�ƶ�����
	double m_UserSpeed;							//���ѡ����ٶ�
	double m_dbPlace;							//��ӡ��������λ��
};

#endif // !defined(AFX_GAME_H__9CE0EC3C_DF6A_4F7C_B534_26285FB8871E__INCLUDED_)
