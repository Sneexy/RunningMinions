#include "stdafx.h"
#include "StartUI.h"


CStartUI::CStartUI()
{
	m_img = cvLoadImage(".\\resource\\startImage.jpg");
	m_img1 = cvLoadImage(".\\resource\\startImage1.jpg");
}


CStartUI::~CStartUI()
{
	cvReleaseImage(&m_img);
	cvReleaseImage(&m_img1);
}