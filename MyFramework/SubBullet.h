#pragma once
#include "Actor.h"
#include"TimeHelper.h"

class Bullet;
class SubBullet : public Actor
{
public:
	SubBullet();
	~SubBullet();

private:
	Vector2f taget;
	std::vector<Bullet*> m_vecBullet;
	bool isFirstUpdate;
public:
	virtual void Init() override;
	virtual void PrevUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	void SetTaget(const Vector2f& ref)
	{
		taget = ref;
	}
};

