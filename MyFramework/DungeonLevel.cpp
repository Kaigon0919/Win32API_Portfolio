#include "stdafx.h"
#include "DungeonLevel.h"
#include"Player.h"
#include"PlayerBackGround.h"
#include"GameMouse.h"
#include"Monster.h"
#include"IFStream.h"
DungeonLevel::DungeonLevel()
{
}


DungeonLevel::~DungeonLevel()
{
}

void DungeonLevel::Loading()
{
	YSortOn(0);
	SetBackBufferColor(RGB(6, 7, 13));
	m_BackGround = CreateActor<PlayerBackGround>();

	// BackGround Setting.
	m_BackGround->SetSprite(L"Dungeon.bmp");
	m_BackGround->Load(L"Dungeon.mtd");

	ColLink(L"MouseCol", L"Monster");
	ColLink(L"MouseCol", L"Warp");
	ColLink(L"Arrow", L"Player");
	ColLink(L"Arrow", L"Monster");
}

void DungeonLevel::LevelEnter()
{
	m_Player = (Player*)FindActor(L"Player");
	if (m_Player)
	{
		// player Setting.
		m_Player->SetBackGound(m_BackGround);
		m_Player->SetBattleMode(true);
		m_Player->SetBackSound(L"DungeonBGM.mp3");
		m_Player->SetMonsters(&m_Monster);
	}

	m_GameMouse = (GameMouse*)FindActor(L"GameMouse");
	if (m_GameMouse)
	{
		m_GameMouse->SetPlayer(m_Player);
	}
	m_GameMouse->WatingTimeReset();

	std::set<Monster*>::iterator itSetMonstStart = m_Monster.begin();
	std::set<Monster*>::iterator itSetMonstEnd = m_Monster.end();

	for (; itSetMonstStart != itSetMonstEnd; ++itSetMonstStart)
	{
		(*itSetMonstStart)->SetPlayer(m_Player);
	}
}

void DungeonLevel::LevelExit()
{
	m_Player->SetMonsters(nullptr);
}

void DungeonLevel::LevelUpdate()
{

#ifdef  _DEBUG
	if (InputManager::Instance().IsDown(L"Exit"))
	{
		PostMessage(SystemClass::Instance().GetHWND(), WM_CLOSE, 0, 0);
	}
	if (InputManager::Instance().IsDown(L"LevelPrev"))
	{
		SystemClass::Instance().ChangeLevel((ALLSTATE)((int)SystemClass::Instance().GetCurLevelState() - 1));
	}
	if (InputManager::Instance().IsDown(L"LevelNext"))
	{
		SystemClass::Instance().ChangeLevel((ALLSTATE)((int)SystemClass::Instance().GetCurLevelState() + 1));
	}
	if (InputManager::Instance().IsDown(L"Next"))
	{
		SetDebugModeToggle();
	}
#endif //  _DEBUG

	
}

void DungeonLevel::EndDebugUpdate()
{
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 0, L"DungeonLevel", lstrlenW(L"DungeonLevel"));
	wchar_t OutText[100]{};
	swprintf_s(OutText, L"Fps : %d", TimeManager::Instance().GetFPS());
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 20, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"AllActorCount : %d", (int)AllActorCount());
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 40, OutText, lstrlenW(OutText));
	Vector2i mousePos = InputManager::Instance().GetMousePos();
	swprintf_s(OutText, L"Mouse Position : (x : %d, y : %d)", mousePos.x, mousePos.y);
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 60, OutText, lstrlenW(OutText));

	//Player.
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 100, L"=======PlayerInfo=======", lstrlenW(L"=======PlayerInfo======="));
	swprintf_s(OutText, L"PlayerCurrentState : %s", m_Player->GetCurStateName());
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 120, OutText, lstrlenW(OutText));
	Vector2f playerPosition = m_Player->GetPosition();
	swprintf_s(OutText, L"Player Position : %.2f, %.2f", playerPosition.x, playerPosition.y);
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 140, OutText, lstrlenW(OutText));
}

void DungeonLevel::MonsterSetPlayer(Player * const player)
{
	std::set<Monster*>::iterator itStart = m_Monster.begin();
	std::set<Monster*>::iterator itEnd = m_Monster.end();

	for (; itStart != itEnd; ++itStart)
	{
		if ((*itStart) != nullptr)
		{
			(*itStart)->SetPlayer(m_Player);
		}
	}
}

void DungeonLevel::MonsterRelease(Monster* const taget)
{
	std::set<Monster*>::iterator itStart = m_Monster.begin();
	std::set<Monster*>::iterator itEnd = m_Monster.end();

	for (; itStart != itEnd;)
	{
		if ((*itStart) == taget)
		{
			itStart = m_Monster.erase(itStart);
			taget->Death();
			continue;
		}
		++itStart;
	}
}

void DungeonLevel::MonsterLoad(const wchar_t * StageName)
{
	std::wstring path = ResourceManager::Instance().FindPath(L"Data");
	std::wstring fileName = StageName ;
	path += fileName + L".md";

	IFStream is = IFStream(path.c_str());

	if (!is.IsOpen())
	{
		return;
	}

	size_t count = 0;
	is.Read(&count, sizeof(size_t), sizeof(size_t));
	for (size_t i = 0; i < count; ++i)
	{
		Monster::OutputMonsterData readData;
		is.Read(&readData, sizeof(Monster::OutputMonsterData), sizeof(Monster::OutputMonsterData));
		Monster* Temp = CreateActor<Monster>(readData._position);
		Temp->InitStateSetting(readData._type);
		m_Monster.insert(Temp);
	}
}
