#pragma once
#include<fmod.hpp>


class GameSound;
class SoundPlayer
{
private:
	SoundPlayer();
	~SoundPlayer();
public:
	friend class ResourceManager;
private:
	enum SoundState
	{
		SP_Play,
		SP_Pause,
		SP_Stop,
		SP_Max
	};
private:
	GameSound * m_Sound;
	FMOD::Channel* m_Channel;
	float m_Pitch;
	SoundState m_state;
public:
	inline float GetPitch()const
	{
		return m_Pitch;
	}
	inline void SetPitch(float _PitchValue)
	{
		m_Pitch = _PitchValue;
		m_Channel->setPitch(m_Pitch);
	}
	bool IsPlay()const;

public:
	void Play();
	void Pause();
	void Stop();
	void SetLoop(bool isLoop);
	void ChangeSound(const wchar_t * _SoundFileName, bool isPlay = false);

};

