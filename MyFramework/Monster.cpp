#include "stdafx.h"
#include "Monster.h"
#include"Render.h"
#include"ActorCollision.h"
#include"Level.h"
#include"MultiSprite.h"
#include"DamageNumber.h"
#include"HitEffectActor.h"
#include"SoundPlayer.h"
#include"Player.h"

Monster::Monster() : BattlePawn(), m_State(MonsterState::Mon_Idle), m_Dir(MonsterDir::LeftDown), m_Player(nullptr), m_MoveSpeed(0.0f), m_MoveTaget(Vector2f::zero)
, m_DirString{ L"LeftDown_",L"RightDown_" ,L"LeftTop_" ,L"RightTop_" }
, m_StateString{ L"Idle",L"Move",L"Partrol", L"Attack", L"Hit", L"Dead" }
, m_TrackRange(0.0f), m_FindRange(0.0f), time_Partrol(0.0f), time_Att(0.0f), time_Deadtime(2.0f), m_AttType(MonsterAttackType::MAT_Melee), m_ArrowType(0)
{
	SetName(L"Monster");
}


Monster::~Monster()
{
}
const wchar_t * Monster::MonsterTypeName(MonsterType _type)
{
	switch (_type)
	{
	case Monster::Monster4:
		return L"Monster4";
	case Monster::Monster5:
		return L"Monster5";
	case Monster::Monster25:
		return L"Monster25";
	case Monster::Monster213:
		return L"Monster213";
	case Monster::Monster243:
		return L"Monster243";
	case Monster::Monster245:
		return L"Monster245";
	case Monster::Monster248:
		return L"Monster248";
	case Monster::Monster441:
		return L"Monster441";
	case Monster::Monster504:
		return L"Monster504";
	case Monster::Monster512:
		return L"Monster512";
	default:
		return L"ERROR";
	}
	return L"ERROR";
}
void Monster::InitStateSetting(MonsterType type)
{
	MonsterTypeSetting(type);
	m_HpBar.Init(this, &m_CurHp, m_MaxHp, Vector2f(0.0f, 10.0f), Vector2f(50.0f, 5.0f));
}
void Monster::InitStateSetting(MonsterType type,float maxHP, float moveSpeed, float att, float attRange , float findRange, float trackRange)
{
	MonsterTypeSetting(type);
	m_MaxHp = m_CurHp = maxHP;
	m_MoveSpeed = moveSpeed;
	m_Attck = att;
	m_AttRange = attRange;
	m_FindRange = findRange;
	m_TrackRange = trackRange;

	m_HpBar.Init(this, &m_CurHp, m_MaxHp, Vector2f(0.0f, 10.0f), Vector2f(50.0f, 5.0f));
}
void Monster::ImageSetting(Vector2f size, Vector2f pivot)
{
	m_AniRenderer->SetSize(size);
	m_AniRenderer->SetPivot(pivot);
}
void Monster::ColSetting(Vector2f size, Vector2f pivot)
{
	m_Collision->SetSize(size);
	m_Collision->SetPivot(pivot);
}
void Monster::Init()
{
	m_AniRenderer = CreateRenderer<AniRenderer>();
	m_Collision = CreateCollision(L"Monster");

	m_ShadowRender = CreateRenderer<SingleRenderer>(-1);
	m_ShadowRender->SettingSprite(L"Shadow.bmp");
	m_ShadowRender->SetAlphaValue(70);
	m_ShadowRender->SetPivot(Vector2f(0.0f, 0.0f));
	m_State = Mon_Dead;

}
void Monster::PrevUpdate()
{
}
void Monster::Update()
{
	if (IsDead() && m_State != Mon_Dead)
	{
		ChangeState(Mon_Dead);
		m_Collision->SetUpdate(false);
	}
	if (StateFunc != nullptr)
	{
		(*this.*StateFunc)();
	}

	m_HpBar.Update();
}
void Monster::LateUpdate()
{
}
void Monster::ProcessDamage(float _damage)
{
	BattlePawn::ProcessDamage(_damage);
}
void Monster::MonsterTypeSetting(MonsterType type)
{
	m_MonsterType = type;
	switch (type)
	{
	case Monster::Monster4:
		ImageSetting();
		ColSetting(Vector2f(134.0, 150.0f), Vector2f(0.0f, -75.0f));
		m_ShadowRender->SetSize(Vector2f(100.0f, 64.0f));
		m_ShadowRender->SetPivot(Vector2f(0.0f, -16.0f));
		AnimationSetting(L"Monster4", Vector2i(0, 10), Vector2i(16, 25), Vector2i(16, 25), Vector2i(11, 15), Vector2i(4, 5), Vector2i(4, 5));
		m_MaxHp = m_CurHp = 300.0f;
		m_MoveSpeed = 100.0f;
		m_Attck = 30.0f;
		m_AttRange = 50.0f;
		m_FindRange = 200.0f;
		m_TrackRange = 300.0f;

		SetAttTimeHelper(0.3f);
		break;
	case Monster::Monster5:
		ImageSetting(Vector2f(70.0f, 105.0f), Vector2f(0.0f, -35.0f));
		ColSetting(Vector2f(70.0f, 105.0f), Vector2f(0.0f, -35.0f));
		m_ShadowRender->SetSize(Vector2f(52.0f, 42.0f));
		m_ShadowRender->SetPivot(Vector2f(0.0f, 0.0));
		AnimationSetting(L"Monster5", Vector2i(0, 4), Vector2i(5, 14), Vector2i(5, 14), Vector2i(15, 20), Vector2i(21, 25), Vector2i(21, 25));
		m_MaxHp = m_CurHp = 150.0f;
		m_MoveSpeed = 100.0f;
		m_Attck = 15.0f;
		m_AttRange = 50.0f;
		m_FindRange = 200.0f;
		m_TrackRange = 300.0f;
		SetAttTimeHelper(0.4f);
		break;
	case Monster::Monster25:
		ImageSetting();
		ColSetting(Vector2f(70.0f, 105.0f), Vector2f(0.0f, -52.5));
		m_ShadowRender->SetSize(Vector2f(52.0f, 42.0f));
		m_ShadowRender->SetPivot(Vector2f(0.0f,-10.0f));
		AnimationSetting(L"Monster25", Vector2i(0, 4), Vector2i(5, 14), Vector2i(5, 14), Vector2i(15, 20), Vector2i(21, 25), Vector2i(21, 25));
		m_MaxHp = m_CurHp = 120.0f;
		m_MoveSpeed = 110.0f;
		m_Attck = 12.0f;
		m_AttRange = 50.0f;
		m_FindRange = 250.0f;
		m_TrackRange = 350.0f;
		
		SetAttTimeHelper(0.4f);
		break;
	case Monster::Monster213:
		ImageSetting();
		ColSetting(Vector2f(70.0f, 64.0f), Vector2f(0.0f, -34.0));
		m_ShadowRender->SetSize(Vector2f(32.0f, 32.0f));
		m_ShadowRender->SetPivot(Vector2f(0.0f, 0.0f));
		AnimationSetting(L"Monster213", Vector2i(0, 5), Vector2i(6, 11), Vector2i(6, 11), Vector2i(12, 19), Vector2i(20, 20), Vector2i(20,20));
		m_AttType = MAT_Range;
		m_MaxHp = m_CurHp = 70.0f;
		m_MoveSpeed = 110.0f;
		m_Attck = 20.0f;
		m_AttRange = 200.0f;
		m_FindRange = 200.0f;
		m_TrackRange = 500.0f;
		m_ArrowType = 0;
		SetAttTimeHelper(0.4f);
		break;
	case Monster::Monster243:
		ImageSetting();
		ColSetting(Vector2f(70.0f, 125.0f), Vector2f(0.0f, -55.0));
		m_ShadowRender->SetSize(Vector2f(64.0f, 64.0f));
		m_ShadowRender->SetPivot(Vector2f(0.0f, -8.0f));
		AnimationSetting(L"Monster243", Vector2i(0, 6), Vector2i(7, 16), Vector2i(7, 16), Vector2i(17, 22), Vector2i(23, 23), Vector2i(23, 23));
		m_AttType = MAT_Range;
		m_MaxHp = m_CurHp = 80.0f;
		m_MoveSpeed = 90.0f;
		m_Attck = 30.0f;
		m_AttRange = 200.0f;
		m_FindRange = 200.0f;
		m_TrackRange = 500.0f;
		m_ArrowType = 1;
		SetAttTimeHelper(0.4f);
		break;
	case Monster::Monster245:
		ImageSetting();
		ColSetting(Vector2f(70.0f, 78.0f), Vector2f(0.0f, -38.0));
		m_ShadowRender->SetSize(Vector2f(32.0f, 32.0f));
		m_ShadowRender->SetPivot(Vector2f(0.0f, -4.0f));
		AnimationSetting(L"Monster245", Vector2i(0, 3), Vector2i(4, 11), Vector2i(4, 11), Vector2i(12, 18), Vector2i(19, 19), Vector2i(19, 19));
		m_MaxHp = m_CurHp = 100.0f;
		m_MoveSpeed = 100.0f;
		m_Attck = 15.0f;
		m_AttRange = 50.0f;
		m_FindRange = 200.0f;
		m_TrackRange = 300.0f;
		SetAttTimeHelper(0.3f);
		break;
	case Monster::Monster248:
		ImageSetting();
		ColSetting(Vector2f(112.0f, 122.0f), Vector2f(0.0f, -61.0f));
		m_ShadowRender->SetSize(Vector2f(64.0f, 64.0f));
		m_ShadowRender->SetPivot(Vector2f(0.0, -8.0f));
		AnimationSetting(L"Monster248", Vector2i(0, 7), Vector2i(8, 13), Vector2i(8, 13), Vector2i(14, 18), Vector2i(0, 0), Vector2i(0, 0));
		m_MaxHp = m_CurHp = 170.0f;
		m_MoveSpeed = 70.0f;
		m_Attck = 13.0f;
		m_AttRange = 50.0f;
		m_FindRange = 200.0f;
		m_TrackRange = 300.0f;
		SetAttTimeHelper(0.2f);
		break;
	case Monster::Monster441:
		ImageSetting();
		ColSetting(Vector2f(34.0f, 34.0f), Vector2f(0.0f, -17.0f));
		m_ShadowRender->SetSize(Vector2f(32.0f, 32.0f));
		m_ShadowRender->SetPivot(Vector2f(0.0f, 0.0f));
		AnimationSetting(L"Monster441", Vector2i(0, 9), Vector2i(10, 15), Vector2i(10, 15), Vector2i(16, 21), Vector2i(22, 22), Vector2i(22, 22));
		m_MaxHp = m_CurHp = 50.0f;
		m_MoveSpeed = 170.0f;
		m_Attck = 5.0f;
		m_AttRange = 50.0f;
		m_FindRange = 200.0f;
		m_TrackRange = 300.0f;
		SetAttTimeHelper(0.5f);
		break;

	case Monster::Monster504:
		ImageSetting();
		ColSetting(Vector2f(42.0f, 42.0f), Vector2f(0.0f, -21.0f));
		m_ShadowRender->SetSize(Vector2f(42.0f, 32.0f));
		m_ShadowRender->SetPivot(Vector2f(0.0f, -4.0f));
		AnimationSetting(L"Monster504", Vector2i(0, 9), Vector2i(10, 17), Vector2i(10, 17), Vector2i(18, 26), Vector2i(27, 27), Vector2i(27, 27));
		m_MaxHp = m_CurHp = 100.0f;
		m_MoveSpeed = 100.0f;
		m_Attck = 10.0f;
		m_AttRange = 50.0f;
		m_FindRange = 200.0f;
		m_TrackRange = 300.0f;
		SetAttTimeHelper(0.5f);
		break;
	case Monster::Monster512:
		ImageSetting();
		ColSetting(Vector2f(84.0f, 100.0f), Vector2f(0.0f, -48.0));
		m_ShadowRender->SetSize(Vector2f(84.0, 64.0f));
		m_ShadowRender->SetPivot(Vector2f(0.0f, -12.0f));
		AnimationSetting(L"Monster512", Vector2i(0, 9), Vector2i(10, 16), Vector2i(10, 16), Vector2i(17, 23), Vector2i(24, 24), Vector2i(24, 24));
		m_MaxHp = m_CurHp = 200.0f;
		m_MoveSpeed = 100.0f;
		m_Attck = 20.0f;
		m_AttRange = 50.0f;
		m_FindRange = 200.0f;
		m_TrackRange = 300.0f;
		SetAttTimeHelper(0.4f);
		break;
	case Monster::Max:
		break;
	default:
		break;
	}
}
void Monster::DirUpdate()
{
	Vector2f taget = m_MoveTaget - m_Position;
	if (taget == Vector2f::zero)
	{
		return;
	}
	taget.normalize();
	float v = Vector2f::up.Dot(taget);
	float h = Vector2f::up.Cross(taget);
	MonsterDir newDir;

	if (v >= 0) // 위방향.
	{
		if (h >= 0) // 오른쪽 방향이다. 1사분면.
		{
			newDir = MonsterDir::RightTop;
		}
		else // 왼쪽 방향. 2사분면.
		{
			newDir = MonsterDir::LeftTop;
		}
	}
	else
	{
		if (h >= 0) // 오른쪽 방향이다. 4사분면.
		{
			newDir = MonsterDir::RightDown;
		}
		else // 왼쪽 방향. 3사분면.
		{
			newDir = MonsterDir::LeftDown;
		}
	}
	ChangeDir(newDir);
}

