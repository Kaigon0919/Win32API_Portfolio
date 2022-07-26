#include "stdafx.h"
#include "EditTilemap.h"
#include"Render.h"
#include"Level.h"
#include"OFStream.h"
#include"IFStream.h"
#include"Monster.h"

EditTileMap::EditTileMap() : m_BackBround(nullptr), m_TileRender(nullptr), SelectMap(0), SelectTile(0), initWatingTime(0.5f), m_Mode(TileMode), SelectMonster(0)
{
}


EditTileMap::~EditTileMap()
{
}

void EditTileMap::Init()
{
	SelectTile = 0;
	SelectMap = 0;

	m_MapVector.push_back({ L"Village",L"map01.bmp" });
	m_MapVector.push_back({ L"Village2",L"map02.bmp" });
	m_MapVector.push_back({ L"ItemShop",L"ItemShop.bmp" });
	m_MapVector.push_back({ L"Field",L"Field.bmp" });
	m_MapVector.push_back({ L"Stage1",L"Dungeon.bmp" });
	m_MapVector.push_back({ L"Stage2",L"Dungeon.bmp" });
	m_MapVector.push_back({ L"Stage3",L"Dungeon.bmp" });
	m_MapVector.push_back({ L"Boss",L"Boss.bmp" });

	m_TileRender = CreateRenderer<IsoMetricTileRenderer>(-4);
	m_TileRender->CreateMap(L"Tile01", Vector2f(64.0f, 32.0f));

	m_BackBround = CreateRenderer<SingleRenderer>(-5);
	m_BackBround->SettingSprite(m_MapVector[SelectMap].spriteName.c_str());

	Load();
	MonsterLoad();

}

void EditTileMap::PrevUpdate()
{
}

void EditTileMap::Update()
{
	if (initWatingTime.Check() != true)
	{
		return;
	}
	if (m_Mode == TileMode)
	{
		if (true == InputManager::Instance().IsPressed(L"LMouse"))
		{
			m_TileRender->ScreenPosSetTile(InputManager::Instance().GetMousePos(), SelectTile);
		}
		if (true == InputManager::Instance().IsPressed(L"RMouse"))
		{
			m_TileRender->ScreenPosDeleteTile(InputManager::Instance().GetMousePos());
		}
		if (InputManager::Instance().IsUnPressed(L"MapPrev") && InputManager::Instance().IsUnPressed(L"MapNext"))
		{
			if (InputManager::Instance().IsDown(L"TilePrev"))
			{
				--SelectTile;
				if (SelectTile < 0)
				{
					SelectTile = 0;
				}
			}
			if (InputManager::Instance().IsDown(L"TileNext"))
			{
				size_t max = m_TileRender->GetTileStateCount();
				++SelectTile;
				if (SelectTile >= max)
				{
					SelectTile = (int)max - 1;
				}
			}
		}

		if (InputManager::Instance().IsDown(L"Clear"))
		{
			m_TileRender->Reset();
		}
	}
	else if (m_Mode == MonsterMode)
	{
		if (true == InputManager::Instance().IsDown(L"LMouse"))
		{
			Monster * Temp = GetLevel()->CreateActor<Monster>(GetLevel()->GetMouseConvertPosition());
			Temp->InitStateSetting((Monster::MonsterType)SelectMonster);
			m_Monster.insert(Temp);
		}
		if (true == InputManager::Instance().IsDown(L"RMouse"))
		{

		}
		if (InputManager::Instance().IsUnPressed(L"MapPrev") && InputManager::Instance().IsUnPressed(L"MapNext"))
		{
			if (InputManager::Instance().IsDown(L"TilePrev"))
			{
				--SelectMonster;
				if (SelectMonster < 0)
				{
					SelectMonster = 0;
				}
			}
			if (InputManager::Instance().IsDown(L"TileNext"))
			{
				++SelectMonster;
				if (SelectMonster >= Monster::MonsterType::Max)
				{
					SelectMonster = Monster::MonsterType::Max - 1;
				}
			}
		}
		if (InputManager::Instance().IsDown(L"Clear"))
		{
			MonsterClear();
		}
	}
	if (InputManager::Instance().IsDown(L"MapPrev"))
	{
		--SelectMap;
		if (SelectMap < 0)
		{
			SelectMap = 0;
		}
		Load();
		MonsterLoad();
		m_BackBround->SettingSprite(m_MapVector[SelectMap].spriteName.c_str());
		initWatingTime.Reset();
	}
	if (InputManager::Instance().IsDown(L"MapNext"))
	{
		++SelectMap;
		if (SelectMap >= m_MapVector.size())
		{
			--SelectMap;
		}
		Load();
		MonsterLoad();
		m_BackBround->SettingSprite(m_MapVector[SelectMap].spriteName.c_str());
		initWatingTime.Reset();
	}
	if (InputManager::Instance().IsPressed(L"Up"))
	{
		Vector2f camera = GetLevel()->GetCameraPosition();
		camera += Vector2f::up;
		GetLevel()->SetCameraPosition(camera);
	}
	if (InputManager::Instance().IsPressed(L"Down") && InputManager::Instance().IsUnPressed(L"Save"))
	{
		Vector2f camera = GetLevel()->GetCameraPosition();
		camera += Vector2f::down;
		GetLevel()->SetCameraPosition(camera);
	}
	if (InputManager::Instance().IsPressed(L"Left"))
	{
		Vector2f camera = GetLevel()->GetCameraPosition();
		camera += Vector2f::left;
		GetLevel()->SetCameraPosition(camera);
	}
	if (InputManager::Instance().IsPressed(L"Right"))
	{
		Vector2f camera = GetLevel()->GetCameraPosition();
		camera += Vector2f::right;
		GetLevel()->SetCameraPosition(camera);
	}


	if (InputManager::Instance().IsDown(L"Save"))
	{
		Save();
		MonsterSave();
	}
	if (InputManager::Instance().IsDown(L"Load"))
	{
		Load();
		MonsterSave();
	}
	if (InputManager::Instance().IsDown(L"ChangeMode"))
	{
		m_Mode = (Mode)(m_Mode + 1);
		if (m_Mode == Mode::Max)
		{
			m_Mode = (Mode)0;
		}
	}
}

