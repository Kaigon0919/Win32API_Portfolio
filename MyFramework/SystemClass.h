#pragma once
#include<vector>
#include"MathData.h"

enum ALLSTATE
{
	TITLE,
	EDIT,
	Village,
	Stage1,
	Stage2,
	Stage3,
	//BossRoom,
#ifdef _DEBUG
	Test,
#endif
	MAX
};

class Level;
class Actor;
class SystemClass
{
public: // »ý¼ºÀÚ.
	SystemClass();
	~SystemClass();
	SystemClass(const SystemClass&) = delete;
	SystemClass operator=(const SystemClass&) = delete;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Windows //////////////////////////////////////////////////////////////////////////////////////////
private: // private static data.
	static bool m_isRun;

public: // public static Function.
	static SystemClass& Instance()
	{
		static SystemClass instance;
		return instance;
	}
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

private: // private data.
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	HDC m_HDC;
	Vector2i m_WindowSize;

private: // private Window Function.
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE);

public:
	inline HINSTANCE GetHINSTANCE()const
	{
		return m_hInstance;
	}

	inline HDC GetHDC()const
	{
		return m_HDC;
	}
	inline HWND GetHWND()const
	{
		return m_hWnd;
	}
	inline Vector2i GetWindowsSize()const
	{
		return m_WindowSize;
	}
	bool IsFocus()const;
private:
	bool WindowInitialize(HINSTANCE hInstance);
	bool UserInit();
	void Frame();

public: // public Function.
	bool Initialize(HINSTANCE hInstance);
	int Run();


/////////////////////////////////////////////////////////////////////////////////////////////////////
// other   //////////////////////////////////////////////////////////////////////////////////////////
private:
	std::vector<Level*> m_AllLevel;
	Level* m_CurLevel;
	Level* m_NextLevel;
	ALLSTATE curState;
	ALLSTATE nextState;

	bool isLevelDebug;
public:
	ALLSTATE GetCurLevelState()const
	{
		return curState;
	}
public:
	void ChangeLevel(ALLSTATE _state);
	void ChangeUpdate();
public:
	bool IsHaveCheck(ALLSTATE _State, Actor* _Actor);
	void PushActor(ALLSTATE _State, Actor* _Actor);

public:
	template<class T>
	T* CreateLevel(ALLSTATE _state)
	{
		m_AllLevel[_state] = new T();
		return (T*)m_AllLevel[_state];
	}
};