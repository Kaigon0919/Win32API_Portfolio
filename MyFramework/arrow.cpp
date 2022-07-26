#include "stdafx.h"
#include "arrow.h"
#include"Render.h"
#include"Level.h"
#include"GameMath.h"
#include"BattlePawn.h"
#include"ActorCollision.h"
#include"DamageNumber.h"

Arrow::Arrow() : m_Taget(nullptr), m_Speed(0.0f), m_Att(0.0f), m_Render(nullptr), m_Col(nullptr), m_Dir(LeftDown)
, m_DirString{ L"LeftDown",L"Down" ,L"RightDown" ,L"Left" ,L"Right" ,L"LeftTop" ,L"Top" ,L"RightTop" },m_Type(FireArrow)
{
}


Arrow::~Arrow()
{
}

void Arrow::Init()
{
	m_Render = CreateRenderer<AniRenderer>(1);
	m_Col = CreateCollision(L"Arrow");
	m_Col->SetSize(Vector2f(50.0f, 50.0f));
}

void Arrow::Update()
{
	if (m_Taget == nullptr || m_Taget->IsDead())
	{
		this->Death();
		return;
	}
	m_TagetCenter = m_Taget->GetPosition();
	m_TagetCenter.y -= m_Taget->GetColSize().y / 2.0f;

	DirUpdate();
	float dis = m_Position.Distance(m_TagetCenter);
	if (m_AttRange > dis)
	{
		m_Taget->ProcessDamage(m_Att);

		Vector2f taget = m_TagetCenter - m_Position;
		taget.normalize();
		float h = Vector2f::up.Cross(taget);

		DamageNumber *temp = GetLevel()->CreateActor<DamageNumber>(m_TagetCenter + Vector2f(-50.0f, -m_Taget->GetColSize().y / 2.0f));
		temp->InitSetting(4, L"DamageUI", Vector2f(32, 32), (int)m_Att);
		temp->SetVelocity(Vector2f(h, -3.0f));
		ResourceManager::Instance().PlaySound(L"Hit.wav");

		this->Death();
		return;
	}
	else
	{
		Vector2f moveVector = DistancePerFrame(m_Position, m_TagetCenter, m_Speed * TimeManager::Instance().GetDeltaTime());
		m_Position += moveVector;
	}
}

void Arrow::LateUpdate()
{
	if (m_Taget == nullptr || m_Taget->IsDead())
	{
		this->Death();
		return;
	}
}

Vector2f Arrow::DistancePerFrame(const Vector2f & _myPosition, const Vector2f & _taget, const float _moveDistance)
{
	float FrameDis = _moveDistance;

	// Ÿ�ٱ����� ���� + ũ��.
	Vector2f dir = _taget - _myPosition;
	// �� �������� �Ÿ��� ���Ѵ�.
	float dirLen = dir.Length();
	// Ÿ�ٰ��� �Ÿ��� 0.0f�̸� ���� ���ε������ �Ͼ�Ƿ� Vector2f::zero�� ��ȯ. �� �̵��� �Ÿ��� 0 �̴�.
	if (dirLen == 0.0f)
	{
		return Vector2f::zero;
	}
	// �����Ӵ� �Ÿ��� ������ġ������ �Ÿ����� ũ�ٸ� �����Ӵ� �Ÿ��� ������ġ������ �Ÿ��� �ٲ��ش�.
	if (FrameDis > dirLen)
	{
		FrameDis = dirLen;
	}

	// dir�� �������ͷ� �ٲ��ش�.
	dir.normalize();
	// (���� * �̵��ؾ��� �Ÿ�) �� ��ȯ�ϴ�.
	return dir*FrameDis;
}

void Arrow::DirUpdate()
{
	Vector2f taget = m_TagetCenter - m_Position;
	taget.normalize();
	float v = Vector2f::up.Dot(taget);
	float h = Vector2f::up.Cross(taget);
	ArrowDir newDir;

	if (v >= 0) // ������.
	{
		if (h >= 0) // ������ �����̴�. 1��и�.
		{
			newDir = QuadrantProsses(1, taget);
		}
		else // ���� ����. 2��и�.
		{
			newDir = QuadrantProsses(2, taget);
		}
	}
	else
	{
		if (h >= 0) // ������ �����̴�. 4��и�.
		{
			newDir = QuadrantProsses(4, taget);
		}
		else // ���� ����. 3��и�.
		{
			newDir = QuadrantProsses(3, taget);
		}
	}
	ChangeDir(newDir);
}

