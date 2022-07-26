#include "stdafx.h"
#include "TitleOpenning.h"
#include"Render.h"
#include"Level.h"
#include"ActorCollision.h"

TitleOpenning::TitleOpenning()
{
}


TitleOpenning::~TitleOpenning()
{
}

void TitleOpenning::Init()
{
	m_AniRenderer = CreateRenderer<AniRenderer>();
	m_AniRenderer->SetSize(Vector2f(146.0f, 33.0f));
	m_AniRenderer->SetPivot(Vector2f(0.0f, 0.0f));
	m_AniRenderer->CreateAnimation(L"Click", L"TitleOpenning", 0, 1, true, 0.1f);
	m_AniRenderer->CreateAnimation(L"Notfocus", L"TitleOpenning", 0, 0, false);
	m_AniRenderer->CreateAnimation(L"focus", L"TitleOpenning", 1, 1, false);
	m_AniRenderer->ChangeAnimation(L"Notfocus");

	m_Collision = CreateCollision(L"TitleUI");
	m_Collision->SetSize(Vector2f(146.0f, 33.0f));
}

void TitleOpenning::PrevUpdate()
{
}

void TitleOpenning::Update()
{
}

void TitleOpenning::LateUpdate()
{
}

void TitleOpenning::OnClick()
{
	m_AniRenderer->ChangeAnimation(L"Click");
	ResourceManager::Instance().PlaySound(L"TitleButtonDown.wav");
}
void TitleOpenning::OnClickUp()
{
}

void TitleOpenning::CollisionEnter(ActorCollision * _this, ActorCollision * _other)
{
	m_AniRenderer->ChangeAnimation(L"focus");
}

void TitleOpenning::CollisionStay(ActorCollision * _this, ActorCollision * _other)
{
	if (_other->GetActor()->NameEqual(L"GameMouse"))
	{
		if (InputManager::Instance().IsDown(L"LMouse"))
		{
			OnClick();
		}
		if (InputManager::Instance().IsUp(L"LMouse"))
		{
			OnClickUp();
		}
	}
}

void TitleOpenning::CollisionExit(ActorCollision * _this, ActorCollision * _other)
{
	m_AniRenderer->ChangeAnimation(L"Notfocus");
}
