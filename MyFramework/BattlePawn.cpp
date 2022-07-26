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
{	// �����Ӵ� �̵��� �Ÿ��� ������ �޸𸮿� �������ش�.
	float FrameDis = _moveDistance;

	// Ÿ�ٱ����� ���� + ũ��.
	Vector2f dir = _taget - _myPosition;
	// �� �������� �Ÿ��� ���Ѵ�.
	float dirLen = dir.Length();
	// Ÿ�ٰ��� �Ÿ��� 0.0f�̸� ���� ���ε������ �Ͼ�Ƿ� Vector2f::zero�� ��ȯ. �� �̵��� �Ÿ��� 0 �̴�.
	if (dirLen == 0.0f)
	{
		return Vector2f::zero;
	}
	// �����Ӵ� �Ÿ��� ������ġ������ �Ÿ����� ũ�ٸ� �����Ӵ� �Ÿ��� ������ġ������ �Ÿ��� �ٲ��ش�.
	if (FrameDis > dirLen)
	{
		FrameDis = dirLen;
	}

	// dir�� �������ͷ� �ٲ��ش�.
	dir.normalize();
	// (���� * �̵��ؾ��� �Ÿ�) �� ��ȯ�ϴ�.
	return dir*FrameDis;
}