void Arrow::ChangeDir(ArrowDir _newDir)
{
	if (m_Dir == _newDir)
	{
		return;
	}

	m_Dir = _newDir;
	std::wstring temp = m_DirString[(int)m_Dir];
	m_Render->ChangeAnimation(temp.c_str(), 0);
	return;
}

Arrow::ArrowDir Arrow::QuadrantProsses(int num, Vector2f dir)
{
	if (num < 1 || num> 4)
		return ArrowDir::LeftDown;

	float centerXDegree = 45.0f + (num - 1) * 90;
	float centerYDegree = (45.0f + (num - 1) * 90) * -1;

	Vector2f center = Vector2f(cos(centerXDegree * GameMath::DTOR), sin(centerYDegree* GameMath::DTOR));
	float cosS = cos(22.5f * GameMath::DTOR);
	switch (num)
	{
	case 1:
		//center = Vector2f(cos(45 * GameMath::DTOR), sin(-45 * GameMath::DTOR));
		if (abs(center.Dot(dir)) >= cosS)
		{
			return ArrowDir::RightTop;
		}
		else if (abs(Vector2f::up.Dot(dir)) >= cosS)
		{
			return ArrowDir::Top;
		}
		else if (abs(Vector2f::right.Dot(dir)) >= cosS)
		{
			return ArrowDir::Right;
		}
		break;
	case 2:
		if (abs(center.Dot(dir)) >= cosS)
		{
			return ArrowDir::LeftTop;
		}
		else if (abs(Vector2f::up.Dot(dir)) >= cosS)
		{
			return ArrowDir::Top;
		}
		else if (abs(Vector2f::left.Dot(dir)) >= cosS)
		{
			return ArrowDir::Left;
		}
		break;
	case 3:
		if (abs(center.Dot(dir)) >= cosS)
		{
			return ArrowDir::LeftDown;
		}
		else if (abs(Vector2f::down.Dot(dir)) >= cosS)
		{
			return ArrowDir::Down;
		}
		else if (abs(Vector2f::left.Dot(dir)) >= cosS)
		{
			return ArrowDir::Left;
		}
		break;
	case 4:
		if (abs(center.Dot(dir)) >= cosS)
		{
			return ArrowDir::RightDown;
		}
		else if (abs(Vector2f::down.Dot(dir)) >= cosS)
		{
			return ArrowDir::Down;
		}
		else if (abs(Vector2f::right.Dot(dir)) >= cosS)
		{
			return ArrowDir::Right;
		}
		break;
	default:
		break;
	}
	return ArrowDir::LeftDown;
}

void Arrow::Setting(BattlePawn * taget, ArrowType type ,float speed, float att, float attRange)
{
	m_Taget = taget;
	m_Speed = speed;
	m_Att = att;
	m_AttRange = attRange;
	m_Type = type;
	AnimationSetting();
}

void Arrow::AnimationSetting()
{
	switch (m_Type)
	{
	case Arrow::FireArrow:
		for (int i = 0; i < ArrowDir::DirMax; ++i)
		{
			m_Render->CreateAnimation(m_DirString[i].c_str(), L"FireArrow", 0 + 5 * i, 4 + 5 * i);
		}
		m_Render->SetSize(Vector2f(128.0f, 128.0f));
		break;
	case Arrow::DragonArrow:
		for (int i = 0; i < ArrowDir::DirMax; ++i)
		{
			m_Render->CreateAnimation(m_DirString[i].c_str(),L"DragonArrow1",i,i,false);
		}
		m_Render->SetSize(Vector2f(512.0f, 512.0f));
		break;
	default:
		break;
	}
	m_Render->ChangeAnimation(m_DirString[0].c_str());
}
