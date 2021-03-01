#include "stdafx.h"
#include "GameUI.h"

CGameUI::CGameUI()
{
	m_speed = 7;
	m_length = 0;
	m_realLength = 0;
	m_roadHigh = 380;
	m_img = cvLoadImage(".\\resource\\backImg.jpg");
	m_clone = cvCloneImage(m_img);
	m_banana[0] = cvLoadImage(".\\resource\\banana0.png");
	m_banana[1] = cvLoadImage(".\\resource\\banana1.png");
	m_banana[2] = cvLoadImage(".\\resource\\banana2.png");
	m_banana[3] = cvLoadImage(".\\resource\\banana3.png");
	m_banana[4] = cvLoadImage(".\\resource\\bigbanana.jpg");
	m_enemy[0] = cvLoadImage(".\\resource\\enemy0.png");
	m_enemy[1] = cvLoadImage(".\\resource\\enemy1.png");
	m_barrier[0] = cvLoadImage(".\\resource\\barrier0.png");
	m_barrier[1] = cvLoadImage(".\\resource\\barrier1.png");
	m_sign[0] = cvLoadImage(".\\resource\\sign0.tif");
	m_sign[1] = cvLoadImage(".\\resource\\sign1.tif");
	m_sign[2] = cvLoadImage(".\\resource\\sign2.tif");
	m_whiteflag[0] = cvLoadImage(".\\resource\\whiteflag1.tif");
	m_whiteflag[1] = cvLoadImage(".\\resource\\whiteflag2.tif");
	m_whiteflag[2] = cvLoadImage(".\\resource\\whiteflag3.tif");
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
	m_score_letter = cvLoadImage(".\\resource\\score.png");
	m_prop[0] = cvLoadImage(".\\resource\\prop0.png");
	m_prop[1] = cvLoadImage(".\\resource\\prop1.png");
}


CGameUI::~CGameUI()
{
	cvReleaseImage(&m_img);
	cvReleaseImage(&m_clone);
	cvReleaseImage(&m_score_letter);
	int i;
	for (i = 0; i < 5; i++)cvReleaseImage(&m_banana[i]);
	for (i = 0; i < 2; i++)cvReleaseImage(&m_enemy[i]);
	for (i = 0; i < 2; i++)cvReleaseImage(&m_barrier[i]);
	for (i = 0; i < 3; i++)cvReleaseImage(&m_sign[i]);
	for (i = 0; i < 3; i++)cvReleaseImage(&m_whiteflag[i]);
	for (i = 0; i < 10; i++)cvReleaseImage(&m_nums[i]);
	for (i = 0; i < 2; i++)cvReleaseImage(&m_prop[i]);
}


void CGameUI::ShowNowImage(char* WndName)
{
	cvShowImage(WndName, m_img);
	SetBackImage();
}


void CGameUI::SetBackImage()
{
	//滚动
	m_realLength += m_speed;
	m_length = (m_realLength + m_clone->width) % m_clone->width;
	for (int x = 0; x < m_clone->width; x++)
	{
		int tx = (x + m_length + m_clone->width) % m_clone->width;
		for (int y = 0; y < m_clone->height; y++)
		{
			CV_IMAGE_ELEM(m_img, uchar, y, x * 3) = CV_IMAGE_ELEM(m_clone, uchar, y, tx * 3);
			CV_IMAGE_ELEM(m_img, uchar, y, x * 3 + 1) = CV_IMAGE_ELEM(m_clone, uchar, y, tx * 3 + 1);
			CV_IMAGE_ELEM(m_img, uchar, y, x * 3 + 2) = CV_IMAGE_ELEM(m_clone, uchar, y, tx * 3 + 2);
		}
	}
}


void CGameUI::ShowLevelStart()
{
	IplImage* sign = m_sign[2];
	int b, g, r, px = 230, py = 190;
	for (int j = 0; j < sign->width; j++)
	{
		for (int i = 0; i < sign->height; i++)
		{
			b = CV_IMAGE_ELEM(sign, uchar, i, j * 3);
			g = CV_IMAGE_ELEM(sign, uchar, i, j * 3 + 1);
			r = CV_IMAGE_ELEM(sign, uchar, i, j * 3 + 2);

			if (b == 0 && g == 0 && r == 0)continue;

			CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3) = b;
			CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3 + 1) = g;
			CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3 + 2) = r;
		}
	}
}


void CGameUI::ShowLevelEnd(int score)
{
	IplImage* sign = m_sign[1];
	int b, g, r, px = 230, py = 190;
	for (int j = 0; j < sign->width; j++)
	{
		for (int i = 0; i < sign->height; i++)
		{
			b = CV_IMAGE_ELEM(sign, uchar, i, j * 3);
			g = CV_IMAGE_ELEM(sign, uchar, i, j * 3 + 1);
			r = CV_IMAGE_ELEM(sign, uchar, i, j * 3 + 2);

			if (b == 0 && g == 0 && r == 0)continue;

			CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3) = b;
			CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3 + 1) = g;
			CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3 + 2) = r;
		}
	}
	ShowScore(score, 450, 275, false);
}


void CGameUI::ShowScore(int score, int px, int py, bool ex)
{//ex-是否添加前面的score字母
	int arr[10], index = 0, len = 0;
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

	//显示分数前的score图片
	if (ex)
	for (int j = 0; j < m_score_letter->width; j++)
	{
		for (int i = 0; i < m_score_letter->height; i++)
		{
			b = CV_IMAGE_ELEM(m_score_letter, uchar, i, j * 3);
			g = CV_IMAGE_ELEM(m_score_letter, uchar, i, j * 3 + 1);
			r = CV_IMAGE_ELEM(m_score_letter, uchar, i, j * 3 + 2);

			if (b == 0 && g == 0 && r == 0)continue;

			CV_IMAGE_ELEM(m_img, uchar, i + py + 1, (j + px - 85) * 3) = b;
			CV_IMAGE_ELEM(m_img, uchar, i + py + 1, (j + px - 85) * 3 + 1) = g;
			CV_IMAGE_ELEM(m_img, uchar, i + py + 1, (j + px - 85) * 3 + 2) = r;
		}
	}

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


void CGameUI::DrawSigns(int index, int px, int py)
{
	IplImage* sign = m_sign[index];
	int b, g, r;
	for (int j = 0; j < sign->width; j++)
	{
		for (int i = 0; i < sign->height; i++)
		{
			b = CV_IMAGE_ELEM(sign, uchar, i, j * 3);
			g = CV_IMAGE_ELEM(sign, uchar, i, j * 3 + 1);
			r = CV_IMAGE_ELEM(sign, uchar, i, j * 3 + 2);

			if (b == 0 && g == 0 && r == 0)continue;

			CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3) = b;
			CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3 + 1) = g;
			CV_IMAGE_ELEM(m_img, uchar, i + py, (j + px) * 3 + 2) = r;
		}
	}
}