#include "stdafx.h"
#include "ActorCollision.h"
#include"Actor.h"
#include"GameMath.h"
#include "ResourceManager.h"

ActorCollision::ActorCollision()
{
}


ActorCollision::~ActorCollision()
{
	// Collision의 객체를 지우는 것이 아닌, 접근 가능하게 하는 주소값을 지운다.
	// Collision 객체는 소유자인 Actor가 직접 지운다.
	std::set<ActorCollision*>::iterator start = m_OtherCol.begin();
	std::set<ActorCollision*>::iterator end = m_OtherCol.end();
	for (; start != end; ++start)
	{
		(*start)->OtherErase(this);
	}
}

void ActorCollision::ParentPosSetting()
{
	m_Col.Position = GetParentPos();
	m_Col.Size = m_Size;
}

bool ActorCollision::GeoCheck(ActorCollision * _other)
{
	switch (m_ColType)
	{
	case CT_RECT:
		switch (_other->m_ColType)
		{
		case CT_RECT:
			return GameMath::RECTTORECT(m_Col, _other->m_Col);
		case CT_CIRCLE:
			return GameMath::RECTTOCIRCLE(m_Col, _other->m_Col);
		case CT_POINT:
			return GameMath::RECTTOPOINT(m_Col, _other->m_Col.Position);
		default:
			break;
		}
		break;
	case CT_CIRCLE:
		switch (_other->m_ColType)
		{
		case CT_RECT:
			return GameMath::RECTTOCIRCLE(_other->m_Col, m_Col);
		case CT_CIRCLE:
			return GameMath::CIRCLETOCIRCLE(m_Col, _other->m_Col);
		case CT_POINT:
			return GameMath::CIRCLETOPOINT(m_Col, _other->m_Col.Position);
		default:
			break;
		}
		break;
	case CT_POINT:
		switch (_other->m_ColType)
		{
		case CT_RECT:
			return GameMath::RECTTOPOINT(_other->m_Col, m_Col.Position);
		case CT_CIRCLE:
			return GameMath::CIRCLETOPOINT(_other->m_Col, m_Col.Position);
		case CT_POINT:
			return GameMath::POINTTOPOINT(m_Col, _other->m_Col);
		default:
			break;
		}
		break;
	default:
		break;
	}
	return false;
}

void ActorCollision::ColCheck(ActorCollision * _other)
{
	FindCollter = m_OtherCol.find(_other);

	// 충돌 체크.
	if (GeoCheck(_other))
	{
		if (FindCollter != m_OtherCol.end())
		{
			// 충돌중.
			GetActor()->CollisionStay(this, _other);
			_other->GetActor()->OtherCollisionStay(_other, this);
		}
		else
		{
			// 충돌 시작.
			GetActor()->CollisionEnter(this, _other);
			_other->GetActor()->OtherCollisionEnter(_other, this);
			m_OtherCol.insert(_other);
			_other->m_OtherCol.insert(this);

		}
	}
	else if(FindCollter != m_OtherCol.end())
	{
		GetActor()->CollisionExit(this, _other);
		_other->GetActor()->OtherCollisionExit(_other, this);
		OtherErase(_other);
		_other->OtherErase(this);
	}
}

void ActorCollision::OtherErase(ActorCollision * _col)
{
	FindCollter = m_OtherCol.find(_col);
	if (FindCollter != m_OtherCol.end())
	{
		m_OtherCol.erase(FindCollter);
	}
}

void ActorCollision::DebugRender()
{
	RectFloat DebugCol = m_Col;

	DebugCol.Position = GetScreenPos();

	switch (m_ColType)
	{
	case CT_RECT:
		Rectangle(ResourceManager::Instance().GetBackBuffer(), DebugCol.IntLeft(), DebugCol.IntTop(), DebugCol.IntRight(), DebugCol.IntBottom());
		break;
	case CT_CIRCLE:
		Ellipse(ResourceManager::Instance().GetBackBuffer(), DebugCol.IntLeft(), DebugCol.Position.GetIntY() - DebugCol.Size.GetHalfIntX(), DebugCol.IntRight(), DebugCol.Position.GetIntY() + DebugCol.Size.GetHalfIntX());
		break;
	case CT_POINT:
		DebugCol.Size = Vector2f(6, 6);
		Rectangle(ResourceManager::Instance().GetBackBuffer(), DebugCol.IntLeft(), DebugCol.IntTop(), DebugCol.IntRight(), DebugCol.IntBottom());
		break;
	default:
		break;
	}
}
