#pragma once
#include "cv.h"
#include"highgui.h"
////////////��ʾ��������//////////////////
class CEndUI
{
public:
	CEndUI();
	virtual ~CEndUI();
	void DrawScore(int score);
	IplImage* GetEndImage(){ return m_img; }
private:
	IplImage* m_img;
	IplImage* m_nums[10];
};

