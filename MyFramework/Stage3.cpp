#include "stdafx.h"
#include "Stage3.h"
#include"Player.h"
#include"PlayerBackGround.h"
#include"WarpObject.h"
#include"GameMouse.h"

Stage3Level::Stage3Level()
{
}


Stage3Level::~Stage3Level()
{
}





void Stage3Level::Loading()
{
	DungeonLevel::Loading();
	warp_BossStage = CreateActor<WarpObject>(Vector2f(1239.0f, -289.0f));
	warp_Stage2 = CreateActor<WarpObject>(Vector2f(-970.0f,562.0f));
	
	warp_BossStage->SetNextLevel(ALLSTATE::Stage3);
	warp_BossStage->SetActive(false);

	warp_Stage2->SetNextLevel(ALLSTATE::Stage2);
	warp_Stage2->SetNextLevelPosition(Vector2f(1239.0f, -289.0f));


	m_BackGround->Load(L"Stage3.mtd");
	MonsterLoad(L"Stage3");
}

void Stage3Level::LevelEnter()
{
	DungeonLevel::LevelEnter();
}

void Stage3Level::LevelExit()
{
	DungeonLevel::LevelExit();
}

void Stage3Level::LevelUpdate()
{
	DungeonLevel::LevelUpdate();
	if (InputManager::Instance().IsDown(L"SpaceBar"))
	{
		warp_BossStage->SetActive(true);
	}
}

void Stage3Level::EndDebugUpdate()
{
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 0, L"Stage3", lstrlenW(L"Stage3"));
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
