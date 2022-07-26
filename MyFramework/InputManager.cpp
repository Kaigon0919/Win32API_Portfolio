#include "stdafx.h"
#include "InputManager.h"


InputManager::InputManager() : Start(), End(), m_InputData(), m_MousePos(0,0)
{
}


InputManager::~InputManager()
{
	Start = m_InputData.begin();
	End = m_InputData.end();

	while (Start != End)
	{
		delete Start->second;
		Start->second = nullptr;
		++Start;
	}
}

bool InputManager::IsUp(const wchar_t * _keyName)
{
	InputData* taget = FindNode(_keyName);
	if (!taget)
	{
		return false;
	}
	return 	taget->isUp;
}

bool InputManager::IsDown(const wchar_t * _keyName)
{
	InputData* taget = FindNode(_keyName);
	if (!taget)
	{
		return false;
	}
	return 	taget->isDown;
}

bool InputManager::IsUnPressed(const wchar_t * _keyName)
{
	InputData* taget = FindNode(_keyName);
	if (!taget)
	{
		return false;
	}
	return 	taget->isUnPressed;
}

bool InputManager::IsPressed(const wchar_t * _keyName)
{
	InputData* taget = FindNode(_keyName);
	if (!taget)
	{
		return false;
	}
	return 	taget->isPressed;
}

void InputManager::MouseUpdate()
{
	POINT mousePoint;
	// OS의 마우스 위치를 받는다.
	GetCursorPos(&mousePoint);
	// OS의 마우스 위치를 윈도우창의 로컬위치로 변환 시킨다.
	ScreenToClient(SystemClass::Instance().GetHWND(), &mousePoint);
	m_MousePos = {mousePoint.x, mousePoint.y};
	
	
}

Vector2i InputManager::GetMousePos() const
{
	return m_MousePos;
}
void InputManager::Update()
{

	MouseUpdate();

	Start = m_InputData.begin();
	End = m_InputData.end();


	for (; Start != End; ++Start)
	{
		if (Start->second)
		{
			Start->second->Update();
		}
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// InputData Function.
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InputManager::InputData::Update()
{
	bool keyCheck = AllKeyCheck();

	if (keyCheck)
	{
		if (isUnPressed)
		{
			isUp = false;
			isUnPressed = false;
			isDown = true;
			isPressed = true;
		}
		else
		{
			isUp = false;
			isUnPressed = false;
			isDown = false;
			isPressed = true;
		}
	}
	else if (keyCheck == false)
	{
		if (isPressed)
		{
			isUp = true;
			isUnPressed = true;
			isDown = false;
			isPressed = false;
		}
		else
		{
			isUp = false;
			isUnPressed = true;
			isDown = false;
			isPressed = false;
		}
	}
}

bool InputManager::InputData::AllKeyCheck()
{
	if (!SystemClass::Instance().IsFocus())
	{
		return false;
	}
	for (size_t i = 0; i < m_key.size(); ++i)
	{
		if (GetAsyncKeyState(m_key[i]) == 0)
		{
			return false;
		}
	}
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////