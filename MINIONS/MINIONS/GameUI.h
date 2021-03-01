#pragma once
#include "cv.h"
#include"highgui.h"
//////整个界面的图片效果,在gamemanager里实体化//////////
class CGameUI
{
public:
	CGameUI();
	virtual ~CGameUI();
private:
	int m_speed;
	int m_length;//m_realLength%显示画面宽度
	int m_roadHigh;
	int m_realLength;//画面移动的实长
	IplImage* m_img;
	IplImage* m_clone;
	IplImage* m_banana[4];
	IplImage* m_enemy[2];
	IplImage* m_barrier[5];
	IplImage* m_sign[10];
	IplImage* m_whiteflag[3];//承载各种道具信息的图
	IplImage* m_nums[10];
	IplImage* m_score_letter;
	IplImage* m_prop[10];
public:
	void SetBackImage();
	void ShowLevelStart();
	void ShowLevelEnd(int score);
	void ShowNowImage(char* WndName);
	void InitRealLength(){ m_realLength = 0; }
	void DrawSigns(int index, int px, int py);
	void ShowScore(int score, int px, int py, bool ex);
	int GetBackSpeed(){ return m_speed; }
	int GetRoadHigh(){ return m_roadHigh; }
	int GetRealLenghth(){ return m_realLength; }
	IplImage* GetNowImage(){ return m_img; }
	IplImage* GetSignImg(int i){ return m_sign[i]; }
	IplImage* GetPropImg(int i){ return m_prop[i]; }
	IplImage* GetEnemyImg(int i){ return m_enemy[i]; }
	IplImage* GetBananaImg(int i){ return m_banana[i]; }
	IplImage* GetBarrierImg(int i){ return m_barrier[i]; }
	IplImage* GetWhiteflag(int level){ return m_whiteflag[level - 1]; }
};

