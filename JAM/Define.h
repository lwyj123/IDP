#ifndef _DEFINE_H_
#define _DEFINE_H_

struct NotePoint
{
	double		xPos;			//横坐标
	double		yPos;			//纵坐标
};

struct NoteInfo
{
	int				NoteMode;		//音符样式
	int				NoteType;		//音符类型	
	NotePoint		NotePos;		//音符坐标
};

struct InfoMusic
{
	char	MusicFilePath[40];			//音乐文件路径
	char	MusicName[30];				//音乐名称
	double	MusicSpeed;					//音乐速度
	char	NoteFilePath[40];			//音乐音符文件路径
	double	FristNote;					//第一个音符出现的时间（拍数）
	int		NoteNum;					//音符数
};

struct PrintState
{
	bool	IsLongNote[7];		//是否是长音符
	bool	PrintKey[7];		//控制按键是否打印按下效果
	bool	SeriesState;		//控制是否打印连击数
	bool	CartoonState;		//控制是否打印开场动画
	int		BeatState;			//控制是否打印打击音符的状态（0为不打印）
};

struct ArtStat
{
	int		PillNum;			//药丸数
	int		CoolNum;			//统计打击为COOL的数量
	int		GoodNum;			//统计打击为GOOD的数量
	int		BadNum;				//统计打击为BAD的数量
	int		MissNum;			//统计打击为MISS的数量
	int		SeriesNum;			//统计连击的数量（初始要为-1）
	int		MaxSeriesNum;		//统计最大连击的数量
	int		nGrade;				//总成绩
	int		Jam;				//JAM气值
	int		Award;				//JAM爆气后,累计的奖励分数
};

struct PicDC
{
	CDC		L_Effect;				//打击效果	
	CDC		L_PicDC;				//空图
	CDC		L_CartoonDC;			//开机动画图片
	CDC		L_BeatArea;				//音符打击区
	CDC		L_PicArea;				//背景图片
	CDC		L_PicNote[3];			//音符图片
	CDC		L_PicKey;				//按键按下图片
	CDC		L_PicBeatState;			//音符打击时状态图片
	CDC		L_Series;				//连击数字图片

	CDC		L_ArtStat;				//技术统计
};

#endif