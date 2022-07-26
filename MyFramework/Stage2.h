#pragma once
#include "DungeonLevel.h"
class WarpObject;
class Stage2Level : public DungeonLevel
{
public:
	Stage2Level();
	~Stage2Level();
public:
	WarpObject * warp_Stage1;
	WarpObject * warp_Stage3;
public:
	virtual void Loading() override;
	virtual void LevelEnter() override;
	virtual void LevelExit() override;

	virtual void LevelUpdate() override;
	virtual void EndDebugUpdate() override;
};

