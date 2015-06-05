#ifndef _DEFINE_H_
#define _DEFINE_H_

struct NotePoint
{
	double		xPos;			//������
	double		yPos;			//������
};

struct NoteInfo
{
	int				NoteMode;		//������ʽ
	int				NoteType;		//��������	
	NotePoint		NotePos;		//��������
};

struct InfoMusic
{
	char	MusicFilePath[40];			//�����ļ�·��
	char	MusicName[30];				//��������
	double	MusicSpeed;					//�����ٶ�
	char	NoteFilePath[40];			//���������ļ�·��
	double	FristNote;					//��һ���������ֵ�ʱ�䣨������
	int		NoteNum;					//������
};

struct PrintState
{
	bool	IsLongNote[7];		//�Ƿ��ǳ�����
	bool	PrintKey[7];		//���ư����Ƿ��ӡ����Ч��
	bool	SeriesState;		//�����Ƿ��ӡ������
	bool	CartoonState;		//�����Ƿ��ӡ��������
	int		BeatState;			//�����Ƿ��ӡ���������״̬��0Ϊ����ӡ��
};

struct ArtStat
{
	int		PillNum;			//ҩ����
	int		CoolNum;			//ͳ�ƴ��ΪCOOL������
	int		GoodNum;			//ͳ�ƴ��ΪGOOD������
	int		BadNum;				//ͳ�ƴ��ΪBAD������
	int		MissNum;			//ͳ�ƴ��ΪMISS������
	int		SeriesNum;			//ͳ����������������ʼҪΪ-1��
	int		MaxSeriesNum;		//ͳ���������������
	int		nGrade;				//�ܳɼ�
	int		Jam;				//JAM��ֵ
	int		Award;				//JAM������,�ۼƵĽ�������
};

struct PicDC
{
	CDC		L_Effect;				//���Ч��	
	CDC		L_PicDC;				//��ͼ
	CDC		L_CartoonDC;			//��������ͼƬ
	CDC		L_BeatArea;				//���������
	CDC		L_PicArea;				//����ͼƬ
	CDC		L_PicNote[3];			//����ͼƬ
	CDC		L_PicKey;				//��������ͼƬ
	CDC		L_PicBeatState;			//�������ʱ״̬ͼƬ
	CDC		L_Series;				//��������ͼƬ

	CDC		L_ArtStat;				//����ͳ��
};

#endif