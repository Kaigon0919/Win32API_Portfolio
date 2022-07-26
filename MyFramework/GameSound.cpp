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
	// FMOD에서는 멀티바이트를 사용하므로 멀티바이트로 변경시킨다.
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
