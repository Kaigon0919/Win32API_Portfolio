#pragma once
#include "Actor.h"

class AniRenderer;
class HitEffectActor : public Actor
{
public:
	HitEffectActor();
	~HitEffectActor();

private:
	AniRenderer* m_Effect;

public:
	virtual void Init() override;
	virtual void Update() override;
};