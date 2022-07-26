#include "stdafx.h"
#include "TitleQuit.h"
#include"Render.h"
#include"Level.h"
#include"ActorCollision.h"
TitleQuit::TitleQuit()
{
}


TitleQuit::~TitleQuit()
{
}

void TitleQuit::Init()
{

	m_AniRenderer = CreateRenderer<AniRenderer>();
	m_AniRenderer->SetSize(Vector2f(146.0f, 33.0f));
	m_AniRenderer->SetPivot(Vector2f(0.0f, 0.0f));
	m_AniRenderer->CreateAnimation(L"Notfocus", L"TitleQuit", 0, 0, false);
	m_AniRenderer->CreateAnimation(L"focus", L"TitleQuit", 1, 1, false);
	m_AniRenderer->CreateAnimation(L"Click", L"TitleQuit", 0, 1, true);
	m_AniRenderer->ChangeAnimation(L"Notfocus");

	m_Collision = CreateCollision(L"TitleUI");
	m_Collision->SetSize(Vector2f(146.0f, 33.0f));
}

void TitleQuit::PrevUpdate()
{
}

void TitleQuit::Update()
{
}

void TitleQuit::LateUpdate()
{
}
void TitleQuit::OnClick()
{
	m_AniRenderer->ChangeAnimation(L"Click");
	ResourceManager::Instance().PlaySound(L"TitleButtonDown.wav");
	PostMessage(SystemClass::Instance().GetHWND(), WM_CLOSE, 0, 0);
}
void TitleQuit::OnClickUp()
{
}

void TitleQuit::CollisionEnter(ActorCollision * _this, ActorCollision * _other)
{
	m_AniRenderer->ChangeAnimation(L"focus");
}

void TitleQuit::CollisionStay(ActorCollision * _this, ActorCollision * _other)
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

void TitleQuit::CollisionExit(ActorCollision * _this, ActorCollision * _other)
{
	m_AniRenderer->ChangeAnimation(L"Notfocus");
}
