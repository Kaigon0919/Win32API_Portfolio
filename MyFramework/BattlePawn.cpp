#include "stdafx.h"
#include "BattlePawn.h"
#include"Render.h"
#include"ActorCollision.h"



BattlePawn::BattlePawn() :m_MaxHp(), m_CurHp(), m_Attck(), m_AttRange()
{
}


BattlePawn::~BattlePawn()
{
}

void BattlePawn::Attack(BattlePawn * taget)
{
	if (taget)
	{
		taget->ProcessDamage(m_Attck);
	}
}

void BattlePawn::ProcessDamage(float _damage)
{
	m_CurHp -= _damage;
	m_CurHp = m_CurHp < 0 ? 0 : m_CurHp;
}

Vector2f BattlePawn::GetPivot() const
{
	if (m_AniRenderer == nullptr)
	{
		return Vector2f::zero;
	}
	return m_AniRenderer->GetPivot();
}

Vector2f BattlePawn::GetColSize() const
{
	if (m_Collision == nullptr)
	{
		return Vector2f::zero;
	}
	return m_Collision->GetSize();
}

Vector2f BattlePawn::DistancePerFrame(const Vector2f & _myPosition, const Vector2f & _taget, const float _moveDistance)
{	// 프레임당 이동할 거리를 별도의 메모리에 저장해준다.
	float FrameDis = _moveDistance;

	// 타겟까지의 방향 + 크기.
	Vector2f dir = _taget - _myPosition;
	// 갈 곳까지의 거리를 구한다.
	float dirLen = dir.Length();
	// 타겟과의 거리가 0.0f이면 이후 제로디비전이 일어나므로 Vector2f::zero를 반환. 즉 이동할 거리가 0 이다.
	if (dirLen == 0.0f)
	{
		return Vector2f::zero;
	}
	// 프레임당 거리가 최종위치까지의 거리보다 크다면 프레임당 거리를 최종위치까지의 거리로 바꿔준다.
	if (FrameDis > dirLen)
	{
		FrameDis = dirLen;
	}

	// dir를 단위벡터로 바꿔준다.
	dir.normalize();
	// (방향 * 이동해야할 거리) 를 반환하다.
	return dir*FrameDis;
}
