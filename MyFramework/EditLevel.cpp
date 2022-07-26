#include "stdafx.h"
#include "EditLevel.h"
#include"EditTileMap.h"
#include"GameMouse.h"

EditLevel::EditLevel()
{
}


EditLevel::~EditLevel()
{
}

void EditLevel::Loading()
{
	YSortOn(0);
}

void EditLevel::LevelEnter()
{
	m_TileMap = CreateActor<EditTileMap>();
	GameMouse * mouse = (GameMouse*)FindActor(L"GameMouse");
	if (mouse)
	{
		mouse->SetPlayer(nullptr);
	}
	mouse->WatingTimeReset();
}

void EditLevel::LevelExit()
{
	m_TileMap->Death();
}

void EditLevel::LevelUpdate()
{
#ifdef _DEBUG
	if (InputManager::Instance().IsDown(L"Exit"))
	{
		PostMessage(SystemClass::Instance().GetHWND(), WM_CLOSE, 0, 0);
	}
	if (InputManager::Instance().IsDown(L"LevelPrev"))
	{
		SystemClass::Instance().ChangeLevel((ALLSTATE)((int)ALLSTATE::EDIT - 1));
	}
	if (InputManager::Instance().IsDown(L"LevelNext"))
	{
		SystemClass::Instance().ChangeLevel((ALLSTATE)((int)ALLSTATE::EDIT + 1));
	}
	if (InputManager::Instance().IsDown(L"Next"))
	{
		SetDebugModeToggle();
	}
#endif
	if (InputManager::Instance().IsDown(L"BackSpace"))
	{
		SystemClass::Instance().ChangeLevel((ALLSTATE)((int)ALLSTATE::TITLE));
	}
}

void EditLevel::EndDebugUpdate()
{
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 0, L"EditLevel", lstrlenW(L"EditLevel"));
	wchar_t OutText[100]{};
	swprintf_s(OutText, L"Fps : %d", TimeManager::Instance().GetFPS());
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 20, OutText, lstrlenW(OutText));
	swprintf_s(OutText, L"AllActorCount : %d", (int)AllActorCount());
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 40, OutText, lstrlenW(OutText));
	Vector2i mousePos = InputManager::Instance().GetMousePos();
	swprintf_s(OutText, L"Mouse Position : (x : %d, y : %d)", mousePos.x, mousePos.y);
	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 60, OutText, lstrlenW(OutText));
}
