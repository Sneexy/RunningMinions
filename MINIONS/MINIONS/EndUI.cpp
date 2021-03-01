#include "stdafx.h"
#include "EndUI.h"


CEndUI::CEndUI()
{
	m_img = cvLoadImage(".\\resource\\endImage.jpg");
	m_nums[0] = cvLoadImage(".\\resource\\nums\\0.png");
	m_nums[1] = cvLoadImage(".\\resource\\nums\\1.png");
	m_nums[2] = cvLoadImage(".\\resource\\nums\\2.png");
	m_nums[3] = cvLoadImage(".\\resource\\nums\\3.png");
	m_nums[4] = cvLoadImage(".\\resource\\nums\\4.png");
	m_nums[5] = cvLoadImage(".\\resource\\nums\\5.png");
	m_nums[6] = cvLoadImage(".\\resource\\nums\\6.png");
	m_nums[7] = cvLoadImage(".\\resource\\nums\\7.png");
	m_nums[8] = cvLoadImage(".\\resource\\nums\\8.png");
	m_nums[9] = cvLoadImage(".\\resource\\nums\\9.png");
}


CEndUI::~CEndUI()
{
}


void CEndUI::DrawScore(int score)
{
	int arr[10], index = 0, len = 0, px = 562, py = 210;
	int r, g, b;
	//将分数值逆置存入arr数组，避免末尾0的影响
	if (score != 0)
	{
		while (score)
		{
			arr[len++] = score % 10;
			score /= 10;
		}
	}
	else arr[len++] = 0;

	//显示分数
	for (int k = len - 1; k >= 0; k--)
	{
		for (int i = 0; i < m_nums[arr[k]]->height; i++)
		{
			for (int j = 0; j < m_nums[arr[k]]->width; j++)
			{
				int b = CV_IMAGE_ELEM(m_nums[arr[k]], uchar, i, j * 3);
				int g = CV_IMAGE_ELEM(m_nums[arr[k]], uchar, i, j * 3 + 1);
				int r = CV_IMAGE_ELEM(m_nums[arr[k]], uchar, i, j * 3 + 2);

				CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3) = b;
				CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3 + 1) = g;
				CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3 + 2) = r;
			}
		}
		px += m_nums[arr[k]]->width;
	}
}