void Monster::ChangeDir(MonsterDir _newDir)
{
	if (m_Dir == _newDir)
	{
		return;
	}
	m_Dir = _newDir;
	std::wstring temp = m_DirString[(int)m_Dir] + m_StateString[(int)m_State];
	if (m_AniRenderer)
	{
		m_AniRenderer->ChangeAnimation(temp.c_str(), m_AniRenderer->GetCurIndex());
	}
	return;
}
void Monster::Attack(BattlePawn * _taget)
{
	BattlePawn::Attack(_taget);

	GetLevel()->CreateActor<HitEffectActor>(m_Player->GetPosition() - Vector2f(0.0f, 37.0f));
	ResourceManager::Instance().PlaySound(L"Hit.wav");
	Vector2f taget = _taget->GetPosition() - m_Position;
	taget.normalize();
	float h = Vector2f::up.Cross(taget);

	DamageHUD(_taget->GetPosition() + Vector2f(-50.0f, -_taget->GetColSize().y), Vector2f(h, -3.0f));

}
void Monster::ChangeState(MonsterState _newState)
{
	std::wstring temp = m_DirString[(int)m_Dir] + m_StateString[(int)_newState];
	switch (_newState)
	{
	case Monster::Mon_Idle:
		m_State = MonsterState::Mon_Idle;
		StateFunc = &Monster::IdleFunc;
		break;
	case Monster::Mon_Move:
		m_State = MonsterState::Mon_Move;
		StateFunc = &Monster::MoveFunc;
		break;
	case Monster::Mon_Partrol:
		m_State = MonsterState::Mon_Partrol;
		StateFunc = &Monster::PartrolFunc;
		break;
	case MonsterState::Mon_Attack:
		m_State = MonsterState::Mon_Attack;
		StateFunc = &Monster::AttackFunc;
		break;
	case Monster::Mon_Hit:
		m_State = MonsterState::Mon_Hit;
		StateFunc = &Monster::HitFunc;
		break;
	case Monster::Mon_Dead:
		m_State = MonsterState::Mon_Dead;
		StateFunc = &Monster::DeadFunc;
		break;
	default:
		return;
	}
	m_AniRenderer->ChangeAnimation(temp.c_str());
}

