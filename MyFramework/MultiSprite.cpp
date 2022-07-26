#include "stdafx.h"
#include "MultiSprite.h"
#include"GameSprite.h"

MultiSprite::MultiSprite(const size_t _count)
{
	m_Sprites.reserve(_count);
}


MultiSprite::~MultiSprite()
{
	for (size_t i = 0; i < m_Sprites.size(); i++)
	{
		if (m_Sprites[i] != nullptr)
		{
			delete m_Sprites[i];
			m_Sprites[i] = nullptr;
		}
	}
	m_Sprites.clear();
}

void MultiSprite::PushSprite(GameSprite * _taget)
{
	m_Sprites.push_back(_taget);
}
