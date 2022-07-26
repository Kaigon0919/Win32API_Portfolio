#include "stdafx.h"
#include "TitleLevel.h"
#include"ResourceManager.h"
#include"TitleMain.h"
#include"TitleCredit.h"
#include"TitleQuit.h"
#include"TitleStart.h"
#include"TitleOpenning.h"
#include"GameMouse.h"

TitleLevel::TitleLevel()
{
}


TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{
	
	m_Main = CreateActor<TitleMain>();
	TitleCredit* pCredit = CreateActor<TitleCredit>();
	TitleQuit* pQuit = CreateActor<TitleQuit>();
	TitleStart* pStart =CreateActor<TitleStart>();
	TitleOpenning* pOpen = CreateActor<TitleOpenning>();
	m_Mouse = CreateActor<GameMouse>();
	m_Mouse->StateOverOn(ALLSTATE::Stage1, ALLSTATE::Stage2, ALLSTATE::Stage3, ALLSTATE::EDIT, ALLSTATE::Village);


	pStart->SetPosition(Vector2f(513, 520));
	pOpen->SetPosition(Vector2f(513, 553));
	pCredit->SetPosition(Vector2f(513, 586));
	pQuit->SetPosition(Vector2f(513, 619));
	pOpen->SetPosition(Vector2f(513, 553));

	ColLink(L"TitleUI", L"MouseCol");

}

void TitleLevel::LevelEnter()
{
	m_Mouse->SetPlayer(nullptr);
	m_Mouse->WatingTimeReset();
	m_Main->StartSound();
}

void TitleLevel::LevelExit()
{
	m_Main->StopSound();
}

void TitleLevel::LevelUpdate()
{

#ifdef _DEBUG
	if (InputManager::Instance().IsDown(L"LevelPrev"))
	{
		SystemClass::Instance().ChangeLevel((ALLSTATE)((int)ALLSTATE::TITLE));
	}
	if (InputManager::Instance().IsDown(L"LevelNext"))
	{
		SystemClass::Instance().ChangeLevel((ALLSTATE)((int)ALLSTATE::TITLE + 1));
	}
	if (InputManager::Instance().IsDown(L"Exit"))
	{
		PostMessage(SystemClass::Instance().GetHWND(), WM_CLOSE, 0, 0);
	}
	if (InputManager::Instance().IsDown(L"Prev"))
	{
	}
	if (InputManager::Instance().IsDown(L"Next"))
	{
		SetDebugModeToggle();
	}
#endif // !_DEBUG

}

void TitleLevel::EndDebugUpdate()
{

	TextOutW(ResourceManager::Instance().GetBackBuffer(), 20, 0, L"TitleLevel", lstrlenW(L"TitleLevel"));
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


}
