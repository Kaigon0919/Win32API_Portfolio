#include "stdafx.h"

#include<atlstr.h>

#include "GameSound.h"
#include"ResourceManager.h"

GameSound::GameSound() : m_Length(0)
{
}


GameSound::~GameSound()
{
}

bool GameSound::Load(const wchar_t * _filePath, bool isLoop)
{
	// FMOD������ ��Ƽ����Ʈ�� ����ϹǷ� ��Ƽ����Ʈ�� �����Ų��.
	std::string path = CW2A(_filePath);
	
	FMOD_MODE mode = FMOD_DEFAULT;
	if (isLoop)
	{
		mode = FMOD_LOOP_NORMAL;
	}
	if (FMOD_OK != ResourceManager::Instance().m_SoundSystem->createSound(path.c_str(), mode, nullptr, &m_Sound))
	{
		return false;
	}
	
	m_Sound->getLength(&m_Length, FMOD_TIMEUNIT_MS);
	return true;
}

void GameSound::SetLoop(const bool isLoop)
{
	FMOD_MODE mode = FMOD_LOOP_OFF;
	if (isLoop)
	{
		mode = FMOD_LOOP_NORMAL;
	}
	m_Sound->setMode(mode);
}
