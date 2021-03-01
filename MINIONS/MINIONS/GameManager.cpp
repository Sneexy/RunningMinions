#include "stdafx.h"
#include "GameManager.h"


CGameManager::CGameManager()
{
	cvNamedWindow(m_WndName, 1);
	cvMoveWindow(m_WndName, 257, 52);
	m_whiteflag[1] = cvCloneImage(m_gameui.GetWhiteflag(1));
	m_whiteflag[2] = cvCloneImage(m_gameui.GetWhiteflag(2));
	m_whiteflag[3] = cvCloneImage(m_gameui.GetWhiteflag(3));
	Start();
}


CGameManager::~CGameManager()
{
	for (int i = 0; i < 3; i++)cvReleaseImage(&m_whiteflag[i]);
}


void CGameManager::Start()
{
	m_state = GameState::GameStart;
	cvShowImage(m_WndName, m_startui.GetStartImage());
	PlaySound(TEXT(".\\resource\\backMusic1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}


void CGameManager::Run()
{
	while (m_gameui.GetRealLenghth() < 5000)
	{
		cvWaitKey(18);
		switch (m_state)
		{
		case CGameManager::GameStart:
			if (GetAsyncKeyState('Q') & 0x8000)
			{
				cvShowImage(m_WndName, cvLoadImage(".\\resource\\startImage1.jpg"));
			}
			if (GetAsyncKeyState(' ') & 0x8000)
			{
				GameRunInit(1);//初始化参数
				PlaySound(TEXT(".\\resource\\backMusic2.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			}
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				return;
			}
			break;
		case CGameManager::GameRunning:
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)return;
			if (GetAsyncKeyState('Q') && 0x8000)ShowSigns(1);
			if (GetAsyncKeyState('B') && 0x8000)cvWaitKey();
			MyPlayerUpdate();
			FoodUpdate();
			EnemyUpdate();
			BarrierUpdate();
			PropUpdate();
			Collider();
			ShowScore();
			m_gameui.ShowNowImage(m_WndName);
			JudgeStartEnd();//检测专属于开始结束的事件
			break;
		case CGameManager::GameEnd:
			m_endui.DrawScore(m_score);
			cvShowImage(m_WndName, m_endui.GetEndImage());
			if (GetAsyncKeyState(VK_RETURN) & 0x8000)Start();
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)return;
			break;
		default:
			break;
		}
	}
}


void CGameManager::End()
{
	m_state = GameState::GameEnd;
}


void CGameManager::GameRunInit(int level)
{
	//改变程序运行状态
	m_state = GameState::GameRunning;

	//清除原来的player、香蕉、敌人、障碍物
	int i;
	m_myplayer.Init();
	for (i = 0; i < m_banana.size(); i++)
		delete m_banana[i];
	m_banana.clear();

	for (i = 0; i < m_enemy.size(); i++)
		delete m_enemy[i];
	m_enemy.clear();

	for (i = 0; i < m_barrier.size(); i++)
		delete m_barrier[i];
	m_barrier.clear();

	for (i = 0; i < m_prop.size(); i++)
		delete m_prop[i];
	m_prop.clear();


	//重置
	if (level == 1)Banana_Enemy_Barrier_Init();
	if (level == 2)Banana_Enemy_Barrier_Prop_Init();
	m_myplayer.Init();
	m_score = 0;
	m_backSpeed = m_gameui.GetBackSpeed();
	m_gameui.InitRealLength();
	m_level = level;
}


void CGameManager::Banana_Enemy_Barrier_Init()
{
	int b, g, r, i;
	for (int posx = 0; posx < 5000; posx++)
	{
		b = CV_IMAGE_ELEM(m_whiteflag[1], uchar, 0, posx * 3);
		g = CV_IMAGE_ELEM(m_whiteflag[1], uchar, 0, posx * 3 + 1);
		r = CV_IMAGE_ELEM(m_whiteflag[1], uchar, 0, posx * 3 + 2);
		//创建竖直香蕉
		if (r == 1 || r == 2)
		{
			for (i = 0; i < g; i++)
			{
				if (!b)b = -249;
				m_banana.push_back(new CFood(m_gameui.GetBananaImg(r - 1), posx + 42 * i, b + 250, m_gameui.GetBackSpeed()));
			}
		}
		//创建横躺香蕉
		if (r == 3 || r == 4)
		{
			for (i = 0; i < g; i++)
			{
				if (!b)b = -249;
				m_banana.push_back(new CFood(m_gameui.GetBananaImg(r - 1), posx, b + 42 * i + 250, m_gameui.GetBackSpeed()));
			}
		}
		//创建敌人
		if (r == 10 || r == 11)
		{
			m_enemy.push_back(new CEnemy(m_gameui.GetEnemyImg(r - 10), posx, b + 225, m_gameui.GetBackSpeed(), (bool)(g - 1)));
		}
		//创建障碍物
		if (r == 15 || r == 16)
		{
			for (i = 0; i < g; i++)
				m_barrier.push_back(new CEnemy(m_gameui.GetBarrierImg(r - 15), posx + 75 * i, b, m_gameui.GetBackSpeed(), false));
		}
	}
}


void CGameManager::Banana_Enemy_Barrier_Prop_Init()
{
	int b, g, r, i;
	for (int posx = 0; posx < 5000; posx++)
	{
		b = CV_IMAGE_ELEM(m_whiteflag[2], uchar, 0, posx * 3);
		g = CV_IMAGE_ELEM(m_whiteflag[2], uchar, 0, posx * 3 + 1);
		r = CV_IMAGE_ELEM(m_whiteflag[2], uchar, 0, posx * 3 + 2);
		//创建香蕉
		if (r == 1 || r == 2)
		{
			for (i = 0; i < g; i++)
			{
				if (!b)b = -249;
				m_banana.push_back(new CFood(m_gameui.GetBananaImg(r - 1), posx + 42 * i, b + 250, m_gameui.GetBackSpeed()));
			}
		}
		//创建香蕉
		if (r == 3 || r == 4)
		{
			for (i = 0; i < g; i++)
			{
				if (!b)b = -249;
				m_banana.push_back(new CFood(m_gameui.GetBananaImg(r - 1), posx, b + 42 * i + 250, m_gameui.GetBackSpeed()));
			}
		}
		//创建敌人
		if (r == 10 || r == 11)
		{
			m_enemy.push_back(new CEnemy(m_gameui.GetEnemyImg(r - 10), posx, b + 225, m_gameui.GetBackSpeed(), (bool)(g - 1)));
		}
		//创建障碍物
		if (r == 15 || r == 16)
		{
			for (i = 0; i < g; i++)
				m_barrier.push_back(new CEnemy(m_gameui.GetBarrierImg(r - 15), posx + 75 * i, b, m_gameui.GetBackSpeed(), false));
		}
		//创建道具
		if (r == 30 || r == 31)
		{
			m_prop.push_back(new CFood(m_gameui.GetPropImg(r - 30), posx, g * 225 + b, m_gameui.GetBackSpeed()));
		}
	}
}


void CGameManager::MyPlayerUpdate()
{
	cvWaitKey(15);
	m_myplayer.Move();
	m_myplayer.Draw(m_gameui.GetNowImage());
	if (m_myplayer.isDead())End();
}


void CGameManager::FoodUpdate()
{
	for (int i = 0; i < m_banana.size(); i++)
	{
		m_banana[i]->Move();
		if (m_banana[i]->GetPoint().x < 800)m_banana[i]->Draw(m_gameui.GetNowImage());
		if (m_banana[i]->NeedClear()) m_banana.erase(m_banana.begin() + i);
	}
}


void CGameManager::EnemyUpdate()
{
	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->Move();
		if (m_enemy[i]->GetPoint().x < 800)  m_enemy[i]->Draw(m_gameui.GetNowImage());
		if (m_enemy[i]->NeedClear())m_enemy.erase(m_enemy.begin() + i);
	}
}


void CGameManager::BarrierUpdate()
{
	for (int i = 0; i < m_barrier.size(); i++)
	{
		m_barrier[i]->Move();
		if (m_barrier[i]->GetPoint().x < 800)  m_barrier[i]->Draw(m_gameui.GetNowImage());
		if (m_barrier[i]->NeedClear())m_barrier.erase(m_barrier.begin() + i);
	}
}


void CGameManager::PropUpdate()
{
	for (int i = 0; i < m_prop.size(); i++)
	{
		m_prop[i]->Move();
		if (m_prop[i]->GetPoint().x < 800)m_prop[i]->Draw(m_gameui.GetNowImage());
		if (m_prop[i]->NeedClear()) m_prop.erase(m_prop.begin() + i);
	}
}


void CGameManager::Collider()//碰撞检测
{
	int i;
	//小黄人和香蕉的碰撞
	for (i = 0; i < m_banana.size(); i++)
	{
		int cx = m_banana[i]->GetPoint().x + m_banana[i]->GetNowImage()->width / 2;
		int cy = m_banana[i]->GetPoint().y + m_banana[i]->GetNowImage()->height / 2;
		int mx = m_myplayer.GetPosx() + m_myplayer.GetNowImage()->width / 2;
		int my = m_myplayer.GetPosy() + m_myplayer.GetNowImage()->height / 2;

		if (abs(mx - cx) < m_myplayer.GetNowImage()->width / 2 + m_banana[i]->GetNowImage()->width / 2 &&
			abs(my - cy) < m_myplayer.GetNowImage()->height / 2 + m_banana[i]->GetNowImage()->height / 2)
		{
			m_score += 50;
			m_banana.erase(m_banana.begin() + i);
		}
	}


	//小黄人和丑丑的敌人的碰撞
	for (i = 0; i < m_enemy.size(); i++)
	{
		int cx = m_enemy[i]->GetPoint().x + m_enemy[i]->GetNowImage()->width / 2;
		int cy = m_enemy[i]->GetPoint().y + m_enemy[i]->GetNowImage()->height / 2;
		int mx = m_myplayer.GetPosx() + m_myplayer.GetNowImage()->width / 2;
		int my = m_myplayer.GetPosy() + m_myplayer.GetNowImage()->height / 2;
		if (abs(mx - cx) < m_myplayer.GetNowImage()->width / 2 + m_enemy[i]->GetNowImage()->width / 2 &&
			abs(my - cy) < m_myplayer.GetNowImage()->height / 2 + m_enemy[i]->GetNowImage()->height / 2)
		{
			if (m_myplayer.isJumping())
			{
				m_score += 20;
				m_enemy.erase(m_enemy.begin() + i);
			}
			else m_myplayer.Destroy();
		}
	}

	//小黄人和障碍物的碰撞
	for (i = 0; i < m_barrier.size() && !m_myplayer.isPadowning(); i++)
	{
		int cx = m_barrier[i]->GetPoint().x + m_barrier[i]->GetNowImage()->width / 2;
		int cy = m_barrier[i]->GetPoint().y + m_barrier[i]->GetNowImage()->height / 2;
		int mx = m_myplayer.GetPosx() + m_myplayer.GetNowImage()->width / 2;
		int my = m_myplayer.GetPosy() + m_myplayer.GetNowImage()->height / 2;
		if (abs(mx - cx) < m_myplayer.GetNowImage()->width / 2 + m_barrier[i]->GetNowImage()->width / 2 &&
			abs(my - cy) < m_myplayer.GetNowImage()->height / 2 + m_barrier[i]->GetNowImage()->height / 2)
		{
			m_myplayer.Destroy();
		}
	}
	//小黄人和道具的碰撞
	for (i = 0; i < m_prop.size() && !m_myplayer.isPadowning(); i++)
	{
		int cx = m_prop[i]->GetPoint().x + m_prop[i]->GetNowImage()->width / 2;
		int cy = m_prop[i]->GetPoint().y + m_prop[i]->GetNowImage()->height / 2;
		int mx = m_myplayer.GetPosx() + m_myplayer.GetNowImage()->width / 2;
		int my = m_myplayer.GetPosy() + m_myplayer.GetNowImage()->height / 2;
		if (abs(mx - cx) < m_myplayer.GetNowImage()->width / 2 + m_prop[i]->GetNowImage()->width / 2 &&
			abs(my - cy) < m_myplayer.GetNowImage()->height / 2 + m_prop[i]->GetNowImage()->height / 2)
		{
			//判断是什么道具
			if (m_prop[i]->GetWidth() == 158)//加分的马里奥
			{
				m_score += 400;
				m_prop.erase(m_prop.begin());//帮忙摘到香蕉的蝴蝶
			}
			else if (m_prop[i]->GetWidth() == 111)
			{
				m_prop.erase(m_prop.begin());
				m_banana.erase(m_banana.begin());
				m_banana.erase(m_banana.begin());
				m_banana.erase(m_banana.begin());
				m_score += 150;
			}
		}
	}
}


void CGameManager::ShowSigns(int index)
{
	if (index == 1)m_gameui.DrawSigns(0, 100, 1);
}


void CGameManager::ShowScore()
{
	m_gameui.ShowScore(m_score, 300, 550, true);
}


void CGameManager::JudgeStartEnd()//衔接开始结束
{
	if (m_gameui.GetRealLenghth()<200 && m_level == 2)
	{
		m_gameui.ShowLevelStart();
	}
	if (m_level == 1)
	{
		if (m_gameui.GetRealLenghth() > 4900)GameRunInit(2);
		else if (m_gameui.GetRealLenghth() > 4700)m_gameui.ShowLevelEnd(m_score);
	}
	else if (m_level == 2)
	{
		if (m_gameui.GetRealLenghth() > 4300)End();
		else if (m_gameui.GetRealLenghth() > 4100)m_gameui.ShowLevelEnd(m_score);
	}
}