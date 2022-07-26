#include "stdafx.h"
#include "HitEffectActor.h"
#include"Render.h"
#include"Level.h"


HitEffectActor::HitEffectActor()
{
}


HitEffectActor::~HitEffectActor()
{
}

void HitEffectActor::Init()
{
	m_Effect = CreateRenderer<AniRenderer>(2);
	m_Effect->SetSize(Vector2f(128.0f, 128.0f));
	m_Effect->SetPivot(Vector2f(0.0f, 0.0f));
	m_Effect->CreateAnimation(L"HitAni", L"HitEffect", 0, 3,false);
	m_Effect->ChangeAnimation(L"HitAni");
}

void HitEffectActor::Update()
{
	if (m_Effect->IsEnd())
	{
		this->Death();
	}
}
