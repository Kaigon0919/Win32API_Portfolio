#pragma once
#include "Level.h"
#include<set>
class Player;
class PlayerBackGround;
class GameMouse;
class Monster5;
class Monster;
class TestLevel :public Level
{
public:
	TestLevel();
	~TestLevel();
	
private:
	Player* m_Player;
	PlayerBackGround* m_BackGround;
	GameMouse * m_GameMouse;

	std::set<Monster*> m_Monster;
public:
	virtual void Loading() override;
	virtual void LevelEnter() override;
	virtual void LevelExit() override;

	virtual void LevelUpdate() override;
	virtual void EndDebugUpdate() override;
};

