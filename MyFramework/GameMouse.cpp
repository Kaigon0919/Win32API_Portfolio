#include "stdafx.h"
#include "GameMouse.h"
#include"Render.h"
#include"ActorCollision.h"
#include"Level.h"

///////////////////////////////////////////////////////////////////////////////////////////

bool YSortFunc(const ActorCollision* one, ActorCollision* two)
{
	if (one->GetActor()->GetPosition().y > two->GetActor()->GetPosition().y)
	{
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////



GameMouse::GameMouse() : pRenderer(nullptr), m_Player(nullptr), m_Collision(nullptr), StateString{ L"Default",L"DefaultClick",L"Hand",L"Warp",L"NotMove",L"Attack",L"AttackClick",L"MagicSkill",L"PhysicSkill" }, m_TagetActor(nullptr) ,initWatingTime(0.5f)
{

}


GameMouse::~GameMouse()
{
}

void GameMouse::Init()
{
	SetName(L"GameMouse");
	pRenderer = CreateRenderer<AniRenderer>(100);
	pRenderer->SetSize(Vector2f(64, 64));
	pRenderer->SetPivot(Vector2f(16, 16));
	AnimaitionSetting();

	m_Collision = CreateCollision(L"MouseCol", CT_POINT);

	m_State = MouseState::Max;
	ChageState(MouseState::Default);
	pRenderer->CameraMode(true);
	m_ScaleRatio = 1.0f;

}

void GameMouse::PrevUpdate()
{
}

void GameMouse::Update()
{
	
	m_Position = GetLevel()->GetMouseConvertPosition();

	if (!initWatingTime.Check())
	{
		return;
	}

	ColList.sort(YSortFunc);

	(*this.*StateFunc)();
}

void GameMouse::LateUpdate()
{

	std::list<ActorCollision*>::iterator it = ColList.begin();

	while (it != ColList.end())
	{
		if ((*it)->IsUpdate() == false)
		{
			ColList.erase(it);
			break;
		}
		++it;
	}
}

void GameMouse::CollisionEnter(ActorCollision * _this, ActorCollision * _other)
{
	if (_other->GetActor()->NameEqual(L"Monster"))
	{
		ColList.push_back(_other);
	}
	if (_other->GetActor()->NameEqual(L"Warp"))
	{
		ColList.push_back(_other);
	}
}

void GameMouse::CollisionStay(ActorCollision * _this, ActorCollision * _other)
{
}

void GameMouse::CollisionExit(ActorCollision * _this, ActorCollision * _other)
{
	if (_other->GetActor()->NameEqual(L"Monster"))
	{
		std::list<ActorCollision*>::iterator it = ColList.begin();
		while (it != ColList.end())
		{
			if (*it == _other)
			{
				ColList.erase(it);
				break;
			}
			++it;
		}
	}
	if (_other->GetActor()->NameEqual(L"Warp"))
	{
		std::list<ActorCollision*>::iterator it = ColList.begin();
		while (it != ColList.end())
		{
			if (*it == _other)
			{
				ColList.erase(it);
				break;
			}
			++it;
		}
	}
}

void GameMouse::AnimaitionSetting()
{
	pRenderer->CreateAnimation(L"Hamd", L"Mouse", 0, 2);
	pRenderer->CreateAnimation(L"Default", L"Mouse", 3, 15);
	pRenderer->CreateAnimation(L"DefaultClick", L"Mouse", 16, 17, false, 0.05f);
	pRenderer->CreateAnimation(L"Warp", L"Mouse", 18, 21);
	pRenderer->CreateAnimation(L"NotMove", L"Mouse", 22, 33);
	pRenderer->CreateAnimation(L"Attack", L"Mouse", 34, 40);
	pRenderer->CreateAnimation(L"AttackClick", L"Mouse", 41, 42, false);
	pRenderer->CreateAnimation(L"MagicSkill", L"Mouse", 43, 51);
	pRenderer->CreateAnimation(L"PhysicSkill", L"Mouse", 52, 61);
}

void GameMouse::ChageState(MouseState _newState)
{
	if (m_State == _newState)
	{
		return;
	}

	m_State = _newState;
	pRenderer->ChangeAnimation(StateString[m_State].c_str());
	switch (m_State)
	{
	case MouseState::Default:
		StateFunc = &GameMouse::DefaultFunc;
		break;
	case MouseState::DefaultClick:
		StateFunc = &GameMouse::DefaultClickFunc;
		break;
	case MouseState::Hand:
		StateFunc = &GameMouse::HandFunc;
		break;
	case MouseState::Warp:
		StateFunc = &GameMouse::WarpFunc;
		break;
	case MouseState::NotMove:
		break;
	case MouseState::Attack:
		StateFunc = &GameMouse::AttackFunc;
		break;
	case MouseState::AttackClick:
		StateFunc = &GameMouse::AttackClickFunc;
		break;
	case MouseState::MagicSkill:
		break;
	case MouseState::PhysicSkill:
		break;
	case MouseState::Max:
		break;
	default:
		break;
	}
}
