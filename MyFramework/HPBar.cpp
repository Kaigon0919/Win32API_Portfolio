#include "stdafx.h"
#include "HPBar.h"
#include"Render.h"
#include"BattlePawn.h"
#include"Level.h"

HPBar::HPBar()
{
}


HPBar::~HPBar()
{
}

void HPBar::Init(BattlePawn * pawn, float * curHp, float maxHp, Vector2f pivot, Vector2f size,int orderOffset, bool back)
{
	m_MaxHp = maxHp;
	m_CurHp = curHp;
	m_Size = size;
	m_Pivot = pivot;

	if (back == true)
	{
		m_Back = pawn->CreateRenderer<SingleRenderer>(14 + orderOffset);
		m_Back->SettingSprite(L"HpBack.bmp");
		m_Back->SetPivot(pivot);
		m_Back->SetSize(size);
	}

	m_Up = pawn->CreateRenderer<SingleRenderer>(16 + orderOffset);
	m_Up->SettingSprite(L"Hp.bmp");
	m_Up->SetPivot(pivot);
	m_Up->SetSize(size);
}

void HPBar::SetSprite(const wchar_t * _BackImage, const wchar_t * _UpImage)
{
	m_Up->SettingSprite(_UpImage);
	m_Up->SetPivot(m_Pivot);
	m_Up->SetSize(m_Size);

	m_Back->SettingSprite(_BackImage);
	m_Back->SetPivot(m_Pivot);
	m_Back->SetSize(m_Size);
}

void HPBar::SetUpSprite(const wchar_t * _UpImage)
{
	m_Up->SettingSprite(_UpImage);
	m_Up->SetPivot(m_Pivot);
	m_Up->SetSize(m_Size);
}

void HPBar::SetBackSprite(const wchar_t * _BackImage)
{
	m_Back->SettingSprite(_BackImage);
	m_Back->SetPivot(m_Pivot);
	m_Back->SetSize(m_Size);
}

void HPBar::SetActive(bool isActive)
{
	if (m_Back)
	{
		m_Back->SetUpdate(isActive);
	}
	if (m_Up)
	{
		m_Up->SetUpdate(isActive);
	}
}

void HPBar::Update()
{
	m_Up->SetSize({ m_Size.x * (*m_CurHp) / m_MaxHp,  m_Size.y });

	float X = ((m_MaxHp - (*m_CurHp)) / m_MaxHp * m_Size.x) * 0.5F;
	m_Up->SetPivot({ -X + m_Pivot.x,  m_Pivot.y });
}