void EditTileMap::LateUpdate()
{

}

void EditTileMap::DebugRender()
{

}

void EditTileMap::AfterRender()
{
	wchar_t str[1024];

	swprintf_s(str, L"Level Name : %s", m_MapVector[SelectMap].stageName.c_str());
	TextOut(ResourceManager::Instance().GetBackBuffer(), 500, 60, str, lstrlen(str));
	if (m_Mode == TileMode)
	{
		swprintf_s(str, L"Mode : TileMode");
		TextOut(ResourceManager::Instance().GetBackBuffer(), 500, 80, str, lstrlen(str));
		swprintf_s(str, L"Select Tile : %d, Map : %d", SelectTile, SelectMap);
		TextOut(ResourceManager::Instance().GetBackBuffer(), 500, 100, str, lstrlen(str));
		swprintf_s(str, L"Tile Count : %d", (int)m_TileRender->GetTileCount());
		TextOut(ResourceManager::Instance().GetBackBuffer(), 500, 120, str, lstrlen(str));
	}
	else if (m_Mode == MonsterMode)
	{
		swprintf_s(str, L"Mode : MonsterMode");
		TextOut(ResourceManager::Instance().GetBackBuffer(), 500, 80, str, lstrlen(str));
		swprintf_s(str, L"Monster Type : %s", Monster::MonsterTypeName((Monster::MonsterType)SelectMonster));
		TextOut(ResourceManager::Instance().GetBackBuffer(), 500, 100, str, lstrlen(str));
		swprintf_s(str, L"Monster Count : %d", (int)m_Monster.size());
		TextOut(ResourceManager::Instance().GetBackBuffer(), 500, 120, str, lstrlen(str));
	}
}

