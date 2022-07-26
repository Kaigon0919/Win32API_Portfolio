#include "stdafx.h"
#include "Stage2.h"
#include"Player.h"
#include"PlayerBackGround.h"
#include"WarpObject.h"
#include"GameMouse.h"
#include"Monster.h"

Stage2Level::Stage2Level()
{
}


Stage2Level::~Stage2Level()
{
}


void Stage2Level::Loading()
{
	DungeonLevel::Loading();
	warp_Stage1 = CreateActor<WarpObject>(Vector2f(-970.0f, 562.0f));
	warp_Stage3 = CreateActor<WarpObject>(Vector2f(1239.0f, -289.0f));

	warp_Stage1->SetNextLevel(ALLSTATE::Stage1);
	warp_Stage1->SetNextLevelPosition(Vector2f(1239.0f, -289.0f));


	warp_Stage3->SetNextLevel(ALLSTATE::Stage3);
	warp_Stage3->SetNextLevelPosition(Vector2f(-982.0f, 560.0f));
	warp_Stage3->SetActive(false);


	m_BackGround->Load(L"Stage2.mtd");
	MonsterLoad(L"Stage2");
}

void Stage2Level::LevelEnter()
{
	DungeonLevel::LevelEnter();
}

void Stage2Level::LevelExit()
{
	DungeonLevel::LevelExit();
}

void Stage2Level::LevelUpdate()
{
	DungeonLevel::LevelUpdate();
	bool isAllDie = true;

	std::set<Monster*>::iterator itSetMonstStart = m_Monster.begin();
	std::set<Monster*>::iterator itSetMonstEnd = m_Monster.end();
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
		warp_Stage3->SetActive(true);
	}
}

void Stage2Level::EndDebugUpdate()
{
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 0, L"Stage2", lstrlenW(L"Stage2"));
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
