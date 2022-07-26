#include "stdafx.h"
#include "Player.h"
#include"Level.h"
#include"Render.h"
#include"ActorCollision.h"
#include"ResourceManager.h"
#include"SoundPlayer.h"
#include"GameMath.h"
#include"DamageNumber.h"
#include"HitEffectActor.h"
#include"PlayerBackGround.h"
#include"arrow.h"

Player::Player() : BattlePawn(), m_MoveTaget(), m_MoveSpeed(0), m_State(PlayerState::Idle), StateFunc(nullptr), m_BackGround(nullptr), m_isBattle(false), backSoundName(L""), m_FieldMonsters(nullptr)
, m_Dir(PlayerDir::LeftDown), m_DirString{ L"LeftDown_",L"Down_" ,L"RightDown_" ,L"Left_" ,L"Right_" ,L"LeftTop_" ,L"Top_" ,L"RightTop_" }
, m_StateString{ L"Idle", L"BattleIdle", L"Walk", L"Run", L"Attack1", L"Attack2", L"Rush", L"Sit", L"Hit", L"Dead",L"Skill1",L"Skill2" }
, time_att1e1(0.4f), time_att1e2(0.6f), time_skill1(0.2f), SkillCount(0), m_Skill1Range(0.0f)
{
	SetName(L"Player");

	// TileMap Col Dot
	Vector2f colVec = Vector2f::up;
	float colPointLen = 15.0f;
	for (int i = 0; i < sizeof(m_ColPoint) / sizeof(Vector2f); ++i)
	{
		m_ColPoint[i] = colVec * colPointLen;
		colVec.Rotate(45);
	}
}


Player::~Player()
{
}

void Player::SetBackSound(const wchar_t * _soundName)
{
	if (backSoundName == _soundName)
	{
		return;
	}
	backSoundName = _soundName;
	m_BackGoundSound->ChangeSound(_soundName, true);
	m_BackGoundSound->SetLoop(true);
}

void Player::SetBattleMode(bool isBattleMode)
{
	m_isBattle = isBattleMode;

	if (m_isBattle)
	{
		ChangeState(PlayerState::BattleIdle);
	}
	else
	{
		ChangeState(PlayerState::Idle);
	}
}

void Player::Init()
{
	Vector2f winSize = SystemClass::Instance().GetWindowsSize();
	SetPosition(winSize*0.5f);
	m_AniRenderer = CreateRenderer<AniRenderer>();
	m_AniRenderer->SetSize(Vector2f(128.0f, 256.0f));
	m_AniRenderer->SetPivot(Vector2f(0.0f, 0.0f));

	m_ShadowRender = CreateRenderer<SingleRenderer>(-1);
	m_ShadowRender->SettingSprite(L"Shadow.bmp");
	m_ShadowRender->SetAlphaValue(50);
	m_ShadowRender->SetSize(Vector2f(32.0f, 32.0f));
	m_ShadowRender->SetPivot(Vector2f(0.0f, -4.0f));

	m_Collision = CreateCollision(L"Player");
	m_Collision->SetSize(Vector2f(48.0f, 86.0f));
	m_Collision->SetPivot(Vector2f(0.0f, -43.0f));

	m_SkillRender = CreateRenderer<AniRenderer>(1);
	m_SkillRender->SetSize(Vector2f(256.0f, 256.0f));
	m_SkillRender->SetPivot(Vector2f(0.0f, -32.0f));

	AnimationSetting();

	m_ScaleRatio = 1.0f;

	m_MoveTaget = Vector2f(0, 0);
	ChangeState(PlayerState::Idle);

	m_BackGoundSound = ResourceManager::Instance().CreateSoundPlayer();

	m_CameraToPlayer = GetLevel()->GetCameraPosition() - m_Position;

	// State Setting.
	m_AttRange = 70.0f;
	m_MoveSpeed = 200.0f;
	m_Attck = 30.0f;
	m_MaxHp = m_CurHp = 3000.0f;
	m_MaxMp = m_CurMp = 100.0f;
	m_MaxSp = m_CurSp = 100.0f;
	m_Skill1Range = 100.0f;

	m_StateHUD.Init(this, &m_CurHp, m_MaxHp,&m_CurMp,m_MaxMp,&m_CurSp, m_MaxSp, Vector2f(-winSize.x * 0.5f + 132.0f, -winSize.y * 0.5f + 75.0f), Vector2f(264.0f,150.f));
}

