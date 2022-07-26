#pragma once

// std Header
#include<list>

// user Header
#include"MathData.h"
#include"NameBase.h"


class SystemClass;
class Level;
class ActorRenderer;
class ActorCollision;
class Actor : public NameBase
{
protected:
	Actor();
	virtual ~Actor();

public:
	friend class Level;
	friend class SystemClass;
private:
	Level * m_Level;
	bool m_StateOver;

protected:
	Vector2f m_Position;
	float m_ScaleRatio;

// Get,Set Function.
private: 
	inline void SetLevel(Level * _level)
	{
		m_Level = _level;
	}

public: 
	inline void SetPosition(const Vector2f& ref)
	{
		m_Position = ref;
	}
	inline void SetPosition(const float& _x , const float& _y)
	{
		m_Position.x = _x;
		m_Position.y = _y;
	}
	inline Vector2f GetPosition()const
	{
		return m_Position;
	}
	inline Level* GetLevel() const
	{
		return m_Level;
	}
	inline void SetScale(const float& _scale)
	{
		m_ScaleRatio = _scale;
	}
	inline float GetSclae()const
	{
		return m_ScaleRatio;
	}
	Vector2f GetScreenPosition()const;

// Function.
public:
	virtual void Init() = 0;
	virtual void PrevUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void DebugRender();
	virtual void AfterRender();

public:
	bool IsStateOver()
	{
		return m_StateOver;
	}

	template<typename... Rest>
	void StateOverOn(Rest ..._Arg)
	{
		if (0 >= sizeof...(_Arg))
		{
			return;
		}

		Level::PushOver(this);
		m_StateOver = true;

		StateOverPush(_Arg...);
	}

	template<typename... Rest>
	void StateOverPush(ALLSTATE T, Rest ..._Arg)
	{
		SystemClass::Instance().PushActor(T, this);
		StateOverPush(_Arg...);
	}

	void StateOverPush(){	}


////////////////////////////////////////////////////////////////////////////
//Renderer                                                                //
////////////////////////////////////////////////////////////////////////////

private:
	std::list<ActorRenderer*> m_RenderList;
public:
	template<class T>
	T* CreateRenderer(int _Order = 0)
	{
		T* newRenderer = new T();
		newRenderer->Order(_Order);
		newRenderer->SetActor(this);
		m_RenderList.push_back(newRenderer);
		m_Level->PushRenderer(_Order, newRenderer);
		return newRenderer;
	}
////////////////////////////////////////////////////////////////////////////
//Collision                                                               //
////////////////////////////////////////////////////////////////////////////
private:
	std::list<ActorCollision*> m_pCollisionList;

public:
	ActorCollision* CreateCollision(const wchar_t*_GroupName, int _Type = 0);
public:
	virtual void CollisionEnter(ActorCollision* _this, ActorCollision* _other) {}
	virtual void CollisionStay(ActorCollision* _this, ActorCollision* _other) {}
	virtual void CollisionExit(ActorCollision* _this, ActorCollision* _other) {}

	virtual void OtherCollisionEnter(ActorCollision* _this, ActorCollision* _other) {}
	virtual void OtherCollisionStay(ActorCollision* _this, ActorCollision* _other) {}
	virtual void OtherCollisionExit(ActorCollision* _this, ActorCollision* _other) {}

};

