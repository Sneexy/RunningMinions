#pragma once
#include "cv.h"
#include"highgui.h"
////////小黄人的参数设定，行为函数/////////////
#define ROADHIGH 380
#define MAXHIGH 260
#define BACKWIDTH 800
#define BACKHEIGHT 600
#define SPEEDY 25
#define levelNum 10
class CMyPlayer
{
public:
	CMyPlayer();
	virtual ~CMyPlayer();
	void Init();
	void Jump();
	void Move();
	void ChangeLevel(int level);
	void Draw(IplImage* backImage);
	void Destroy(){ m_isClear = true; }
	int GetPosx(){ return m_posx; }
	int GetPosy(){ return m_posy; }
	bool needJumpUp;
	bool isDead(){ return m_isClear; }
	bool isJumping(){ return m_posy < ROADHIGH; }
	bool isPadowning(){ return m_isPadown; }
	IplImage* GetNowImage();
private:
	int m_posx;
	int m_posy;
	int m_level;
	int m_speed;
	int m_hunger;
	int m_showFlag;
	int m_relaMoveX;//相对位移速度
	int m_relaMoveY;
	int m_isPadown;
	bool m_isClear;
	IplImage* m_jumpImg;
	IplImage* m_imgs[levelNum];
};