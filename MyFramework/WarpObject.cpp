#include "stdafx.h"
#include "WarpObject.h"
#include"Render.h"
#include"ActorCollision.h"
#include"Level.h"
WarpObject::WarpObject()
{
}


WarpObject::~WarpObject()
{
}

void WarpObject::Init()
{
	SetName(L"Warp");
	pRenderer = CreateRenderer<SingleRenderer>(-1);
	pRenderer->SettingSprite(L"warp1.bmp");

	m_Collision = CreateCollision(L"Warp");
	m_Collision->SetSize(pRenderer->GetSize());
}

void WarpObject::CollisionEnter(ActorCollision * _this, ActorCollision * _other)
{
}

void WarpObject::CollisionStay(ActorCollision * _this, ActorCollision * _other)
{
}

void WarpObject::CollisionExit(ActorCollision * _this, ActorCollision * _other)
{
}

void WarpObject::SetActive(bool isActive)
{
	if (pRenderer)
	{
		pRenderer->SetUpdate(isActive);
	}
	if (m_Collision)
	{
		m_Collision->SetUpdate(isActive);
	}
	SetUpdate(isActive);

}

void WarpObject::OnWarp(Actor * player)
{
	SystemClass::Instance().ChangeLevel(nextLevel);
	player->SetPosition(nextLevelPosition);
}
