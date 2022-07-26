#include "stdafx.h"
#include "MainBullet.h"
#include"Bullet.h"
#include"SubBullet.h"
#include"Level.h"


MainBullet::MainBullet() : m_Bullet(nullptr), isFirstUpdate(false)
{
}


MainBullet::~MainBullet()
{
}

void MainBullet::Init()
{
	m_Bullet = GetLevel()->CreateActor<Bullet>();
	//m_Bullet->Off();
}

void MainBullet::PrevUpdate()
{
	if (!isFirstUpdate)
	{
		m_Bullet->SetPosition(m_Position);

		Vector2i mousePos = Vector2i(GetLevel()->GetMouseConvertPosition().GetIntX(), GetLevel()->GetMouseConvertPosition().GetIntY());
		taget = Vector2f(mousePos.x - m_Position.x, mousePos.y - m_Position.y);
		taget.normalize();
		m_Bullet->SetTaget(taget);
		m_Bullet->UpdateOn();
		isFirstUpdate = true;
	}
}

void MainBullet::Update()
{
}

void MainBullet::LateUpdate()
{
	if (m_Bullet->IsDeath())
	{
		SubBullet* newBullet = GetLevel()->CreateActor<SubBullet>();
		newBullet->SetPosition(m_Bullet->GetPosition());
		newBullet->SetTaget(taget);
		Death();
	}
	if (!m_Bullet->IsUpdate())
	{
		m_Bullet->Death();
		Death();
	}
}
