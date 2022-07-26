#pragma once
#include "Level.h"
#include<set>
class Player;
class PlayerBackGround;
class GameMouse;
class Monster;
class DungeonLevel : public Level
{
public:
	DungeonLevel();
	~DungeonLevel();
protected:
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

protected:
	void MonsterSetPlayer(Player*const player);
	void MonsterRelease(Monster *const taget);
	void MonsterLoad(const wchar_t * fileName);
};

