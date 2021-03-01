#pragma once
#include "cv.h"
#include"highgui.h"
#include"GameUI.h"
////////////////控制敌人的参数以及移动、绘制、生死/////////////////////////////
class CEnemy
{
public:
	CEnemy();
	virtual ~CEnemy();
	CEnemy(IplImage* img, int posx, int posy, int backSpeed, bool ifwalk);
	void Move();
	void Draw(IplImage* backImage);
	bool NeedClear(){ return m_isDead; }
	IplImage* GetNowImage(){ return m_img; }
	CvPoint GetPoint(){ return m_pos; }
private:
	int m_speed;
	int m_walkLoop;
	int m_walkingFlag[10];
	bool m_isDead;
	bool m_needWalking;
	CvPoint m_pos;
	IplImage* m_img;
};