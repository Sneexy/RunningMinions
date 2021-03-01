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
////////////////������Ϸ���ܿ�����//////////////////////////////
class CGameManager
{
public:
	CGameManager();
	virtual ~CGameManager();
	enum GameState { GameStart, GameRunning, GameEnd };
	//��ʼ��
	void Start();
	void GameRunInit(int level);
	void Banana_Enemy_Barrier_Init();
	void Banana_Enemy_Barrier_Prop_Init();
	//��ɫ����
	void Run();
	void FoodUpdate();
	void PropUpdate();
	void EnemyUpdate();
	void BarrierUpdate();
	void MyPlayerUpdate();
	void Collider();
	//������ʾ
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
	vector<CFood*>m_prop;//����
	vector<CEnemy*>m_enemy;
	vector<CEnemy*>m_barrier;
	IplImage* m_whiteflag[5];

};