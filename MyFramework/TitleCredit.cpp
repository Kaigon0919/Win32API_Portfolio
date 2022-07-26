#include "stdafx.h"
#include "TitleCredit.h"
#include"Render.h"
#include"Level.h"
#include"ActorCollision.h"

TitleCredit::TitleCredit()
{
}


TitleCredit::~TitleCredit()
{
}

void TitleCredit::Init()
{
	m_AniRenderer = CreateRenderer<AniRenderer>();
	m_AniRenderer->SetSize(Vector2f(146.0f, 33.0f));
	m_AniRenderer->SetPivot(Vector2f(0.0f, 0.0f));
	m_AniRenderer->CreateAnimation(L"Click", L"TitleCredit", 0, 1, true, 0.1f);
	m_AniRenderer->CreateAnimation(L"Notfocus", L"TitleCredit", 0, 0, false);
	m_AniRenderer->CreateAnimation(L"focus", L"TitleCredit", 1, 1, false);
	m_AniRenderer->ChangeAnimation(L"Notfocus");

	m_Collision = CreateCollision(L"TitleUI");
	m_Collision->SetSize(Vector2f(146.0f, 33.0f));
}

void TitleCredit::PrevUpdate()
{
}

void TitleCredit::Update()
{
}

void TitleCredit::LateUpdate()
{
}

void TitleCredit::OnClick()
{
	m_AniRenderer->ChangeAnimation(L"Click");
	ResourceManager::Instance().PlaySound(L"TitleButtonDown.wav");
	SystemClass::Instance().ChangeLevel(ALLSTATE::EDIT);

}
void TitleCredit::OnClickUp()
{
}

void TitleCredit::CollisionEnter(ActorCollision * _this, ActorCollision * _other)
{
	m_AniRenderer->ChangeAnimation(L"focus");
}

void TitleCredit::CollisionStay(ActorCollision * _this, ActorCollision * _other)
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

void TitleCredit::CollisionExit(ActorCollision * _this, ActorCollision * _other)
{
	m_AniRenderer->ChangeAnimation(L"Notfocus");
}
