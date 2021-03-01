#pragma once
#include <vector>
#include "cv.h"
#include "highgui.h"
#include "Food.h"
#include "EndUI.h"
#include "Enemy.h"
#include "GameUI.h"
#include "GameUI.h"
#include "StartUI.h"
#include "MyPlayer.h"
using namespace std;
////////////////整个游戏的总控制类//////////////////////////////
class CGameManager
{
public:
	CGameManager();
	virtual ~CGameManager();
	enum GameState { GameStart, GameRunning, GameEnd };
	//初始化
	void Start();
	void GameRunInit(int level);
	void Banana_Enemy_Barrier_Init();
	void Banana_Enemy_Barrier_Prop_Init();
	//角色更新
	void Run();
	void FoodUpdate();
	void PropUpdate();
	void EnemyUpdate();
	void BarrierUpdate();
	void MyPlayerUpdate();
	void Collider();
	//界面显示
	void ShowScore();
	void ShowSigns(int index);
	int GetNowScore(){ return m_score; }
	void JudgeStartEnd();
	void End();
private:
	int m_level;
	int m_backSpeed;
	unsigned int m_score;
	int m_backImageWidth;
	int m_backImageHeight;
	int m_fastclearbanana;
	char *m_WndName = "MINIONS";
	CEndUI m_endui;
	CGameUI m_gameui;
	GameState m_state;
	CStartUI m_startui;
	CMyPlayer m_myplayer;
	vector<CFood*>m_banana;
	vector<CFood*>m_prop;//道具
	vector<CEnemy*>m_enemy;
	vector<CEnemy*>m_barrier;
	IplImage* m_whiteflag[5];

};