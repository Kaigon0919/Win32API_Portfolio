#pragma once
#include "Actor.h"
#include<vector>
#include"TimeHelper.h"


class IsoMetricTileRenderer;
class SingleRenderer;
class Monster;
class EditTileMap :	public Actor
{
public:
	EditTileMap();
	~EditTileMap();
private:
	enum Mode
	{
		TileMode,
		MonsterMode,
		Max
	};
	struct EditMap
	{
		std::wstring stageName;
		std::wstring spriteName;
	};
public:
	IsoMetricTileRenderer* m_TileRender;
	SingleRenderer * m_BackBround;
	std::vector<EditMap> m_MapVector;
	int SelectTile;
	int SelectMonster;
	int SelectMap;

	std::set<Monster*> m_Monster;

	Mode m_Mode;
	TimeHelper initWatingTime;

public:
	virtual void Init();
	virtual void PrevUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void DebugRender();
	virtual void AfterRender()override;
private:
	void Save();
	void Load();
	void MonsterSave();
	void MonsterLoad();
	void MonsterClear();
};

