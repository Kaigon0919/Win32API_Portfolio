#include "stdafx.h"
#include "CollisionManager.h"
#include"ActorCollision.h"

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
	std::map<std::wstring, ColGroup*>::iterator Start = m_ColMap.begin();
	std::map<std::wstring, ColGroup*>::iterator End = m_ColMap.end();

	for (; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			delete Start->second;
		}
	}
	m_ColMap.clear();
}

CollisionManager::ColGroup * CollisionManager::FindColGroup(const wchar_t * _GroupName)
{
	m_itFind= m_ColMap.find(_GroupName);

	if (m_itFind == m_ColMap.end())
	{
		ColGroup* pG = new ColGroup();
		pG->name = _GroupName;
		m_ColMap.insert(std::map<std::wstring, ColGroup*>::value_type(_GroupName, pG));
		return pG;
	}

	return m_itFind->second;
}

void CollisionManager::PushCol(const wchar_t * _GroupName, ActorCollision * _Col)
{
	ColGroup* pG = FindColGroup(_GroupName);

	assert(pG);
	if (!pG)
	{
		return;
	}
	pG->PushCol(_Col);
}

void CollisionManager::Link(const wchar_t * _Left, const wchar_t * _Right)
{
	ColGroup* pLeft = FindColGroup(_Left);
	ColGroup* pRight = FindColGroup(_Right);

	assert(pLeft && pRight);
	if (nullptr == pLeft || nullptr == pRight)
	{
		return;
	}

	pLeft->Link(pRight);
}

void CollisionManager::ColUpdate()
{
	std::map<std::wstring, ColGroup*>::iterator Start = m_ColMap.begin();
	std::map<std::wstring, ColGroup*>::iterator End = m_ColMap.end();

	for (; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			Start->second->ColSetting();
			Start->second->ColUpdate();
		}
	}
}

void CollisionManager::Release()
{
	std::map<std::wstring, ColGroup*>::iterator Start = m_ColMap.begin();
	std::map<std::wstring, ColGroup*>::iterator End = m_ColMap.end();

	for (; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			Start->second->Release();
		}
	}
}

void CollisionManager::DebugRender()
{
	std::map<std::wstring, ColGroup*>::iterator Start = m_ColMap.begin();
	std::map<std::wstring, ColGroup*>::iterator End = m_ColMap.end();

	for (; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			Start->second->DebugRender();
		}
	}
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ColGroup

CollisionManager::ColGroup::ColGroup(){}
CollisionManager::ColGroup::~ColGroup(){}

// 충돌 가능 그룹 설정.
void CollisionManager::ColGroup::Link(ColGroup * _otherGroup)
{
	assert(_otherGroup);
	if (!_otherGroup)
	{
		return;
	}

	m_itGroupStart = m_OtherColGroup.begin();
	m_itGroupEnd = m_OtherColGroup.end();

	for (; m_itGroupStart != m_itGroupEnd; ++m_itGroupStart)
	{
		if (*m_itGroupStart == _otherGroup)
		{
			return;
		}
	}

	m_OtherColGroup.push_back(_otherGroup);
}

// 충돌한 객체 정보 저장.
void CollisionManager::ColGroup::PushCol(ActorCollision * _col)
{
	m_ColList.push_back(_col);
}

// 그룹간 충돌 체크.
void CollisionManager::ColGroup::ColCheck(ColGroup * _otherGroup)
{
	if (this == _otherGroup)
	{
		// 본인 그룹끼리의 충돌이 필요한 경우 별도로 적어줘야한다.
	}
	else
	{
		m_itThisStart = m_ColList.begin();
		m_itThisEnd = m_ColList.end();

		for (; m_itThisStart != m_itThisEnd; ++m_itThisStart)
		{
			// 업데이트가 꺼져있으면 처리안함.
			if (!(*m_itThisStart)->IsUpdate())
			{
				continue;
			}

			m_itOtherStart = _otherGroup->m_ColList.begin();
			m_itOtherEnd = _otherGroup->m_ColList.end();

			for (;m_itOtherStart != m_itOtherEnd; ++m_itOtherStart)
			{
				if (!(*m_itOtherStart)->IsUpdate())
				{
					continue;
				}

				(*m_itThisStart)->ColCheck(*m_itOtherStart);
			}
		}
	}
}

void CollisionManager::ColGroup::ColUpdate()
{
	m_itGroupStart = m_OtherColGroup.begin();
	m_itGroupEnd = m_OtherColGroup.end();
	for (; m_itGroupStart != m_itGroupEnd; ++m_itGroupStart)
	{
		ColCheck(*m_itGroupStart);
	}
}

void CollisionManager::ColGroup::ColSetting()
{
	m_itThisStart= m_ColList.begin();
	m_itThisEnd = m_ColList.end();

	for (; m_itThisStart != m_itThisEnd; ++m_itThisStart)
	{
		(*m_itThisStart)->ParentPosSetting();
	}
}

void CollisionManager::ColGroup::Release()
{
	m_itThisStart = m_ColList.begin();
	m_itThisEnd = m_ColList.end();

	for (; m_itThisStart != m_itThisEnd; )
	{
		if (true == (*m_itThisStart)->IsDeath())
		{
			m_itThisStart = m_ColList.erase(m_itThisStart);
		}
		else {
			++m_itThisStart;
		}
	}
}

void CollisionManager::ColGroup::DebugRender()
{
	m_itThisStart = m_ColList.begin();
	m_itThisEnd = m_ColList.end();

	for (; m_itThisStart != m_itThisEnd; ++m_itThisStart)
	{
		if ((*m_itThisStart)->IsUpdate() == false)
		{
			continue;
		}
		(*m_itThisStart)->DebugRender();
	}
}
