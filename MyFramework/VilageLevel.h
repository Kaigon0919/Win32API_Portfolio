#pragma once
#include "Level.h"

class Player;
class GameMouse;
class PlayerBackGround;
class VillageLevel : public Level
{
public:
	VillageLevel();
	~VillageLevel();

private:
	Player* m_Player;
	PlayerBackGround* m_BackGround;
	GameMouse * m_GameMouse;
public:
	virtual void Loading() override;
	virtual void LevelEnter() override;
	virtual void LevelExit() override;

	virtual void LevelUpdate() override;
	virtual void EndDebugUpdate() override;
};

