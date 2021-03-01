#include "stdafx.h"
#include "MyPlayer.h"
#define ROADHIGH 380
#define MAXHIGH 260
#define BACKWIDTH 800
#define BACKHEIGHT 600
#define SPEEDY 25


CMyPlayer::CMyPlayer()
{
	m_imgs[0] = cvLoadImage(".\\resource\\run\\run0.png");
	m_imgs[1] = cvLoadImage(".\\resource\\run\\run1.png");
	m_imgs[2] = cvLoadImage(".\\resource\\run\\run2.png");
	m_imgs[3] = cvLoadImage(".\\resource\\run\\run3.png");
	m_imgs[4] = cvLoadImage(".\\resource\\run\\run4.png");
	m_imgs[5] = cvLoadImage(".\\resource\\run\\run5.png");
	m_imgs[6] = cvLoadImage(".\\resource\\run\\run6.png");
	m_imgs[7] = cvLoadImage(".\\resource\\run\\run7.png");
	m_imgs[8] = cvLoadImage(".\\resource\\jump.png");
	m_imgs[9] = cvLoadImage(".\\resource\\padown.png");
	Init();//数据初始化

}


CMyPlayer::~CMyPlayer()
{
	for (int i = 0; i < 8; i++)
		cvReleaseImage(&m_imgs[i]);
	cvReleaseImage(&m_jumpImg);
}


void CMyPlayer::Init()
{
	m_speed = 5;
	m_hunger = 0;
	m_posy = ROADHIGH;
	m_posx = 200;
	m_showFlag = 0;
	ChangeLevel(0);
	m_relaMoveX = 0;
	m_relaMoveY = 0;
	m_isClear = false;
	needJumpUp = false;
	m_isPadown = false;
}


IplImage* CMyPlayer::GetNowImage()
{
	return m_imgs[m_showFlag];
	if (m_posy < ROADHIGH)return m_jumpImg;

}


void CMyPlayer::Draw(IplImage* backImage)
{
	int b, g, r;
	if (m_posy < ROADHIGH)m_showFlag = 8;
	if (m_isPadown)m_showFlag = 9;
	for (int i = 0; i < m_imgs[m_showFlag]->height; i++)
	{
		for (int j = 0; j < m_imgs[m_showFlag]->width; j++)
		{
			b = CV_IMAGE_ELEM(m_imgs[m_showFlag], uchar, i, j * 3);
			g = CV_IMAGE_ELEM(m_imgs[m_showFlag], uchar, i, j * 3 + 1);
			r = CV_IMAGE_ELEM(m_imgs[m_showFlag], uchar, i, j * 3 + 2);
			if (b == 0 && g == 255 && r == 0)continue;
			CV_IMAGE_ELEM(backImage, uchar, i + m_posy, (j + m_posx) * 3) = b;
			CV_IMAGE_ELEM(backImage, uchar, i + m_posy, (j + m_posx) * 3 + 1) = g;
			CV_IMAGE_ELEM(backImage, uchar, i + m_posy, (j + m_posx) * 3 + 2) = r;
		}
	}
	m_showFlag = (m_showFlag + 1) % 8;
}


void CMyPlayer::Move()
{
	if (m_posy < ROADHIGH)
	{
		Jump();
		return;
	}
	//相对速度,保持水平方向位置稳定
	m_posx += m_relaMoveX;
	if (m_posx < 198 && m_posy == ROADHIGH)m_relaMoveX = 2;
	else if (m_posx > 202 && m_posy == ROADHIGH)m_relaMoveX = -2;
	else m_relaMoveX = 0;
	//解除趴下的动作
	m_isPadown = false;
	//移动
	if (GetAsyncKeyState('A') && 0x8000 && m_posx - m_speed >= 10)
		m_posx -= m_speed;
	if (GetAsyncKeyState('D') && 0x8000 && m_posx + m_imgs[m_level]->width + m_speed <= BACKWIDTH - 10)
		m_posx += m_speed;
	if (GetAsyncKeyState('W') && 0x8000 && m_posy - m_speed >= MAXHIGH)
	{
		needJumpUp = true;
		Jump();
	}
	if (GetAsyncKeyState('S') && 0x8000 && m_posy + m_imgs[m_level]->height + m_speed <= BACKHEIGHT)
	{
		m_posx += m_speed;
		m_isPadown = true;
	}
}


void CMyPlayer::Jump()
{
	if (needJumpUp)m_posy -= SPEEDY;
	if (!needJumpUp)m_posy += SPEEDY;
	if (m_posy < MAXHIGH)needJumpUp = false;
	if (m_posy > ROADHIGH)m_posy = ROADHIGH;
	m_posx += m_relaMoveX;
}

void CMyPlayer::ChangeLevel(int level)
{
	m_level = level;
}