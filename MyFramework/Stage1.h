#pragma once
#include "DungeonLevel.h"
class WarpObject;
class Stage1Level :	public DungeonLevel
{
public:
	Stage1Level();
	~Stage1Level();
private:
	WarpObject * warp_Village;
	WarpObject * warp_Stage2;

public:
	virtual void Loading() override;
	virtual void LevelEnter() override;
	virtual void LevelExit() override;

	virtual void LevelUpdate() override;
	virtual void EndDebugUpdate() override;
};

