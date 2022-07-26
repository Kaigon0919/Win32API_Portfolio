#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	m_Timer.Update();
	m_Timer.FpsUpdate();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Timer Function.
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

TimeManager::Timer::Timer() : Count(), CurTime(), PrevTime(), deltaTime(0), fps(0), frameCountAcc(0), fpsTimeAcc(0.0f)
{
	// Cpu�� 1�� ���� �� �� �ִ� Count�� �����´�.
	QueryPerformanceFrequency(&Count);

	// Cpu�� ���ݱ��� ������ Count�� �����´�.
	QueryPerformanceCounter(&CurTime);
	PrevTime = CurTime;

}

TimeManager::Timer::~Timer()
{}

void TimeManager::Timer::Update()
{
	QueryPerformanceCounter(&CurTime);
	// (���� ������ ���� ���� - �� ������ ��������) / 1�� ���� ���� �ִ� ���� = �� �����Ӱ� �� �������� �ð� ��.
	deltaTime = (CurTime.QuadPart - PrevTime.QuadPart) / (float)Count.QuadPart;
	PrevTime = CurTime;
}

void TimeManager::Timer::FpsUpdate()
{
	// ������ ����.
	++frameCountAcc;

	// �ð� ����.
	fpsTimeAcc += deltaTime;

	// 1�ʰ� �����ٸ�.
	if (fpsTimeAcc >= 1.0f)
	{
		// Frame per second => Frame / sec
		fps = (int)(frameCountAcc / fpsTimeAcc);
		frameCountAcc = 0;
		fpsTimeAcc = 0.0f; // Line 54 ���� 1�� �������� - 1.0 �� ���ָ� ������ fpsTimeAcc�� �������� 0�����Ѵ�.
	}
}
