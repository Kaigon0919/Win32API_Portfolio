#pragma once
#include<fmod.hpp>

class GameSound
{
public:
	GameSound();
	~GameSound();
private:
	FMOD::Sound* m_Sound;
	unsigned int m_Length;
public:
	FMOD::Sound* GetSound()const
	{
		return m_Sound;
	}
	unsigned int GetLength()const
	{
		return m_Length;
	}
public:
	bool Load(const wchar_t * _filePath, const bool isLoop = false);
	void SetLoop(const bool isLoop);
};

