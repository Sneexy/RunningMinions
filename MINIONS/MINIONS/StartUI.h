#pragma once
#include "cv.h"
#include"highgui.h"
////////��ʼ����///////////
class CStartUI
{
public:
	CStartUI();
	virtual ~CStartUI();
	void Show();
	IplImage* GetStartImage(){ return m_img; }
	IplImage* GetStart1Image(){ return m_img1; }
private:
	IplImage* m_img;
	IplImage* m_img1;
};