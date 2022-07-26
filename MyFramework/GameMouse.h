#pragma once
#include "Actor.h"
#include<list>
#include"TimeHelper.h"

class AniRenderer;
class ActorCollision;
class Player;
class GameMouse : public Actor
{
public:
	GameMouse();
	~GameMouse();
private: // inner enum
	enum MouseState {
		Default,
		DefaultClick,
		Hand,
		Warp,
		NotMove,
		Attack,
		AttackClick,
		MagicSkill,
		PhysicSkill,
		Max
	};
private:
	AniRenderer* pRenderer;
	ActorCollision * m_Collision;
	MouseState m_State;
	std::wstring StateString[MouseState::Max];

	std::list<ActorCollision*> ColList;
	Actor * m_TagetActor;
	TimeHelper initWatingTime;

private:
	void(GameMouse::*StateFunc)();
public:
	virtual void Init() override;
	virtual void PrevUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	virtual void CollisionEnter(ActorCollision* _this, ActorCollision* _other)override;
	virtual void CollisionStay(ActorCollision* _this, ActorCollision* _other)override;
	virtual void CollisionExit(ActorCollision* _this, ActorCollision* _other)override;

private:
	void AnimaitionSetting();
	void ChageState(MouseState _newState);
public:
	inline void WatingTimeReset()
	{
		initWatingTime.Reset();
	}

// State Func.
private:
	void DefaultFunc();
	void DefaultClickFunc();
	void WarpFunc();
	void AttackFunc();
	void AttackClickFunc();
	void HandFunc();

private:
	Player* m_Player;

public:
	void SetPlayer(Player* _player);
};

