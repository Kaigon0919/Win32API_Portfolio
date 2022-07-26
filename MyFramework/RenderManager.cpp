#include "stdafx.h"
#include "RenderManager.h"
#include"ActorRenderer.h"
#include"Actor.h"

// 백버퍼를 한번 클리어해주기 위한 Include
#include"ResourceManager.h"

bool YSortFunc(const ActorRenderer* one, ActorRenderer* two)
{
	if (one->GetActor()->GetPosition().y < two->GetActor()->GetPosition().y)
	{
		return true;
	}
	return false;
}

RenderManager::RenderManager() : m_BackBufferColor(0)
{
}


RenderManager::~RenderManager()
{
}

void RenderManager::PushRenderer(int _Order, ActorRenderer * _Renderer)
{
	std::map<int, std::list<ActorRenderer*>>::iterator taget = m_RenderMap.find(_Order);
	if (m_RenderMap.end() == taget)
	{
		std::list<ActorRenderer*> NewList;
		NewList.push_back(_Renderer);
		m_RenderMap.insert(std::map<int, std::list<ActorRenderer*>>::value_type(_Order, NewList));
		return;
	}

	taget->second.push_back(_Renderer);
}

void RenderManager::Render()
{

	// 백버퍼 클리어.
	BitmapBufferClear(ResourceManager::Instance().GetBackBuffer());

	StartMapIter = m_RenderMap.begin();
	EndMapIter = m_RenderMap.end();

	for (; StartMapIter != EndMapIter; StartMapIter++)
	{
		itYSort = m_YSet.find(StartMapIter->first);
		if (itYSort != m_YSet.end())
		{
			StartMapIter->second.sort(YSortFunc);
		}

		StartListIter = StartMapIter->second.begin();
		EndListIter = StartMapIter->second.end();

		for (; StartListIter != EndListIter; StartListIter++)
		{
			if (false == (*StartListIter)->IsUpdate())
			{
				continue;
			}

			(*StartListIter)->Render();
		}
	}
}

void RenderManager::Release()
{
	StartMapIter = m_RenderMap.begin();
	EndMapIter = m_RenderMap.end();

	for (; StartMapIter != EndMapIter; StartMapIter++)
	{
		StartListIter = StartMapIter->second.begin();
		EndListIter = StartMapIter->second.end();

		for (; StartListIter != EndListIter; )
		{
			if (!(*StartListIter)->IsDeath())
			{
				++StartListIter;
				continue;
			}
			StartListIter = StartMapIter->second.erase(StartListIter);
		}
	}
}

void RenderManager::YSortOn(int _index)
{
	itYSort = m_YSet.find(_index);
	if (itYSort == m_YSet.end())
	{
		m_YSet.insert(_index);
	}
}

void RenderManager::BitmapBufferClear(HDC _buffer,Vector2f _size /*= Vector2f::zero*/ )
{
	if (_size == Vector2f::zero)
	{
		_size = SystemClass::Instance().GetWindowsSize();
	}
	HBRUSH backColor = (HBRUSH)CreateSolidBrush(m_BackBufferColor);
	RECT rt = { 0, 0 , static_cast<long>(_size.x), static_cast<long>(_size.y) };
	FillRect(_buffer, &rt, backColor); //도화지 색 변경
	DeleteObject(backColor);
}
