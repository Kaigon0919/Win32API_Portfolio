#pragma once
#include "Level.h"
#include"TimeHelper.h"
class TitleMain;
class GameMouse;
class TitleLevel :	public Level
{
public:
	TitleLevel();
	~TitleLevel();

	GameMouse* m_Mouse;
	TitleMain* m_Main;
public:
	virtual void Loading() override;
	virtual void LevelEnter() override;
	virtual void LevelExit() override;

	virtual void LevelUpdate() override;
	virtual void EndDebugUpdate() override;
};

