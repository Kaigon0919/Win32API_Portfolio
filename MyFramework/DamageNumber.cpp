#include "stdafx.h"
#include "DamageNumber.h"
#include"Render.h"
#include"Level.h"
DamageNumber::DamageNumber() : time_delete(0.8f), gravity(0.0f, 9.8f), velocity()
{

}


DamageNumber::~DamageNumber()
{
}

void DamageNumber::Update()
{
	if (time_delete.Check())
	{
		Death();
	}
	velocity = velocity + gravity*TimeManager::Instance().GetDeltaTime();
	m_Position += velocity;
}

void DamageNumber::InitSetting(size_t numberCount, const wchar_t * spriteName, Vector2f imageSize, int damage)
{
	m_Value = damage;
	NumberCount = numberCount;
	m_VecRender.reserve(NumberCount);
	m_VecValue.reserve(NumberCount);
	SpriteName = spriteName;

	for (size_t i = 0; i < NumberCount; ++i)
	{
		SingleRenderer* newRender = CreateRenderer<SingleRenderer>(100);
		newRender->SettingSprite(spriteName, 0);
		newRender->SetSize(imageSize);
		newRender->SetPivot({ 20.0f * i, 0.0f });
		newRender->CameraMode(true);

		m_VecValue.push_back(0);
		m_VecRender.push_back(newRender);
	}
	ValueToRenderUpdate();
}

void DamageNumber::ValueToRenderUpdate()
{
	size_t tempValue = m_Value;
	int count = 0;
	while (tempValue != 0)
	{
		tempValue /= 10;
		++count;
	}

	if (count > NumberCount)
	{
		for (size_t i = 0; i < NumberCount; ++i)
		{
			m_VecValue[i] = 9;
		}
	}
	else
	{
		int divNumber = 1;
		for (int i = 0; i < count - 1; ++i)
		{
			divNumber *= 10;
		}

		for (int i = 0; i < NumberCount - count; ++i)
		{
			m_VecValue[i] = 0;
			m_VecRender[i]->SetUpdate(false);
		}

		tempValue = m_Value;
		count = (int)NumberCount - count;

		while (count < NumberCount)
		{
			m_VecRender[count]->SetUpdate(true);
			m_VecValue[count] = (int)tempValue / divNumber;
			tempValue -= m_VecValue[count] * divNumber;
			divNumber /= 10;
			++count;
		}
	}

	for (size_t i = 0; i < NumberCount; ++i)
	{
		m_VecRender[i]->SettingSprite(SpriteName.c_str(), m_VecValue[i]);
	}
}

void DamageNumber::Init()
{
}
