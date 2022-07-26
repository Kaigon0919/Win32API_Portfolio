#pragma once
#include "Actor.h"
class SoundPlayer;
class SingleRenderer;
class TitleMain : public Actor
{
public:
	TitleMain();
	~TitleMain();
private:
	SingleRenderer* pRenderer;
	SoundPlayer* m_Sound;
public:
	virtual void Init() override;
	virtual void PrevUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public:
	void StartSound();
	void StopSound();
};

