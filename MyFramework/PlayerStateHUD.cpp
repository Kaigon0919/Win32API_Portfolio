#include "stdafx.h"
#include "PlayerStateHUD.h"
#include "Level.h"
#include"Render.h"
#include"BattlePawn.h"

PlayerStateHUD::PlayerStateHUD()
{
}


PlayerStateHUD::~PlayerStateHUD()
{
}

void PlayerStateHUD::Init(BattlePawn * _Pawn, float * _CurHp, float _MaxHp, float * _CurMp, float _MaxMp,float * _CurSp, float _MaxSp, Vector2f _Pivot, Vector2f _Size)
{
	m_Size = _Size;
	m_Pivot = _Pivot;

	Vector2f m_fPivot = m_Pivot;

	m_fPivot.x += 71.0f;
	m_fPivot.y -= 39;

	m_HpBar.Init(_Pawn, _CurHp, _MaxHp, m_fPivot, Vector2f(120.0f, 18.0f), 2,false);

	m_fPivot = m_Pivot;
	m_fPivot.x += 71.0f;
	m_fPivot.y -= 16.0f;
	m_MpBar.Init(_Pawn, _CurMp, _MaxMp, m_fPivot, Vector2f(120.0f, 18.0f),2, false);
	m_MpBar.SetUpSprite(L"Mp.bmp");

	m_fPivot = m_Pivot;
	m_fPivot.x += 71.0f;
	m_fPivot.y += 7.0f;
	m_SpBar.Init(_Pawn, _CurSp, _MaxSp, m_fPivot, Vector2f(120.0f, 18.0f),2, false);
	m_SpBar.SetUpSprite(L"Sp.bmp");

	m_Back = _Pawn->CreateRenderer<SingleRenderer>(13);
	m_Back->SettingSprite(L"StateBack.bmp");
	m_Back->SetPivot(_Pivot);
	m_Back->SetSize(_Size);

	m_Up = _Pawn->CreateRenderer<SingleRenderer>(19);
	m_Up->SettingSprite(L"State.bmp");
	m_Up->SetPivot(_Pivot);
	m_Up->SetSize(_Size);
}

void PlayerStateHUD::Update()
{
	m_HpBar.Update();
	m_MpBar.Update();
	m_SpBar.Update();
}
