#include"stdafx.h"
#include"SystemClass.h"
#include"ResourceManager.h"
#include"Level.h"

void SystemClass::Frame()
{
	InputManager::Instance().Update();
	TimeManager::Instance().Update();

	m_CurLevel->LevelUpdate();
	m_CurLevel->PrevUpdate();
	m_CurLevel->Update();
	m_CurLevel->LateUpdate();
	m_CurLevel->Render();
	m_CurLevel->AfterRender();

#ifdef _DEBUG
	if (InputManager::Instance().IsDown(L"Prev"))
	{
		isLevelDebug = isLevelDebug ? false : true;
	}
	if (isLevelDebug)
	{
		m_CurLevel->EndDebugUpdate();
	}
#endif
	BitBlt(m_HDC, 0, 0, m_WindowSize.x, m_WindowSize.y, ResourceManager::Instance().GetBackBuffer(), 0, 0, SRCCOPY);

	m_CurLevel->Collision();
	m_CurLevel->Release();

	ChangeUpdate();
}