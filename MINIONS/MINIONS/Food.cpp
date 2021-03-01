#include "stdafx.h"
#include "Food.h"

CFood::CFood()
{
	m_isDead = false;
}
CFood::CFood(IplImage* img, int posx, int posy, int backSpeed)
{
	m_img = img;
	m_pos.x = posx;
	m_pos.y = posy;
	m_speed = backSpeed;
	m_isDead = false;
}
CFood::~CFood()
{
}

void CFood::Move()
{
	m_pos.x -= m_speed;
	if (m_pos.x + m_img->width < 0)m_isDead = true;
}


void CFood::Draw(IplImage* backImage)
{
	int b, g, r, len;
	if (m_isDead)return;
	len = m_img->width;
	for (int j = 0; j < m_img->width; j++)
	{
		for (int i = 0; i < m_img->height; i++)
		{
			if (i + m_pos.y < 0 || i + m_pos.y > backImage->height || j + m_pos.x < 0 || j + m_pos.x > backImage->width)continue;
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
