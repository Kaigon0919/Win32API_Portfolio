#pragma once
#include "DungeonLevel.h"
class Player;
class PlayerBackGround;
class GameMouse;
class WarpObject;
class Stage3Level : public DungeonLevel
{
public:
	Stage3Level();
	~Stage3Level();
private:
	WarpObject * warp_BossStage;
	WarpObject * warp_Stage2;

public:
	virtual void Loading() override;
	virtual void LevelEnter() override;
	virtual void LevelExit() override;

	virtual void LevelUpdate() override;
	virtual void EndDebugUpdate() override;
};

