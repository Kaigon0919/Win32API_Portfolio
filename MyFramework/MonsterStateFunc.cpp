#include"stdafx.h"
#include"Monster.h"
#include"Render.h"
#include"Player.h"
#include"Level.h"
#include"HPBar.h"
#include"arrow.h"

void Monster::IdleFunc()
{
	if (m_Player && !m_Player->IsDead())
	{
		if (m_Position.Distance(m_Player->GetPosition()) < m_AttRange)
		{
			m_MoveTaget = m_Player->GetPosition();
			DirUpdate();
			ChangeState(MonsterState::Mon_Attack);
		}
		if (m_Position.Distance(m_Player->GetPosition()) < m_FindRange)
		{
			ChangeState(Mon_Move);
		}
	}
}
void Monster::MoveFunc()
{
	if (m_Player && !m_Player->IsDead())
	{
		if (m_Position.Distance(m_Player->GetPosition()) < m_TrackRange)
		{
			m_MoveTaget = m_Player->GetPosition();
			DirUpdate();

			Vector2f moveVector = DistancePerFrame(m_Position, m_Player->GetPosition(), m_MoveSpeed * TimeManager::Instance().GetDeltaTime());
			float dis = (m_Player->GetPosition() - m_Position).Length();
			// 이동해야할 거리가 0.1f보다 적으면 최종위치까지 도달했다고 판단후 상태변환.
			if (dis <= m_AttRange)
			{
				ChangeState(MonsterState::Mon_Attack);
				time_Att.Reset();
				return;
			}
			m_Position += moveVector;

		}
		else
		{
			ChangeState(Mon_Idle);
		}
	}
}
void Monster::PartrolFunc()
{
	if (m_Player)
	{
		if (m_Position.Distance(m_Player->GetPosition()) < m_FindRange)
		{

		}
	}
}
void Monster::AttackFunc()
{
	if (m_Player->IsDead())
	{
		ChangeState(Monster::Mon_Idle);
	}
	if (m_Player)
	{
		if (m_AniRenderer->IsCurAni((m_DirString[m_Dir] + m_StateString[MonsterState::Mon_Attack]).c_str()) && m_AniRenderer->IsEnd())
		{
			ChangeState(Monster::Mon_Move);
		}
		if (time_Att.Check()) // 0.4초.
		{
			switch (m_AttType)
			{
			case Monster::MAT_Melee:
				MeleeAttack();
				break;
			case Monster::MAT_Range:
				RangeAttack();
				break;
			default:
				break;
			}
			time_Att.SetDead(true);
		}
	}
}
void Monster::HitFunc()
{
	ChangeState(Monster::Mon_Idle);
}
void Monster::DeadFunc()
{
	if (time_Deadtime.Check())
	{
		m_AniRenderer->SetUpdate(false);
		m_ShadowRender->SetUpdate(false);
		m_HpBar.SetActive(false);
	}
}


void Monster::MeleeAttack()
{
	Attack(m_Player);
}
void Monster::RangeAttack()
{
	Arrow * temp = GetLevel()->CreateActor<Arrow>(m_Position + Vector2f(0.0f,-GetColSize().y*0.5f));
	temp->Setting(m_Player,(Arrow::ArrowType)m_ArrowType ,250.0f, m_Attck, 10.0f);
}