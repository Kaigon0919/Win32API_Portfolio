#include "stdafx.h"
#include "Stage1.h"
#include"Player.h"
#include"Monster.h"
#include"PlayerBackGround.h"
#include"WarpObject.h"
#include"GameMouse.h"
Stage1Level::Stage1Level(): DungeonLevel()
{
	
}


Stage1Level::~Stage1Level()
{
}

void Stage1Level::Loading()
{
	DungeonLevel::Loading();
	warp_Village = CreateActor<WarpObject>(Vector2f(-970.0f, 562.0f));
	warp_Stage2 = CreateActor<WarpObject>(Vector2f(1239.0f, -289.0f));

	warp_Village->SetNextLevel(ALLSTATE::Village);
	warp_Village->SetNextLevelPosition(Vector2f(-45.0f, 342.0f));

	warp_Stage2->SetNextLevel(ALLSTATE::Stage2);
	warp_Stage2->SetNextLevelPosition(Vector2f(-982.0f, 560.0f));
	warp_Stage2->SetActive(false);

	m_BackGround->Load(L"Stage1.mtd");
	MonsterLoad(L"Stage1");
}

void Stage1Level::LevelEnter()
{
	DungeonLevel::LevelEnter();
	

}

void Stage1Level::LevelExit()
{
	DungeonLevel::LevelExit();
}

void Stage1Level::LevelUpdate()
{
	DungeonLevel::LevelUpdate();


	std::set<Monster*>::iterator itSetMonstStart = m_Monster.begin();
	std::set<Monster*>::iterator itSetMonstEnd = m_Monster.end();

	bool isAllDie = true;
	for (; itSetMonstStart != itSetMonstEnd; ++itSetMonstStart)
	{
		if ((*itSetMonstStart)->IsDead())
		{
			continue;
		}
		isAllDie = false;
	}
	if (isAllDie)
	{
		warp_Stage2->SetActive(true);
	}
}

void Stage1Level::EndDebugUpdate()
{
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 0, L"Stage1", lstrlenW(L"Stage1"));
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
