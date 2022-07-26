#pragma once
#include<string>
#include"UpdateBase.h"

class NameBase : public UpdateBase
{
public:
	NameBase();
	~NameBase();

private:
	std::wstring m_Name;

public:
	inline void SetName(const wchar_t * _name)
	{
		m_Name = _name;
	}
	inline const wchar_t* GetName()const
	{
		return m_Name.c_str();
	}
	inline bool NameEqual(const wchar_t* _name)const
	{
		// string Ŭ���� ����� �̿�, operator==
		return m_Name == _name;
	}
};