void EditTileMap::Save()
{
	size_t tileCount = m_TileRender->GetTileCount();

	IsoMetricTileRenderer::OutputTileData* SaveTile = new IsoMetricTileRenderer::OutputTileData[tileCount];
	m_TileRender->GetAllTileData(SaveTile, (int)tileCount);

	std::wstring filePath = m_MapVector[SelectMap].stageName;
	std::wstring fileName = filePath + L".mtd";

	std::wstring path = ResourceManager::Instance().FindPath(L"MapData");
	path += fileName;

	OFStream os = OFStream(path.c_str());
	os.Write(&tileCount, sizeof(size_t));
	os.Write(SaveTile, sizeof(IsoMetricTileRenderer::OutputTileData) * (int)tileCount);

	delete[] SaveTile;
}

void EditTileMap::Load()
{
	m_TileRender->Reset();

	std::wstring filePath = m_MapVector[SelectMap].stageName;
	std::wstring path = ResourceManager::Instance().FindPath(L"MapData");
	std::wstring fileName = filePath + L".mtd";
	path += fileName;

	IFStream is = IFStream(path.c_str());

	if (!is.IsOpen())
	{
		Save();
		is.ReOpen(path.c_str());
	}

	size_t count = 0;

	is.Read(&count, sizeof(size_t), sizeof(size_t));
	IsoMetricTileRenderer::OutputTileData* LoadTile = new IsoMetricTileRenderer::OutputTileData[count];

	is.Read(LoadTile, sizeof(IsoMetricTileRenderer::OutputTileData)*(int)count, sizeof(IsoMetricTileRenderer::OutputTileData)*(int)count);

	for (size_t i = 0; i < count; ++i)
	{
		IsoMetricTileRenderer::OutputTileData readData = LoadTile[i];
		m_TileRender->SetTile(LoadTile[i]._index, LoadTile[i]._data.SpriteIndex);
	}

	delete[] LoadTile;
}

void EditTileMap::MonsterSave()
{
	std::wstring filePath = m_MapVector[SelectMap].stageName;

	std::wstring fileName = filePath + L".md";

	std::wstring path = ResourceManager::Instance().FindPath(L"Data");
	path += fileName;

	OFStream os = OFStream(path.c_str());

	size_t monsterCount = m_Monster.size();
	os.Write(&monsterCount, sizeof(size_t));

	std::set<Monster*>::iterator itStart = m_Monster.begin();
	std::set<Monster*>::iterator itEnd = m_Monster.end();
	for (; itStart != itEnd; ++itStart)
	{
		Monster::OutputMonsterData outData;
		outData._type = (*itStart)->GetMonsterType();
		outData._position = (*itStart)->GetPosition();
		os.Write(&outData, sizeof(Monster::OutputMonsterData));
	}
}

void EditTileMap::MonsterLoad()
{
	MonsterClear();

	std::wstring filePath = m_MapVector[SelectMap].stageName;
	std::wstring path = ResourceManager::Instance().FindPath(L"Data");
	std::wstring fileName = filePath + L".md";
	path += fileName;

	IFStream is = IFStream(path.c_str());

	if (!is.IsOpen())
	{
		MonsterSave();
		is.ReOpen(path.c_str());
	}

	size_t count = 0;
	is.Read(&count, sizeof(size_t), sizeof(size_t));
	for (size_t i = 0; i < count; ++i)
	{
		Monster::OutputMonsterData readData;
		is.Read(&readData, sizeof(Monster::OutputMonsterData), sizeof(Monster::OutputMonsterData));
		Monster* Temp = GetLevel()->CreateActor<Monster>(readData._position);
		Temp->InitStateSetting(readData._type);
		m_Monster.insert(Temp);
	}
}

void EditTileMap::MonsterClear()
{
	std::set<Monster*>::iterator itStart = m_Monster.begin();
	std::set<Monster*>::iterator itEnd = m_Monster.end();
	for (; itStart != itEnd; ++itStart)
	{
		(*itStart)->Death();
	}
	m_Monster.clear();
}
