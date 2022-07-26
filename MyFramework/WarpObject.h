#pragma once
#include"Actor.h"

class SingleRenderer;
class WarpObject : public Actor
{
public:
	WarpObject();
	~WarpObject();
private:
	SingleRenderer* pRenderer;
	ActorCollision * m_Collision;
	ALLSTATE nextLevel;
	Vector2f nextLevelPosition;

public:
	// Actor을(를) 통해 상속됨
	virtual void Init() override;
	virtual void CollisionEnter(ActorCollision* _this, ActorCollision* _other)override;
	virtual void CollisionStay(ActorCollision* _this, ActorCollision* _other)override;
	virtual void CollisionExit(ActorCollision* _this, ActorCollision* _other)override;

public:
	void SetNextLevel(ALLSTATE _newLevel)
	{
		nextLevel = _newLevel;
	}
	void SetNextLevelPosition(Vector2f _nextPos)
	{
		nextLevelPosition = _nextPos;
	}
	void SetActive(bool isActive);
public:
	void OnWarp(Actor* player);
};

