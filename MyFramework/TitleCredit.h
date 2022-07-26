#pragma once
#include "Actor.h"

class AniRenderer;
class ActorCollision;
class TitleCredit : public Actor
{
public:
	TitleCredit();
	~TitleCredit();
	
private:
	AniRenderer* m_AniRenderer;
	ActorCollision* m_Collision;
public:
	// Actor을(를) 통해 상속됨
	virtual void Init() override;
	virtual void PrevUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	void OnClick();
	void OnClickUp();
	
	virtual void CollisionEnter(ActorCollision* _this, ActorCollision* _other)override;
	virtual void CollisionStay(ActorCollision* _this, ActorCollision* _other)override;
	virtual void CollisionExit(ActorCollision* _this, ActorCollision* _other)override;
};

