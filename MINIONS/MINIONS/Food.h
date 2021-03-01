#pragma once
#include "cv.h"
#include"highgui.h"
#include"GameUI.h"
class CFood
{
public:
	CFood::CFood();
	CFood(IplImage* img, int posx, int posy, int backSpeed);
	virtual ~CFood();
	void Move();
	void Draw(IplImage* backImage);
	int GetWidth(){ return m_img->width; }
	bool NeedClear(){ return m_isDead; }
	CvPoint GetPoint(){ return m_pos; }
	IplImage* GetNowImage(){ return m_img; }
private:
	int m_speed;
	bool m_isDead;
	CvPoint m_pos;
	IplImage* m_img;
};

