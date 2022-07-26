#include "stdafx.h"
#include "SoundPlayer.h"
#include"GameSound.h"


SoundPlayer::SoundPlayer() : m_Channel(nullptr), m_state(SoundState::SP_Stop)
{
}


SoundPlayer::~SoundPlayer()
{
}

bool SoundPlayer::IsPlay() const
{
	bool isPlaying;
	bool isPaused;
	m_Channel->isPlaying(&isPlaying);
	m_Channel->getPaused(&isPaused);
	return isPlaying && !isPaused;
}

void SoundPlayer::Play()
{
	if (!m_Channel)
	{
		return;
	}
	switch (m_state)
	{
	case SoundPlayer::SP_Play:
		Stop();
		ResourceManager::Instance().m_SoundSystem->playSound(m_Sound->GetSound(), nullptr, false, &m_Channel);
		break;
	case SoundPlayer::SP_Pause:
		m_Channel->setPaused(false);
		break;
	case SoundPlayer::SP_Stop:
		ResourceManager::Instance().m_SoundSystem->playSound(m_Sound->GetSound(), nullptr, false, &m_Channel);
		break;
	case SoundPlayer::SP_Max:
		break;
	default:
		break;
	}
	m_state = SP_Play;
}

void SoundPlayer::Pause()
{
	if (!m_Channel)
	{
		return;
	}
	m_Channel->setPaused(true);
	m_state = SP_Pause;
}

void SoundPlayer::Stop()
{
	m_Channel->stop();
	m_state = SP_Stop;
}

void SoundPlayer::SetLoop(bool isLoop)
{
	m_Sound->SetLoop(isLoop);

	unsigned int pick;
	m_Channel->getPosition(&pick, FMOD_TIMEUNIT_MS);
	if (m_state == SP_Play)
	{
		Stop();
		Play();
		m_Channel->setPosition(pick, FMOD_TIMEUNIT_MS);
	}

}

void SoundPlayer::ChangeSound(const wchar_t * _SoundFileName, bool isPlay)
{
	if (m_state != SP_Stop)
	{
		m_Channel->stop();
		m_state = SP_Stop;
	}

	m_Sound = ResourceManager::Instance().FindSound(_SoundFileName);
	if (nullptr == m_Sound)
	{
#ifdef _DEBUG
		wchar_t errString[1024];
		swprintf_s(errString, L"Fail Load ChangeSound, : %s", _SoundFileName);
		MessageBox(SystemClass::Instance().GetHWND(), errString, L"Error SoundLoad", MB_OK);
#endif
		return;
	}
	ResourceManager::Instance().m_SoundSystem->playSound(m_Sound->GetSound(), nullptr, !isPlay, &m_Channel);
	m_Channel->getPitch(&m_Pitch);
	m_state = isPlay ? SP_Play : SP_Pause;
}