void Player::PrevUpdate()
{
}

void Player::Update()
{

#ifdef _DEBUG
	if (true == InputManager::Instance().IsDown(L"Left"))
	{
	}

	if (true == InputManager::Instance().IsDown(L"Right"))
	{
	}

	if (true == InputManager::Instance().IsDown(L"Up"))
	{
	}

	if (true == InputManager::Instance().IsDown(L"Down"))
	{
	}
	if (InputManager::Instance().IsDown(L"SpaceBar"))
	{
	}
#endif
	if (IsDead() && m_State != Dead)
	{
		ChangeState(Dead);
		m_Collision->SetUpdate(false);
		m_SkillRender->SetUpdate(false);
	}
	(*this.*StateFunc)();

	m_StateHUD.Update();

}

void Player::LateUpdate()
{
	Vector2i temp = m_Position + m_CameraToPlayer;
	GetLevel()->SetCameraPosition(temp);
}

void Player::DebugRender()
{
	if (m_BackGround)
	{
		for (int i = 0; i < sizeof(m_ColPoint) / sizeof(Vector2f); ++i)
		{
			POINT p;
			MoveToEx(ResourceManager::Instance().GetBackBuffer(), (int)m_AniRenderer->GetScreenPos().x, (int)m_AniRenderer->GetScreenPos().y, &p);
			LineTo(ResourceManager::Instance().GetBackBuffer(), (int)(m_AniRenderer->GetScreenPos() + m_ColPoint[i]).x, (int)(m_AniRenderer->GetScreenPos() + m_ColPoint[i]).y);
		}
	}
}

void Player::ChangeState(PlayerState _newState)
{
	std::wstring temp = m_DirString[(int)m_Dir] + m_StateString[(int)_newState];
	switch (_newState)
	{
	case Player::Idle:
		m_State = Player::Idle;
		StateFunc = &Player::IdleFunc;
		break;
	case Player::Run:
		m_State = Run;
		StateFunc = &Player::RunFunc;
		break;
	case Player::BattleIdle:
		m_State = BattleIdle;
		StateFunc = &Player::BattleIdleFunc;
		break;
	case Player::Attack1:
		m_State = Attack1;
		StateFunc = &Player::Attack1Func;
		break;
	case Player::Dead:
		m_State = Dead;
		StateFunc = &Player::DeadFunc;
		break;
	case Player::Skill1:
		m_State = Skill1;
		StateFunc = &Player::Skill1Func;
		break;
	default:
		return;
	}
	m_AniRenderer->ChangeAnimation(temp.c_str());
}


void Player::OrderRunMove(const Vector2f& _taget)
{
	if (IsDead())
	{
		return;
	}
	if (m_State == Attack1 || m_State == Skill1 || m_State == Skill2)
	{
		return;
	}
	m_AttackTaget = nullptr;
	Move(_taget);
}

void Player::Attack(BattlePawn * _taget)
{
	if (_taget == nullptr)
	{
		return;
	}
	BattlePawn::Attack(_taget);

	GetLevel()->CreateActor<HitEffectActor>(_taget->GetPosition() + Vector2f(0.0f, -34.0f));

	Vector2f taget = _taget->GetPosition() - m_Position;
	taget.normalize();
	float h = Vector2f::up.Cross(taget);

	DamageHUD(_taget->GetPosition() + Vector2f(-50.0f, -_taget->GetColSize().y), Vector2f(h, -3.0f));
	ResourceManager::Instance().PlaySound(L"Hit.wav");

}

