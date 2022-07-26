#include "stdafx.h"
#include "Actor.h"
#include"ActorRenderer.h"
#include"ActorCollision.h"
#include"Level.h"

Actor::Actor() : NameBase(), m_Position(0,0), m_Level(nullptr), m_ScaleRatio(1.0f), m_StateOver(false)
{
}

Actor::~Actor()
{
	std::list<ActorRenderer*>::iterator StartIter = m_RenderList.begin();
	std::list<ActorRenderer*>::iterator EndIter = m_RenderList.end();

	for (; StartIter != EndIter; StartIter++)
	{
		delete (*StartIter);
	}

	std::list<ActorCollision*>::iterator itColStart = m_pCollisionList.begin();
	std::list<ActorCollision*>::iterator itColEnd = m_pCollisionList.end();

	for (; itColStart != itColEnd; itColStart++)
	{
		delete (*itColStart);
	}
}

Vector2f Actor::GetScreenPosition() const
{
	return m_Position - GetLevel()->GetCameraPosition();
}

void Actor::PrevUpdate()
{
}

void Actor::Update()
{
}

void Actor::LateUpdate()
{
}

void Actor::DebugRender(){}

void Actor::AfterRender()
{
}

ActorCollision * Actor::CreateCollision(const wchar_t *_GroupName, int _Type)
{
	ActorCollision* NewCol = new ActorCollision();
	NewCol->SetType(_Type);
	NewCol->SetActor(this);
	NewCol->m_GroupName = _GroupName;
	m_pCollisionList.push_back(NewCol);
	GetLevel()->PushCol(_GroupName, NewCol);
	return NewCol;
}
