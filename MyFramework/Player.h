#pragma once
#include "Actor.h"
#include"BattlePawn.h"
#include"TimeHelper.h"
#include"PlayerStateHUD.h"

class Monster;
class SoundPlayer;
class PlayerBackGround;
class Player : public BattlePawn
{
public:
	Player();
	~Player();
private:
	enum PlayerState
	{
		Idle, BattleIdle, Walk, Run, Attack1, Attack2, Rush, Sit, Hit, Dead,AttackRun,Skill1, Skill2, PlayerStateMax
	};
	enum PlayerDir
	{
		LeftDown, Down, RightDown, Left, Right, LeftTop, Top, RightTop, PlayerDirMax
	};
private:

	Vector2f m_MoveTaget;
	float m_MoveSpeed;
	Vector2f m_ColPoint[8];
	PlayerState m_State;
	PlayerDir m_Dir;
	std::wstring m_StateString[PlayerState::PlayerStateMax];
	std::wstring m_DirString[PlayerDir::PlayerDirMax];

	Vector2f m_CameraToPlayer;
	
	std::wstring backSoundName;
	SoundPlayer* m_BackGoundSound;

	BattlePawn* m_AttackTaget;

	bool m_isBattle;

	PlayerStateHUD m_StateHUD;

	AniRenderer * m_SkillRender;

	// Actor Data.
	PlayerBackGround* m_BackGround;
	// TimeEvent
	TimeHelper time_att1e1;
	TimeHelper time_att1e2;
	TimeHelper time_skill1;
private:
	float m_MaxSp;
	float m_MaxMp;
	float m_CurSp;
	float m_CurMp;

	size_t SkillCount;
	float m_Skill1Range;
	std::set<Monster*> * m_FieldMonsters;

private:
	void(Player::*StateFunc)();

public:
	const wchar_t* GetCurStateName()const
	{
		switch (m_State)
		{
		case Player::Idle:
			return m_StateString[(int)Player::Idle].c_str();
		case Player::BattleIdle:
			return m_StateString[(int)Player::BattleIdle].c_str();
		case Player::Walk:
			return m_StateString[(int)Player::Walk].c_str();
		case Player::Run:
			return m_StateString[(int)Player::Run].c_str();
		case Player::Attack1:
			return m_StateString[(int)Player::Attack1].c_str();
		case Player::Attack2:
			return m_StateString[(int)Player::Attack2].c_str();
		case Player::Dead:
			return m_StateString[(int)Player::Dead].c_str();
		case Player::Skill1:
			return m_StateString[(int)Player::Skill1].c_str();
		case Player::Skill2:
			return m_StateString[(int)Player::Skill2].c_str();
		default:
			return L"Error";
		}
	}

	inline Vector2f GetMoveTaget()const
	{
		return m_MoveTaget;
	}

	inline void SetBackGound(PlayerBackGround * ref)
	{
		m_BackGround = ref;
	}
	void SetBackSound(const wchar_t* _soundName);
	void SetBattleMode(bool isBattleMode);

	inline void SetMonsters(std::set<Monster*> * _MonsterData)
	{
		m_FieldMonsters = _MonsterData;
	}
public:
	virtual void Init() override;
	virtual void PrevUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void DebugRender()override;

public:
	// Order Func.
	void OrderRunMove(const Vector2f& _taget);
	void OrderAttack(BattlePawn* _taget);
	void OrderMagie(BattlePawn* _taget);
private:
	void Move(const Vector2f& _taget);
	virtual void Attack(BattlePawn * taget);
private:
	// Setting Func.
	void AnimationSetting();
	
	// State Func.
	void ChangeState(PlayerState _newState);
	void IdleFunc();
	void RunFunc();
	void DeadFunc();

	void BattleIdleFunc();
	void Attack1Func();
	void Skill1Func();
	void Skill2Func();

	// Move Func.
	void ChangeDir(PlayerDir _newDir);
	void DirUpdate();
	PlayerDir QuadrantProsses(int num);

	//
	void DamageHUD(Vector2f pos, Vector2f vel);
	
};