void Player::OrderAttack(BattlePawn* _taget)
{
	if (IsDead())
	{
		return;
	}
	if(m_State == Attack1 || m_State == Skill1 || m_State == Skill2)
	{
		return;
	}
	if (_taget == nullptr || _taget->IsDead())
	{
		return;
	}
	m_AttackTaget = _taget;
	Move(m_AttackTaget->GetPosition());
}

void Player::OrderMagie(BattlePawn * _taget)
{
	if (IsDead() || m_CurSp - 10.0f <= 0)
	{
		return;
	}
	if (m_State == Attack1 || m_State == Skill1 || m_State == Skill2 || m_isBattle == false)
	{
		return;
	}

	if (_taget == nullptr)
	{
		m_CurSp -= 10.0f;
		ChangeState(PlayerState::Skill1);
		m_SkillRender->ChangeAnimation(L"Skill1");
		m_SkillRender->SetUpdate(true);
	}
	else
	{
		m_CurSp -= 10.0f;
		ChangeState(PlayerState::Skill1);
		m_SkillRender->ChangeAnimation(L"Skill1");
		m_SkillRender->SetUpdate(true);
	}
	SkillCount = 0;
}

void Player::Move(const Vector2f& _taget)
{
	m_MoveTaget = _taget;
	if (m_State != PlayerState::Run)
	{
		ChangeState(PlayerState::Run);
	}
	DirUpdate();
}


void Player::ChangeDir(PlayerDir _newDir)
{
	if (m_Dir == _newDir)
	{
		return;
	}

	m_Dir = _newDir;
	std::wstring temp = m_DirString[(int)m_Dir] + m_StateString[(int)m_State];
	m_AniRenderer->ChangeAnimation(temp.c_str(), m_AniRenderer->GetCurIndex());
	return;
}
void Player::DirUpdate()
{
	Vector2f taget = m_MoveTaget - m_Position;
	taget.normalize();
	float v = Vector2f::up.Dot(taget);
	float h = Vector2f::up.Cross(taget);
	PlayerDir newDir;

	if (v >= 0) // 위방향.
	{
		if (h >= 0) // 오른쪽 방향이다. 1사분면.
		{
			newDir = QuadrantProsses(1);
		}
		else // 왼쪽 방향. 2사분면.
		{
			newDir = QuadrantProsses(2);
		}
	}
	else
	{
		if (h >= 0) // 오른쪽 방향이다. 4사분면.
		{
			newDir = QuadrantProsses(4);
		}
		else // 왼쪽 방향. 3사분면.
		{
			newDir = QuadrantProsses(3);
		}
	}
	ChangeDir(newDir);

}
Player::PlayerDir Player::QuadrantProsses(int num)
{
	if (num < 1 || num> 4)
		return PlayerDir::LeftDown;

	Vector2f taget = m_MoveTaget - m_Position;
	taget.normalize();

	float centerXDegree = 45.0f + (num - 1) * 90;
	float centerYDegree = (45.0f + (num - 1) * 90) * -1;

	Vector2f center = Vector2f(cos(centerXDegree * GameMath::DTOR), sin(centerYDegree* GameMath::DTOR));
	float cosS = cos(22.5f * GameMath::DTOR);
	switch (num)
	{
	case 1:
		if (abs(center.Dot(taget)) >= cosS)
		{
			return PlayerDir::RightTop;
		}
		else if (abs(Vector2f::up.Dot(taget)) >= cosS)
		{
			return PlayerDir::Top;
		}
		else if (abs(Vector2f::right.Dot(taget)) >= cosS)
		{
			return PlayerDir::Right;
		}
		break;
	case 2:
		if (abs(center.Dot(taget)) >= cosS)
		{
			return PlayerDir::LeftTop;
		}
		else if (abs(Vector2f::up.Dot(taget)) >= cosS)
		{
			return PlayerDir::Top;
		}
		else if (abs(Vector2f::left.Dot(taget)) >= cosS)
		{
			return PlayerDir::Left;
		}
		break;
	case 3:
		if (abs(center.Dot(taget)) >= cosS)
		{
			return PlayerDir::LeftDown;
		}
		else if (abs(Vector2f::down.Dot(taget)) >= cosS)
		{
			return PlayerDir::Down;
		}
		else if (abs(Vector2f::left.Dot(taget)) >= cosS)
		{
			return PlayerDir::Left;
		}
		break;
	case 4:
		if (abs(center.Dot(taget)) >= cosS)
		{
			return PlayerDir::RightDown;
		}
		else if (abs(Vector2f::down.Dot(taget)) >= cosS)
		{
			return PlayerDir::Down;
		}
		else if (abs(Vector2f::right.Dot(taget)) >= cosS)
		{
			return PlayerDir::Right;
		}
		break;
	default:
		break;
	}
	return PlayerDir::LeftDown;
}

