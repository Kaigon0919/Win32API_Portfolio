#pragma once
#include"Actor.h"
#include"TimeHelper.h"

class Bullet;
class MainBullet : public Actor
{
public:
	MainBullet();
	~MainBullet();
private:
	Vector2f taget;
	Bullet* m_Bullet;
	bool isFirstUpdate;
public:
	virtual void Init() override;
	virtual void PrevUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
};

