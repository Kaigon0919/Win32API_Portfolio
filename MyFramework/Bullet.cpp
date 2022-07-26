#include "stdafx.h"
#include "Bullet.h"
#include"Render.h"
#include"ResourceManager.h"
#include"ActorCollision.h"
#include"Level.h"

Bullet::Bullet() : m_DeathTimer(2.0f), m_MoveSpeed(200.0f), taget(0,0)
{
	SetName(L"Bullet");
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
	m_Renderer = CreateRenderer<SingleRenderer>();
	m_Renderer->SettingSprite(L"Character", 0);
	m_Renderer->SetSize(Vector2f(100, 100));

	ActorCollision* p = CreateCollision(L"PlayerBullet");
	p->SetSize(Vector2f(50, 50));
}

void Bullet::PrevUpdate()
{
}

void Bullet::Update()
{
	m_Position += taget*m_MoveSpeed * TimeManager::Instance().GetDeltaTime();
	if (true == m_DeathTimer.Check())
	{
		Death();
		m_DeathTimer.Reset();
	}
}

void Bullet::LateUpdate()
{
}

void Bullet::CollisionEnter(ActorCollision * _this, ActorCollision * _other)
{
}

void Bullet::CollisionStay(ActorCollision * _this, ActorCollision * _other)
{
}

void Bullet::CollisionExit(ActorCollision * _this, ActorCollision * _other)
{
}

void Bullet::OtherCollisionEnter(ActorCollision * _this, ActorCollision * _other)
{
}

void Bullet::OtherCollisionStay(ActorCollision * _this, ActorCollision * _other)
{
}

void Bullet::OtherCollisionExit(ActorCollision * _this, ActorCollision * _other)
{
}


