#include "stdafx.h"
#include "TimeHelper.h"
#include "TimeManager.h"


TimeHelper::TimeHelper(float _Time) : m_Time(_Time), m_CurTime(0.0f), m_IsDead(false)
{
}


TimeHelper::~TimeHelper()
{
}

void TimeHelper::Reset()
{
	m_CurTime = 0.0f;
	m_IsDead = false;
}

bool TimeHelper::Check()
{
	if (m_IsDead)
	{
		return false;
	}

	m_CurTime += TimeManager::Instance().GetDeltaTime();

	if (m_CurTime >= m_Time)
	{
		return true;
	}

	return false;
}