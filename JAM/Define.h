#ifndef _DEFINE_H_
#define _DEFINE_H_

struct NotePoint
{
	double		xPos;			//������
	double		yPos;			//������
};

struct NoteInfo		//һ������������������ʽ�������ͺ���������
{
	int				NoteMode;		//������ʽ
	int				NoteType;		//��������	
	NotePoint		NotePos;		//��������
};

struct InfoMusic	//�����ļ���Ϣ�ṹ�壬�������׵���Ϣ
{
	char	MusicFilePath[40];			//�����ļ�·��
	char	MusicName[30];				//��������
	double	MusicSpeed;					//�����ٶ�
	char	NoteFilePath[40];			//���������ļ�·��
	double	FristNote;					//��һ���������ֵ�ʱ�䣨������
	int		NoteNum;					//������
};

struct PrintState				//���ƴ�ӡ״̬�Ľṹ��
{
	bool	IsLongNote[7];		//�Ƿ��ǳ�����
	bool	PrintKey[7];		//���ư����Ƿ��ӡ����Ч��
	bool	SeriesState;		//�����Ƿ��ӡ������
	bool	CartoonState;		//�����Ƿ��ӡ��������
	int		BeatState;			//�����Ƿ��ӡ���������״̬��0Ϊ����ӡ��
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