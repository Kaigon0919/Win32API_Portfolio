#pragma once
#include "ActorSubBase.h"
#include"MathData.h"
#include<set>

enum ColType
{
	CT_RECT,
	CT_CIRCLE,
	CT_POINT,
	CT_MAX
};

class ActorCollision :	public ActorSubBase
{
public:
	ActorCollision();
	~ActorCollision();

private:
	RectFloat m_Col;
	ColType m_ColType;

	// �浹�� �ݸ����� �����ϴ� �ڷᱸ��.
	std::set<ActorCollision*>m_OtherCol;
	std::set<ActorCollision*>::iterator FindCollter;
public:
	std::wstring m_GroupName;
public:
	void SetType(int _type)
	{
		m_ColType = static_cast<ColType>(_type);
	}
	const wchar_t* GroupName() 
	{
		return m_GroupName.c_str();
	}
public:
	void ParentPosSetting();
	bool GeoCheck(ActorCollision* _other);
	void ColCheck(ActorCollision* _other);

	void OtherErase(ActorCollision* _col);
	void DebugRender();

};

