#pragma once
#include "UpdateBase.h"

class Actor;
class ActorSubBase :public UpdateBase
{
protected:
	ActorSubBase();
	~ActorSubBase();

public:
	friend Actor;

private:
	Actor* m_pActor;

protected:
	Vector2f m_Size;
	Vector2f m_Pivot;

private:
	void SetActor(Actor* _pActor)
	{
		m_pActor = _pActor;
	}
public:
	Actor* GetActor() const
	{
		return m_pActor;
	}
	virtual bool IsUpdate() const override;
	virtual bool IsDeath() const override;
public:
	inline Vector2f GetSize()const
	{
		return m_Size;
	}
	inline Vector2f GetPivot()const
	{
		return m_Pivot;
	}
	inline void SetSize(Vector2f _size)
	{
		m_Size = _size;
	}
	inline void SetPivot(Vector2f _pivot)
	{
		m_Pivot = _pivot;
	}

	Vector2f GetParentPos()const;
	Vector2f GetScreenPos()const;
};

