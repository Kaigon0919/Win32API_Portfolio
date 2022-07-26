#include "stdafx.h"
#include "TitleMain.h"
#include"Level.h"
#include"Render.h"
#include"SoundPlayer.h"
TitleMain::TitleMain()
{
}


TitleMain::~TitleMain()
{
}

void TitleMain::Init()
{
	Vector2i winSize = SystemClass::Instance().GetWindowsSize();
	SetPosition(winSize.GetHalfX(), winSize.GetHalfY());
	pRenderer = CreateRenderer<SingleRenderer>(-5);
	pRenderer->SettingSprite(L"title01.bmp");
	m_Sound = ResourceManager::Instance().CreateSoundPlayer();
	m_Sound->ChangeSound(L"Title.wav",true);
	m_Sound->SetLoop(true);
	//pRenderer->SetSize(Vector2f(1024.0f, 768.0f));
}

void TitleMain::PrevUpdate()
{
}

void TitleMain::Update()
{
}

void TitleMain::LateUpdate()
{
}

void TitleMain::StartSound()
{
	m_Sound->Play();
}

void TitleMain::StopSound()
{
	m_Sound->Stop();
}
