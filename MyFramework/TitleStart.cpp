#include "stdafx.h"
#include "TitleStart.h"
#include"Render.h"
#include"Level.h"
#include"ActorCollision.h"

TitleStart::TitleStart()
{
}


TitleStart::~TitleStart()
{
}

void TitleStart::Init()
{
	m_AniRenderer = CreateRenderer<AniRenderer>();
	m_AniRenderer->SetSize(Vector2f(146.0f, 33.0f));
	m_AniRenderer->SetPivot(Vector2f(0.0f, 0.0f));
	m_AniRenderer->CreateAnimation(L"Notfocus", L"TitleStart", 0, 0, false);
	m_AniRenderer->CreateAnimation(L"focus", L"TitleStart", 1, 1, false);
	m_AniRenderer->CreateAnimation(L"Click", L"TitleStart", 0, 1, true);
	m_AniRenderer->ChangeAnimation(L"Notfocus");

	m_Collision = CreateCollision(L"TitleUI");
	m_Collision->SetSize(Vector2f(146.0f, 33.0f));
}

void TitleStart::PrevUpdate()
{
}

void TitleStart::Update()
{
}

void TitleStart::LateUpdate()
{
}
void TitleStart::OnClick()
{
	m_AniRenderer->ChangeAnimation(L"Click");
	ResourceManager::Instance().PlaySound(L"TitleButtonDown.wav");
	SystemClass::Instance().ChangeLevel(ALLSTATE::Village);
}
void TitleStart::OnClickUp()
{
}

void TitleStart::CollisionEnter(ActorCollision * _this, ActorCollision * _other)
{
	m_AniRenderer->ChangeAnimation(L"focus");
}

void TitleStart::CollisionStay(ActorCollision * _this, ActorCollision * _other)
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

void TitleStart::CollisionExit(ActorCollision * _this, ActorCollision * _other)
{
	m_AniRenderer->ChangeAnimation(L"Notfocus");
}
