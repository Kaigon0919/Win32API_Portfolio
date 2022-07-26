#pragma once
#include "Actor.h"
#include "TimeHelper.h"
class SingleRenderer;
class Bullet : public Actor
{
public:
	Bullet();
	~Bullet();
private:
	Vector2f taget;
	SingleRenderer* m_Renderer;
	TimeHelper m_DeathTimer;
	float m_MoveSpeed;
public:
	virtual void Init() override;
	virtual void PrevUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	virtual void CollisionEnter(ActorCollision* _this, ActorCollision* _other)override;
	virtual void CollisionStay(ActorCollision* _this, ActorCollision* _other)override;
	virtual void CollisionExit(ActorCollision* _this, ActorCollision* _other)override;

	virtual void OtherCollisionEnter(ActorCollision* _this, ActorCollision* _other) override;
	virtual void OtherCollisionStay(ActorCollision* _this, ActorCollision* _other)override;
	virtual void OtherCollisionExit(ActorCollision* _this, ActorCollision* _other) override;
public:
	void SetTaget(Vector2f _taget)
	{
		taget = _taget;
	}
};

