#pragma once
#include "Actor.h"
class AniRenderer;
class TitleQuit :public Actor
{
public:
	TitleQuit();
	~TitleQuit();

private:
	AniRenderer* m_AniRenderer;
	ActorCollision* m_Collision;
public:
	// Actor��(��) ���� ��ӵ�
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

