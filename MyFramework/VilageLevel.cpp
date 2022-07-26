#include "stdafx.h"
#include "VilageLevel.h"
#include"Player.h"
#include"PlayerBackGround.h"
#include"GameMouse.h"
#include"WarpObject.h"


VillageLevel::VillageLevel()
{
}


VillageLevel::~VillageLevel()
{
}

void VillageLevel::Loading()
{
	YSortOn(0);
	SetBackBufferColor(RGB(6, 7, 13));
	m_BackGround = CreateActor<PlayerBackGround>();
	m_GameMouse = CreateActor<GameMouse>();
	if (FindActor(L"Player") == nullptr)
	{
		m_Player = CreateActor<Player>();
#ifdef _DEBUG
		m_Player->StateOverOn(ALLSTATE::Stage1, ALLSTATE::Stage2, ALLSTATE::Stage3, ALLSTATE::Test);
#else
		m_Player->StateOverOn(ALLSTATE::Stage1, ALLSTATE::Stage2, ALLSTATE::Stage3);
#endif
	}
	m_BackGround->SetSprite(L"map01.bmp");
	m_BackGround->SetSize(Vector2f(2000.0f, 1500.0f));
	m_BackGround->Load(L"Village.mtd");
	ColLink(L"MouseCol", L"Monster");
	ColLink(L"MouseCol", L"Warp");

	WarpObject* DungeonWarp = CreateActor<WarpObject>(Vector2f(-45.0f, 342.0f));
	DungeonWarp->SetNextLevel(ALLSTATE::Stage1);
	DungeonWarp->SetNextLevelPosition(Vector2f(-982.0f,560.0f));

}

void VillageLevel::LevelEnter()
{
	m_Player = (Player*)FindActor(L"Player");
	if (m_Player)
	{
		// player Setting.
		m_Player->SetBackGound(m_BackGround);
		m_Player->SetBattleMode(false);
		m_Player->SetBackSound(L"TownBGM.wav");
	}

	m_GameMouse = (GameMouse*)FindActor(L"GameMouse");
	if (m_GameMouse)
	{
		m_GameMouse->SetPlayer(m_Player);
	}
	m_GameMouse->WatingTimeReset();
}

void VillageLevel::LevelExit()
{
}

void VillageLevel::LevelUpdate()
{
#ifdef _DEBUG
	if (InputManager::Instance().IsDown(L"Exit"))
	{
		PostMessage(SystemClass::Instance().GetHWND(), WM_CLOSE, 0, 0);
	}
	if (InputManager::Instance().IsDown(L"LevelPrev"))
	{
		SystemClass::Instance().ChangeLevel((ALLSTATE)((int)ALLSTATE::Village - 1));
	}
	if (InputManager::Instance().IsDown(L"LevelNext"))
	{
		SystemClass::Instance().ChangeLevel((ALLSTATE)((int)ALLSTATE::Village + 1));
	}
	if (InputManager::Instance().IsDown(L"Prev"))
	{
	}
	if (InputManager::Instance().IsDown(L"Next"))
	{
		SetDebugModeToggle();
	}
#endif
}

void VillageLevel::EndDebugUpdate()
{
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 0, L"VilageLevel", lstrlenW(L"VilageLevel"));
	wchar_t OutText[100]{};
	swprintf_s(OutText, L"Fps : %d", TimeManager::Instance().GetFPS());
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 20, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"AllActorCount : %d", (int)AllActorCount());
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 40, OutText, lstrlenW(OutText));
	Vector2i mousePos = InputManager::Instance().GetMousePos();
	swprintf_s(OutText, L"Mouse Position : (x : %d, y : %d)", mousePos.x, mousePos.y);
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 60, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"DIR : %s", ResourceManager::Instance().RootPathPtr());
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 80, OutText, lstrlenW(OutText));
	//Player.
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 100, L"=======PlayerInfo=======", lstrlenW(L"=======PlayerInfo======="));
	swprintf_s(OutText, L"PlayerCurrentState : %s", m_Player->GetCurStateName());
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 120, OutText, lstrlenW(OutText));
	Vector2f playerPosition = m_Player->GetPosition();
	swprintf_s(OutText, L"Player Position : %.2f, %.2f", playerPosition.x, playerPosition.y);
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 140, OutText, lstrlenW(OutText));
}