void Player::DamageHUD(Vector2f pos, Vector2f vel)
{
	DamageNumber *temp = GetLevel()->CreateActor<DamageNumber>(pos);
	temp->InitSetting(4, L"DamageUI", Vector2f(32, 32), (int)m_Attck);
	temp->SetVelocity(vel);
}

void Player::AnimationSetting()
{
	for (int i = 0; i < PlayerDir::PlayerDirMax; ++i)
	{
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[0]).c_str(), L"Character", 55 * i + 0, 55 * i + 0);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[1]).c_str(), L"Character", 55 * i + 1, 55 * i + 8);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[2]).c_str(), L"Character", 55 * i + 9, 55 * i + 18);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[3]).c_str(), L"Character", 55 * i + 19, 55 * i + 28);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[4]).c_str(), L"Character", 55 * i + 29, 55 * i + 38, false);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[5]).c_str(), L"Character", 55 * i + 39, 55 * i + 48, false);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[6]).c_str(), L"Character", 55 * i + 49, 55 * i + 52, false);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[7]).c_str(), L"Character", 55 * i + 53, 55 * i + 53);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[8]).c_str(), L"Character", 55 * i + 54, 55 * i + 54);
	}

	m_AniRenderer->CreateAnimation((m_DirString[0] + m_StateString[9]).c_str(), L"Character", 440, 440);
	m_AniRenderer->CreateAnimation((m_DirString[1] + m_StateString[9]).c_str(), L"Character", 440, 440);
	m_AniRenderer->CreateAnimation((m_DirString[2] + m_StateString[9]).c_str(), L"Character", 441, 441);
	m_AniRenderer->CreateAnimation((m_DirString[3] + m_StateString[9]).c_str(), L"Character", 440, 440);
	m_AniRenderer->CreateAnimation((m_DirString[4] + m_StateString[9]).c_str(), L"Character", 441, 441);
	m_AniRenderer->CreateAnimation((m_DirString[5] + m_StateString[9]).c_str(), L"Character", 442, 442);
	m_AniRenderer->CreateAnimation((m_DirString[6] + m_StateString[9]).c_str(), L"Character",442,442);
	m_AniRenderer->CreateAnimation((m_DirString[7] + m_StateString[9]).c_str(), L"Character",443,443);



	for (int i = 0; i < PlayerDir::PlayerDirMax; ++i)
	{
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[11]).c_str(), L"CharacterMotion", 1 + (i * 12), 11 + (i * 12), false);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[12]).c_str(), L"CharacterMotion", 0 + ((i+8) * 12), 11 + ((i+8) * 12), false);
	}

	m_SkillRender->CreateAnimation(L"Skill1", L"Skill1", 0, 8, false);
	m_SkillRender->ChangeAnimation(L"Skill1");
	m_SkillRender->SetUpdate(false);

}
