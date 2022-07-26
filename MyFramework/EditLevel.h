#pragma once
#include "Level.h"
class EditTileMap;
class EditLevel :	public Level
{
public:
	EditLevel();
	~EditLevel();
public:
	EditTileMap* m_TileMap;
public:
	virtual void Loading() override;
	virtual void LevelEnter() override;
	virtual void LevelExit() override;

	virtual void LevelUpdate() override;
	virtual void EndDebugUpdate() override;
};

