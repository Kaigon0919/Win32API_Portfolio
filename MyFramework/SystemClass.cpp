#include "stdafx.h"

// default HeaderFile
#include<locale>

// user HeaderFile
#include"SystemClass.h"
#include"MathData.h"
#include"Level.h"
#include"Resource.h"
#include"Actor.h"


RectFloat PlayerRect = RectFloat({ 100, 100 }, { 50, 50 });

bool SystemClass::m_isRun = false;


SystemClass::SystemClass() : m_hInstance(nullptr), m_hWnd(nullptr), m_HDC(nullptr), m_WindowSize(1024,768), m_CurLevel(nullptr), m_NextLevel(nullptr), m_AllLevel(ALLSTATE::MAX), isLevelDebug(false)
{
#ifdef _DEBUG
	isLevelDebug = true;
#endif
}


SystemClass::~SystemClass()
{
	for (size_t i = 0; i < m_AllLevel.size(); i++)
	{
		if (nullptr != m_AllLevel[i])
		{
			delete m_AllLevel[i];
			m_AllLevel[i] = nullptr;
		}
	}
	Level::EndDestroy();
}

bool SystemClass::Initialize(HINSTANCE hInstance)
{
	// 윈도우 초기화.
	bool result = WindowInitialize(hInstance);
	if (!result)
	{
		return false;
	}

	result = UserInit();
	if (!result)
	{
		return false;
	}
	// 마우스 표시 설정.
	ShowCursor(false);
	return true;
}

int SystemClass::Run()
{
	m_isRun = true;

	MSG msg;

	// 기본 메시지 루프입니다.
	while (m_isRun)
	{
		// 윈도우 메세지가 있을 시 처리를 한다.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 윈도우 메세지가 없을때 처리한다.
			Frame();
		}
	}

	return (int)msg.wParam;
}



void SystemClass::ChangeLevel(ALLSTATE _state)
{
	if (!m_AllLevel[_state])
	{
		return;
	}
	m_NextLevel = m_AllLevel[_state];
	nextState = _state;
	
}
void SystemClass::ChangeUpdate()
{
	if (m_NextLevel)
	{
		if (!m_NextLevel->isLoading)
		{
			m_NextLevel->Loading();
			m_NextLevel->isLoading = true;
		}
		if (m_CurLevel != nullptr)
		{
			m_CurLevel->LevelExit();
		}
		m_CurLevel = m_NextLevel;
		std::list<Actor*>::iterator OverStart = Level::m_OverActorList.begin();
		std::list<Actor*>::iterator OverEnd = Level::m_OverActorList.end();
		for (; OverStart != OverEnd; ++OverStart)
		{
			(*OverStart)->SetLevel(m_CurLevel);
		}
		m_CurLevel->LevelEnter();
		m_NextLevel = false;
		curState = nextState;
	}
}
bool SystemClass::IsHaveCheck(ALLSTATE _State, Actor * _Actor)
{
	assert(nullptr != m_AllLevel[_State]);
	return m_AllLevel[_State]->IsHaveCheck(_Actor);
}
void SystemClass::PushActor(ALLSTATE _State, Actor * _Actor)
{
	assert(nullptr != m_AllLevel[_State]);
	m_AllLevel[_State]->PushActor(_Actor);
}
bool SystemClass::IsFocus() const
{
	return m_hWnd == GetFocus();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Winodow Function.
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SystemClass::WindowInitialize(HINSTANCE hInstance)
{
	m_hInstance = hInstance;

	if (!m_hInstance)
	{
		return false;
	}

	// 유니코드 국가 설정.
	_wsetlocale(LC_ALL, L"KOR");

	// 윈도우 초기 설정 및 등록.
	MyRegisterClass(m_hInstance);

	// 윈도우 생성.
	if (!InitInstance(m_hInstance))
	{
		return false;
	}
	return true;
}
// 윈도우 초기 설정 및 등록.
ATOM SystemClass::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYFRAMEWORK));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"SystemClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

// 윈도우 생성 함수.
BOOL SystemClass::InitInstance(HINSTANCE hInstance)
{
	m_hWnd = CreateWindowW(L"SystemClass", L"MyFramework", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!m_hWnd)
	{
		return false;
	}

	m_HDC = GetDC(m_hWnd);
	if (!m_HDC)
	{
		return false;
	}

	RECT rect = { 0,0, m_WindowSize.x, m_WindowSize.y };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);

	ShowWindow(m_hWnd, SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);

	return true;
}

// 윈도우 메세지 처리 함수.
LRESULT CALLBACK SystemClass::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		m_isRun = false;
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////