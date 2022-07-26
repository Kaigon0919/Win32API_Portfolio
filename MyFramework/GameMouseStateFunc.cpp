#include"stdafx.h"
#include"GameMouse.h"
#include"Player.h"
#include"Level.h"
#include"ActorCollision.h"
#include"WarpObject.h"
void GameMouse::SetPlayer(Player* _player)
{
	m_Player = _player;
}

void GameMouse::DefaultFunc()
{
	if (InputManager::Instance().IsDown(L"LMouse"))
	{
		ChageState(MouseState::DefaultClick);
		if (m_Player)
		{
			m_Player->OrderRunMove(GetLevel()->GetMouseConvertPosition());
		}
	}
	if (ColList.empty() == false)
	{
		if (ColList.front()->GetActor()->NameEqual(L"Monster"))
		{
			ChageState(GameMouse::Attack);
		}
		if (ColList.front()->GetActor()->NameEqual(L"Warp"))
		{
			ChageState(GameMouse::Warp);

			m_TagetActor = ColList.front()->GetActor();
		}
	}
	if (m_Player && InputManager::Instance().IsDown(L"RMouse"))
	{
		m_Player->OrderMagie(nullptr);
		return;
	}
}
void GameMouse::DefaultClickFunc()
{
	if (InputManager::Instance().IsUp(L"LMouse"))
	{
		ChageState(MouseState::Default);
	}
	if (m_Player && InputManager::Instance().IsPressed(L"LMouse"))
	{
		m_Player->OrderRunMove(GetLevel()->GetMouseConvertPosition());
	}
}
void GameMouse::WarpFunc()
{
	if (InputManager::Instance().IsUnPressed(L"LMouse"))
	{
		if (ColList.empty() || ColList.front()->GetActor()->NameEqual(L"Warp") == false)
		{
			ChageState(GameMouse::Default);
			m_TagetActor = nullptr;
		}
	}
	else if (m_Player && InputManager::Instance().IsPressed(L"LMouse"))
	{
		if (m_TagetActor->GetPosition().Distance(m_Player->GetPosition()) > 10.0f)
		{
			m_Player->OrderRunMove(m_TagetActor->GetPosition());
		}
		else
		{
			((WarpObject*)m_TagetActor)->OnWarp(m_Player);
			ColList.clear();
			ChageState(GameMouse::Default);
			m_TagetActor = nullptr;
		}
	}
}
void GameMouse::AttackFunc() 
{
	if (ColList.empty() || ColList.front()->GetActor()->NameEqual(L"Monster") == false)
	{
		ChageState(GameMouse::Default);
		return;
	}
	if (InputManager::Instance().IsPressed(L"LMouse"))
	{
		ChageState(MouseState::AttackClick);
		m_TagetActor = ColList.front()->GetActor();
		m_Player->OrderAttack(static_cast<BattlePawn*>(m_TagetActor));
		return;
	}

	if (m_Player && InputManager::Instance().IsDown(L"RMouse"))
	{
		m_TagetActor = ColList.front()->GetActor();
		m_Player->OrderMagie(static_cast<BattlePawn*>(m_TagetActor));
		return;
	}
}
void GameMouse::AttackClickFunc()
{
	if (InputManager::Instance().IsUp(L"LMouse"))
	{
		ChageState(MouseState::Attack);
		m_TagetActor = nullptr;
	}
	else
	{
		m_Player->OrderAttack(static_cast<BattlePawn*>(m_TagetActor));
	}
}

void GameMouse::HandFunc()
{

}
