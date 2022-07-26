#include "stdafx.h"
#include "SubBullet.h"
#include "Level.h"
#include "Bullet.h"

SubBullet::SubBullet() : m_vecBullet(8), isFirstUpdate(false)
{
}


SubBullet::~SubBullet()
{
}

void SubBullet::Init()
{
	for (size_t i = 0; i < m_vecBullet.size(); ++i)
	{
		m_vecBullet[i] = GetLevel()->CreateActor<Bullet>();
		m_vecBullet[i]->UpdateOff();
	}
}

void SubBullet::PrevUpdate()
{
	if (!isFirstUpdate)
	{
		for (size_t i = 0; i < m_vecBullet.size(); ++i)
		{
			m_vecBullet[i]->SetPosition(m_Position);
			taget.Rotate(360.0f / m_vecBullet.size());
			m_vecBullet[i]->SetTaget(taget);
			m_vecBullet[i]->UpdateOn();
			isFirstUpdate = true;
		}
	}
}

void SubBullet::Update()
{
}

void SubBullet::LateUpdate()
{
	for (size_t i = 0; i < m_vecBullet.size(); i++)
	{
		if (m_vecBullet[i]->IsDeath())
		{
			continue;
		}
		return;
	}

	Death();

}
