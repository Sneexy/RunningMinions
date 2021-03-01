#include "stdafx.h"
#include "Enemy.h"


CEnemy::CEnemy()
{
	m_isDead = false;
	m_needWalking = false;
	m_walkLoop = 0;
}
CEnemy::CEnemy(IplImage* img, int posx, int posy, int backSpeed, bool ifwalk)
{
	m_img = img;
	m_pos.x = posx;
	m_pos.y = posy;
	m_isDead = false;
	m_speed = backSpeed;
	m_needWalking = ifwalk;
	m_walkingFlag[0] = m_walkingFlag[1] = m_walkingFlag[7] = m_walkingFlag[8] = m_speed;
	m_walkingFlag[2] = m_walkingFlag[3] = m_walkingFlag[5] = m_walkingFlag[6] = -m_speed;
	m_walkingFlag[4] = m_walkingFlag[9] = 0;
}

CEnemy::~CEnemy()
{
}


void CEnemy::Move()
{
	m_pos.x -= m_speed;
	if (m_pos.x + m_img->width < 0)m_isDead = true;
}


void CEnemy::Draw(IplImage* backImage)
{
	if (m_needWalking)
	{
		m_pos.x += m_walkingFlag[m_walkLoop % 10];
		m_walkLoop++;
	}
	int b, g, r, len;
	if (m_isDead)return;
	len = m_img->width;
	for (int j = 0; j < m_img->width; j++)
	{
		for (int i = 0; i < m_img->height; i++)
		{
			if (i + m_pos.y < 0 || i + m_pos.y >= backImage->height
				|| j + m_pos.x < 0 || j + m_pos.x >= backImage->width)continue;
			b = CV_IMAGE_ELEM(m_img, uchar, i, j * 3);
			g = CV_IMAGE_ELEM(m_img, uchar, i, j * 3 + 1);
			r = CV_IMAGE_ELEM(m_img, uchar, i, j * 3 + 2);
			if (b == 0 && g == 255 && r == 0)continue;
			CV_IMAGE_ELEM(backImage, uchar, i + m_pos.y, (j + m_pos.x) * 3) = b;
			CV_IMAGE_ELEM(backImage, uchar, i + m_pos.y, (j + m_pos.x) * 3 + 1) = g;
			CV_IMAGE_ELEM(backImage, uchar, i + m_pos.y, (j + m_pos.x) * 3 + 2) = r;
		}
	}
}
