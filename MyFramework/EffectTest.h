#pragma once
#include "Actor.h"
class AniRenderer;
class ActorCollision;
class EffectTest :
	public Actor
{
public:
	EffectTest();
	~EffectTest();
private:
	AniRenderer* m_AniRenderer;
	ActorCollision* m_Collision;

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
private:
	void AnimationSetting();
};

