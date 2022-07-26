#pragma once
#include "Actor.h"
#include"BattlePawn.h"
#include"TimeHelper.h"
#include"HPBar.h"

class Player;
class AniRenderer;
class Monster : public BattlePawn
{
public:
	Monster();
	~Monster();
protected:
	enum MonsterState
	{
		Mon_Idle, Mon_Move, Mon_Partrol, Mon_Attack, Mon_Hit, Mon_Dead, StateMax
	};
	enum MonsterDir
	{
		LeftDown, RightDown, LeftTop, RightTop, DirMax
	};

	
public:
	
	enum MonsterType
	{
		Monster4,
		Monster5,
		Monster25,
		Monster213,
		Monster243,
		Monster245,
		Monster248,
		Monster441,
		Monster504,
		Monster512,
		Max
	};
	enum MonsterAttackType
	{
		MAT_Melee,
		MAT_Range,
		MAT_Max
	};
	struct OutputMonsterData
	{
	public:
		Vector2f _position;
		MonsterType _type;
	};
protected:
	MonsterState m_State;
	MonsterDir m_Dir;
	std::wstring m_StateString[MonsterState::StateMax];
	std::wstring m_DirString[MonsterDir::DirMax];

	Player * m_Player;
	Vector2f m_MoveTaget;
	float m_MoveSpeed;

	float m_FindRange;
	float m_TrackRange;

	MonsterType m_MonsterType;
	MonsterAttackType m_AttType;

	TimeHelper time_Partrol;
	TimeHelper time_Att;
	TimeHelper time_Deadtime;

	int m_ArrowType;

	HPBar m_HpBar;
protected:
	void DirUpdate();
	void ChangeDir(MonsterDir _newDir);
	virtual void Attack(BattlePawn * taget);
public:
	inline void SetPlayer(Player* _player)
	{
		m_Player = _player;
	}
	inline void SetAttTimeHelper(float time)
	{
		time_Att.SetTime(time);
	}
	static const wchar_t* MonsterTypeName(MonsterType _type);
	inline MonsterType GetMonsterType()const
	{
		return m_MonsterType;
	}
public:
	void InitStateSetting(MonsterType type);
	void InitStateSetting(MonsterType type ,float maxHP , float moveSpeed, float att, float attRange, float findRange, float trackRange);
	void ImageSetting(Vector2f size = Vector2f(256.0f, 512.0f), Vector2f pivot = Vector2f(0.0f, 0.0f));
	void ColSetting(Vector2f size, Vector2f pivot);
	void AnimationSetting(const wchar_t * imgName, Vector2i AniIdleIdx, Vector2i AniMoveIdx, Vector2i AniPartorlIdx, Vector2i AniAttackIdx, Vector2i AniHitIdx, Vector2i AniDeadIdx);
private:
	void(Monster::*StateFunc)();
public:
	virtual void Init() override;
	virtual void PrevUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

	virtual void ProcessDamage(float _damage)override;
private:
	void MonsterTypeSetting(MonsterType type);

	// State Func.
	virtual void ChangeState(MonsterState _newState);
	virtual void IdleFunc();
	virtual void MoveFunc();
	virtual void PartrolFunc();
	virtual void AttackFunc();
	virtual void HitFunc();
	virtual void DeadFunc();
	virtual void MeleeAttack();
	virtual void RangeAttack();
public:
	void DamageHUD(Vector2f pos, Vector2f vel);
};