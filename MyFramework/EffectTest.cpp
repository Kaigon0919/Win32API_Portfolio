#include "stdafx.h"
#include "EffectTest.h"
#include"Render.h"
#include"ActorCollision.h"
#include"Level.h"

EffectTest::EffectTest()
{
}


EffectTest::~EffectTest()
{
}

void EffectTest::Init()
{
	m_AniRenderer = CreateRenderer<AniRenderer>();
	m_AniRenderer->SetSize(Vector2f(256.0f, 256.0f));
	m_AniRenderer->SetPivot(Vector2f(0.0f, 0.0f));
	m_AniRenderer->CreateAnimation(L"effect1", L"effect2", 0, 9*8);
	m_AniRenderer->ChangeAnimation(L"effect1");

	SetPosition(600, 400);

	AnimationSetting();
}

void EffectTest::PrevUpdate()
{
}

void EffectTest::Update()
{
}

void EffectTest::LateUpdate()
{
}

void EffectTest::CollisionEnter(ActorCollision * _this, ActorCollision * _other)
{
}

void EffectTest::CollisionStay(ActorCollision * _this, ActorCollision * _other)
{
}

void EffectTest::CollisionExit(ActorCollision * _this, ActorCollision * _other)
{
}

void EffectTest::OtherCollisionEnter(ActorCollision * _this, ActorCollision * _other)
{
}

void EffectTest::OtherCollisionStay(ActorCollision * _this, ActorCollision * _other)
{
}

void EffectTest::OtherCollisionExit(ActorCollision * _this, ActorCollision * _other)
{
}

void EffectTest::AnimationSetting()
{
}
