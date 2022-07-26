#pragma once
#include "Actor.h"
#include"TimeHelper.h"
class SingleRenderer;
class DamageNumber : public Actor
{
public:
	DamageNumber();
	~DamageNumber();

private:
	size_t m_Value;
	size_t NumberCount;
	std::wstring SpriteName;
	std::vector<SingleRenderer*> m_VecRender;
	std::vector<int> m_VecValue;
	TimeHelper time_delete;

	Vector2f velocity;
	Vector2f acceleration;
	const Vector2f gravity;
public:
	inline void SetValue(size_t value)
	{
		m_Value = value;
	}
	inline void SetVelocity(Vector2f vel)
	{
		velocity = vel;
	}
public:
	virtual void Update() override;
public:
	void InitSetting(size_t numberCount, const wchar_t* spriteName, Vector2f imageSize, int damage);
	void ValueToRenderUpdate();

	// Actor을(를) 통해 상속됨
	virtual void Init() override;
};

