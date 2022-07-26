#include"stdafx.h"
#include"Player.h"
#include"Render.h"
#include"PlayerBackGround.h"
#include"SoundPlayer.h"
#include"Level.h"
void Player::IdleFunc()
{
}

void Player::RunFunc()
{
	// 프레임당 이동해야할 거리.
	if (m_AttackTaget)
	{
		m_MoveTaget = m_AttackTaget->GetPosition();
	}
	Vector2f moveVector = DistancePerFrame(m_Position, m_MoveTaget, m_MoveSpeed * TimeManager::Instance().GetDeltaTime());
	float dis = (m_MoveTaget - m_Position).Length();
	// 이동해야할 거리가 0.1f보다 적으면 최종위치까지 도달했다고 판단후 상태변환.
	if (m_AttackTaget)
	{
		if (dis <= m_AttRange)
		{
			ChangeState(PlayerState::Attack1);
			time_att1e1.Reset();
			time_att1e2.Reset();
			return;
		}
	}
	else
	{
		if (dis <= 0.1f)
		{
			if (m_isBattle)
			{
				ChangeState(PlayerState::BattleIdle);
			}
			else
			{
				ChangeState(PlayerState::Idle);
			}
			return;
		}
	}
	// 이동.
	Vector2f tempPos = m_Position + moveVector;
	Vector2f backMove = Vector2f();
	// 8방향의 점들이 이동불가 타일에 있을때.
	if (m_BackGround)
	{
		Vector2f tempBack = Vector2f();

		for (int i = 0; i < sizeof(m_ColPoint) / sizeof(Vector2f); ++i)
		{
			tempBack = Vector2f::zero;
			while (m_BackGround->IsTileEqualState(tempPos + m_ColPoint[i] + tempBack, 1))
			{
				tempBack -= m_ColPoint[i].GetNormalize();
			}
			backMove += tempBack;
		}
	}
	m_Position += moveVector + backMove;
}

void Player::DeadFunc()
{
}

void Player::BattleIdleFunc()
{

}
void Player::Attack1Func()
{
	if (time_att1e1.Check())
	{
		Attack(m_AttackTaget);
		time_att1e1.SetDead(true);

	}
	if (time_att1e2.Check())
	{
		Attack(m_AttackTaget);
		time_att1e2.SetDead(true);
	}
	if (m_AniRenderer->IsCurAni((m_DirString[m_Dir] + m_StateString[Attack1]).c_str()) && m_AniRenderer->IsEnd())
	{
		ChangeState(PlayerState::BattleIdle);
		m_AttackTaget = nullptr;
	}
}


void Player::Skill1Func()
{
	if (m_SkillRender->IsEnd())
	{
		m_SkillRender->SetUpdate(false);
	}
	if (m_AniRenderer->IsCurAni((m_DirString[m_Dir] + m_StateString[Skill1]).c_str()) && m_AniRenderer->IsEnd())
	{
		ChangeState(PlayerState::BattleIdle);
	}

	if (time_skill1.Check() && SkillCount < 5)
	{
		if (m_FieldMonsters != nullptr)
		{
			std::set<Monster*>::iterator itStart = m_FieldMonsters->begin();
			std::set<Monster*>::iterator itEnd = m_FieldMonsters->end();
			for (; itStart != itEnd; ++itStart)
			{
				if (((BattlePawn*)(*itStart))->IsDead())
				{
					continue;
				}
				if (m_Position.Distance(((BattlePawn*)(*itStart))->GetPosition()) < m_Skill1Range)
				{
					Attack((BattlePawn*)(*itStart));
				}
			}
		}
		time_skill1.Reset();
		++SkillCount;
	}
}
void Player::Skill2Func()
{
	if (m_SkillRender->IsEnd())
	{
		m_SkillRender->SetUpdate(false);
	}
	if (m_AniRenderer->IsCurAni((m_DirString[m_Dir] + m_StateString[Skill2]).c_str()) && m_AniRenderer->IsEnd())
	{
		ChangeState(PlayerState::BattleIdle);
	}
}