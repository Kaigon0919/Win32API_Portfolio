#pragma once
#include "Actor.h"
class AniRenderer;
class SingleRenderer;
class BattlePawn : public Actor
{
public:
	BattlePawn();
	~BattlePawn();
protected:
	float m_CurHp;
	float m_MaxHp;
	float m_Attck;
	float m_AttRange;

	AniRenderer* m_AniRenderer;
	SingleRenderer* m_ShadowRender;
	ActorCollision* m_Collision;
public:
	virtual void Attack(BattlePawn * taget);
	virtual void ProcessDamage(float _damage);
	bool IsDead()const
	{
		return m_CurHp <= 0;
	}

	Vector2f GetPivot()const;
	Vector2f GetColSize()const;

protected:
	Vector2f DistancePerFrame(const Vector2f& _myPosition, const Vector2f& _taget, const float _moveDistance);
};

