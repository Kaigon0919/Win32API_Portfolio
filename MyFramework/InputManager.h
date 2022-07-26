#pragma once

#include<Windows.h>
#include<map>
#include<vector>

#include"MathData.h"

class SysyemClass;
class InputManager
{
private:
	InputManager();
	~InputManager();
public: // Singletone Function.
	static InputManager& Instance()
	{
		static InputManager instance = InputManager();
		return instance;
	}
#pragma region InnerClass
private: // inner class.
	class InputData
	{
	public: // 생성자.
		InputData(size_t _size) : isUp(false), isUnPressed(true), isDown(false), isPressed(false)
		{
			m_key.reserve(_size);
		}
		~InputData() {}
	private: // friend
		friend InputManager;
	private: // private data.
		std::vector<int> m_key;
		float PressedTime;
		bool isUp;
		bool isUnPressed;
		bool isDown;
		bool isPressed;

	public: // public function.
		void Update();

	private: // private function.
		bool AllKeyCheck();

	public: // public Template Function.
		template<class ... Rest>
		void PushKeyData(const int _value, Rest... _arg)
		{
			m_key.push_back(_value);
			PushKeyData(_arg...);
		}
	private:
		// 템플릿 가변인자를 사용한 재귀함수 종료를 위한 함수.
		void PushKeyData() {}
	};
#pragma endregion

private:
	std::map<std::wstring, InputData*>::iterator Start;
	std::map<std::wstring, InputData*>::iterator End;
	std::map<std::wstring, InputData*> m_InputData;

	Vector2i m_MousePos;

public:
	InputData* FindNode(const wchar_t* _keyName)
	{
		std::map<std::wstring, InputData*>::iterator FindIter = m_InputData.find(_keyName);

		if (FindIter == m_InputData.end())
		{
			return nullptr;
		}
		return FindIter->second;
	}
	bool IsUp(const wchar_t* _keyName);
	bool IsDown(const wchar_t* _keyName);
	bool IsUnPressed(const wchar_t* _keyName);
	bool IsPressed(const wchar_t* _keyName);

	void MouseUpdate();
	Vector2i GetMousePos()const;



	void Update();

public: // public template Function.
	template<class ... Rest>
	bool CreateKey(const wchar_t* _keyName, Rest... _arg)
	{
		InputData* pNewKey = FindNode(_keyName);

		if (pNewKey)
		{
			return false;
		}
		pNewKey = new InputData(sizeof...(Rest));
		pNewKey->PushKeyData(_arg...);
		m_InputData.insert(std::map<std::wstring, InputData*>::value_type(_keyName, pNewKey));
		return true;
	}
};

