#include "stdafx.h"
#include "Level.h"
#include"Actor.h"
#include"ActorRenderer.h"
#include"ActorCollision.h"

#ifdef _DEBUG
bool Level::IsDebugMode = true;
#else
bool Level::IsDebugMode = false;
#endif

std::list<Actor*> Level::m_OverActorList = std::list<Actor*>();

Level::Level() : isLoading(false), m_ActorList(),m_IteratorEnd(),m_IteratorStart()
{

}


Level::~Level()
{
	m_IteratorStart = m_ActorList.begin();
	m_IteratorEnd = m_ActorList.end();

	for (;m_IteratorStart != m_IteratorEnd;++m_IteratorStart)
	{
		if (*m_IteratorStart && false == (*m_IteratorStart)->IsStateOver())
		{
			delete *m_IteratorStart;
			*m_IteratorStart = nullptr;
		}
	}
}
void Level::EndDestroy()
{
	std::list<Actor*>::iterator OverStart = m_OverActorList.begin();
	std::list<Actor*>::iterator OverEnd = m_OverActorList.end();

	for (; OverStart != OverEnd; OverStart++)
	{
		if (nullptr != (*OverStart))
		{
			delete (*OverStart);
			(*OverStart) = nullptr;
		}
	}
}

bool Level::IsHaveCheck(Actor* _Actor)
{
	m_IteratorStart = m_ActorList.begin();
	m_IteratorEnd = m_ActorList.end();

	for (; m_IteratorStart != m_IteratorEnd; m_IteratorStart++)
	{
		if (_Actor == (*m_IteratorStart))
		{
			return true;
		}
	}

	return false;
}

Actor * Level::FindOverActor(const wchar_t * ActorName)
{
	std::list<Actor*>::iterator OverStart = m_OverActorList.begin();
	std::list<Actor*>::iterator OverEnd = m_OverActorList.end();

	for (; OverStart != OverEnd; OverStart++)
	{
		if ((*OverStart)->NameEqual(ActorName))
		{
			return *OverStart;
		}
	}
	return nullptr;
}

void Level::PrevUpdate()
{
	m_IteratorStart = m_ActorList.begin();
	m_IteratorEnd = m_ActorList.end();

	for (; m_IteratorStart != m_IteratorEnd; ++m_IteratorStart)
	{
		if (!(*m_IteratorStart)->IsUpdate()) { continue; }
		(*m_IteratorStart)->PrevUpdate();
	}
}

void Level::Update()
{
	m_IteratorStart = m_ActorList.begin();
	m_IteratorEnd = m_ActorList.end();

	for (; m_IteratorStart != m_IteratorEnd; ++m_IteratorStart)
	{
		if (!(*m_IteratorStart)->IsUpdate()) { continue; }
		(*m_IteratorStart)->Update();
	}
}

void Level::LateUpdate()
{
	m_IteratorStart = m_ActorList.begin();
	m_IteratorEnd = m_ActorList.end();

	for (; m_IteratorStart != m_IteratorEnd; ++m_IteratorStart)
	{
		if (!(*m_IteratorStart)->IsUpdate()) { continue; }
		(*m_IteratorStart)->LateUpdate();
	}
}

void Level::Release()
{
	m_RenderMgr.Release();
	m_ColMgr.Release();

	m_IteratorStart = m_ActorList.begin();
	m_IteratorEnd = m_ActorList.end();

	while (m_IteratorStart != m_IteratorEnd)
	{
		if (!(*m_IteratorStart)->IsDeath())
		{
			++m_IteratorStart;
			continue;
		}
		
		delete (*m_IteratorStart);
		m_IteratorStart = m_ActorList.erase(m_IteratorStart);
	}
}

void Level::Collision()
{
	m_ColMgr.ColUpdate();
}

void Level::Render()
{
	m_RenderMgr.Render();

	if (IsDebugMode)
	{
		m_ColMgr.DebugRender();

		m_IteratorStart = m_ActorList.begin();
		m_IteratorEnd = m_ActorList.end();

		for (; m_IteratorStart != m_IteratorEnd;++m_IteratorStart)
		{
			if ((*m_IteratorStart)->IsUpdate() == false)
			{
				continue;
			}
			(*m_IteratorStart)->DebugRender();
		}
	}
}
void Level::AfterRender()
{
	m_IteratorStart = m_ActorList.begin();
	m_IteratorEnd = m_ActorList.end();

	for (; m_IteratorStart != m_IteratorEnd; ++m_IteratorStart)
	{
		if (!(*m_IteratorStart)->IsUpdate()) { continue; }
		(*m_IteratorStart)->AfterRender();
	}
}
Vector2f Level::GetMouseConvertPosition() const
{
	return  Vector2f(m_Camera.x + InputManager::Instance().GetMousePos().x, m_Camera.y+ InputManager::Instance().GetMousePos().y);
}
void Level::PushActor(Actor * _NewActor)
{
	assert(nullptr != _NewActor);
	m_ActorList.push_back(_NewActor);

	std::list<ActorCollision*>::iterator CStartIter = _NewActor->m_pCollisionList.begin();
	std::list<ActorCollision*>::iterator CEndIter = _NewActor->m_pCollisionList.end();

	for (; CStartIter != CEndIter; ++CStartIter)
	{
		m_ColMgr.PushCol((*CStartIter)->GroupName(), (*CStartIter));
	}

	std::list<ActorRenderer*>::iterator RStartIter = _NewActor->m_RenderList.begin();
	std::list<ActorRenderer*>::iterator REndIter = _NewActor->m_RenderList.end();

	for (; RStartIter != REndIter; ++RStartIter)
	{
		m_RenderMgr.PushRenderer((*RStartIter)->Order(), (*RStartIter));
	}
}
Actor * Level::FindActor(const wchar_t * ActorName)
{
	m_IteratorStart = m_ActorList.begin();
	m_IteratorEnd = m_ActorList.end();

	for (; m_IteratorStart != m_IteratorEnd; m_IteratorStart++)
	{
		if ((*m_IteratorStart)->NameEqual(ActorName))
		{
			return (*m_IteratorStart);
		}
	}

	return nullptr;
}
void Level::PushRenderer(int _Order, ActorRenderer * _pRenderer)
{
	m_RenderMgr.PushRenderer(_Order, _pRenderer);
}

void Level::YSortOn(int _Order)
{
	m_RenderMgr.YSortOn(_Order);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Col
void Level::PushCol(const wchar_t * _GroupName, ActorCollision * _collision)
{
	m_ColMgr.PushCol(_GroupName, _collision);
}

void Level::ColLink(const wchar_t * _Left, const wchar_t * _Right)
{
	m_ColMgr.Link(_Left, _Right);
}
