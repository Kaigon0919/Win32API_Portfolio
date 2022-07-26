#include "stdafx.h"
#include "TestLevel.h"
#include"Player.h"
#include"PlayerBackGround.h"
#include"GameMouse.h"
#include"GameMath.h"
#include"EffectTest.h"
#include"WarpObject.h"
#include"Monster.h"
TestLevel::TestLevel() : Level(), m_Player(nullptr) 
{
}


TestLevel::~TestLevel()
{
}

void TestLevel::Loading()
{
	YSortOn(0);
	SetBackBufferColor(RGB(0,0,0));
	m_BackGround = CreateActor<PlayerBackGround>();
	
	if (FindActor(L"Player") == nullptr)
	{
		m_Player = CreateActor<Player>();
		m_Player->StateOverOn(ALLSTATE::Stage1, ALLSTATE::Stage2, ALLSTATE::Stage3, ALLSTATE::Village);
	}
	if (FindActor(L"GameMouse") == nullptr)
	{
		m_GameMouse = CreateActor<GameMouse>();
		m_GameMouse->StateOverOn(ALLSTATE::Stage1, ALLSTATE::Stage2, ALLSTATE::Stage3, ALLSTATE::Village, ALLSTATE::EDIT, ALLSTATE::TITLE);
	}
	m_BackGround->SetSprite(L"map01.bmp");
	m_BackGround->SetSize(Vector2f(2000.0f, 1500.0f));

	WarpObject* warp1 = CreateActor<WarpObject>(Vector2f(-45.0f, 342.0f));
	warp1->SetNextLevel(ALLSTATE::Stage1);
	warp1->SetNextLevelPosition(Vector2f(-982.0f, 560.0f));
	
	Monster* _Monster = CreateActor<Monster>();
	_Monster->InitStateSetting(Monster::MonsterType::Monster4, 999999.0f, 150.0f,10.0f,70.0f,150.0f,300.0f);
	m_Monster.insert(_Monster);

	ColLink(L"MouseCol", L"Monster");
	ColLink(L"MouseCol", L"Warp");
	ColLink(L"Arrow", L"Player");
	ColLink(L"Arrow", L"Monster");
}

void TestLevel::LevelEnter()
{
	m_Player = (Player*)FindActor(L"Player");
	if (m_Player)
	{
		// player Setting.
		m_Player->SetBackGound(nullptr);
		m_Player->SetBattleMode(true);
		m_Player->SetBackSound(L"TownBGM.wav");
		m_Player->SetMonsters(&m_Monster);
	}

	m_GameMouse = (GameMouse*)FindActor(L"GameMouse");
	if (m_GameMouse)
	{
		m_GameMouse->SetPlayer(m_Player);
	}
	m_GameMouse->WatingTimeReset();

	std::set<Monster*>::iterator itStart = m_Monster.begin();
	std::set<Monster*>::iterator itEnd = m_Monster.end();
	for (;itStart != itEnd ; ++itStart)
	{
		(*itStart)->SetPlayer(m_Player);
	}
}

void TestLevel::LevelExit()
{
	m_Player->SetMonsters(nullptr);
}

void TestLevel::LevelUpdate()
{
#ifdef _DEBUG
	if (InputManager::Instance().IsDown(L"Exit"))
	{
		PostMessage(SystemClass::Instance().GetHWND(),WM_CLOSE,0,0);
	}
	if (InputManager::Instance().IsDown(L"LevelPrev"))
	{
		SystemClass::Instance().ChangeLevel((ALLSTATE)((int)ALLSTATE::Test - 1));
	}
	if (InputManager::Instance().IsDown(L"LevelNext"))
	{
		SystemClass::Instance().ChangeLevel(ALLSTATE::Test);
	}
	if (InputManager::Instance().IsDown(L"Next"))
	{
		SetDebugModeToggle();
	}
#endif
}

void TestLevel::EndDebugUpdate()
{
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 0, L"TestLevel", lstrlenW(L"TestLevel"));
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
	Vector2f tagetPosition = m_Player->GetMoveTaget();
	swprintf_s(OutText, L"Taget Position : %.2f, %.2f", tagetPosition.x, tagetPosition.y);
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 160, OutText, lstrlenW(OutText));
	Vector2f GameMousePosition = m_GameMouse->GetPosition();
	swprintf_s(OutText, L"m_GameMouse Position : %.2f, %.2f", GameMousePosition.x, GameMousePosition.y);
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 180, OutText, lstrlenW(OutText));

}