void Monster::AnimationSetting(const wchar_t * imgName, Vector2i AniIdleIdx, Vector2i AniMoveIdx, Vector2i AniPartorlIdx, Vector2i AniAttackIdx, Vector2i AniHitIdx, Vector2i AniDeadIdx)
{
	MultiSprite* temp = ResourceManager::Instance().FindMultiSprite(imgName);
	int lineNumber = (int)temp->SpriteCount() / 4;
	for (int i = 0; i < MonsterDir::DirMax; ++i)
	{
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[0]).c_str(), imgName, AniIdleIdx.x + i * lineNumber, AniIdleIdx.y + i * lineNumber);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[1]).c_str(), imgName, AniMoveIdx.x + i * lineNumber, AniMoveIdx.y + i *lineNumber);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[2]).c_str(), imgName, AniPartorlIdx.x + i * lineNumber, AniPartorlIdx.y + i *lineNumber);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[3]).c_str(), imgName, AniAttackIdx.x + i * lineNumber, AniAttackIdx.y + i * lineNumber, false);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[4]).c_str(), imgName, AniHitIdx.x + i * lineNumber, AniHitIdx.y + i * lineNumber, false);
		m_AniRenderer->CreateAnimation((m_DirString[i] + m_StateString[5]).c_str(), imgName, AniDeadIdx.x + i * lineNumber, AniDeadIdx.y + i * lineNumber, false);
	}
	ChangeState(Mon_Idle);
}


void Monster::DamageHUD(Vector2f pos, Vector2f vel)
{
	DamageNumber *temp = GetLevel()->CreateActor<DamageNumber>(pos);
	temp->InitSetting(4, L"DamageUIMonster", Vector2f(32, 32), (int)m_Attck);
	temp->SetVelocity(vel);
}
