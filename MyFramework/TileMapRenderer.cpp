#include "stdafx.h"
#include "TileMapRenderer.h"
#include"ResourceManager.h"
#include"Actor.h"
#include"Level.h"
#include"MultiSprite.h"
#include"GameSprite.h"


TileMapRenderer::TileMapRenderer()
{
}


TileMapRenderer::~TileMapRenderer()
{
	Reset();
}

void TileMapRenderer::Reset()
{
	std::map<__int64, TileData*>::iterator StartIter = m_TileDataMap.begin();
	std::map<__int64, TileData*>::iterator EndIter = m_TileDataMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		delete StartIter->second;
	}

	m_TileDataMap.clear();
}

void TileMapRenderer::CreateMap(const wchar_t * _multiSpriteName, Vector2f _tileSize)
{
	m_TileSprite = ResourceManager::Instance().FindMultiSprite(_multiSpriteName);
	m_Size = _tileSize;
}

TileMapRenderer::TileData * TileMapRenderer::SetTile(Vector2i _index, int _spriteIndex)
{
	std::map<__int64, TileData*>::iterator findIter = m_TileDataMap.find(_index);
	if (findIter != m_TileDataMap.end())
	{
		findIter->second->SpriteIndex = _spriteIndex;
		return findIter->second;
	}

	TileData* newTile = new TileData();
	newTile->SpriteIndex = _spriteIndex;
	m_TileDataMap.insert(std::map<__int64, TileData*>::value_type(_index, newTile));
	
	return newTile;
}

TileMapRenderer::TileData * TileMapRenderer::ScreenPosSetTile(Vector2f _index, int _spriteIndex)
{
	_index += GetActor()->GetLevel()->GetCameraPosition();
	Vector2i tileIndex = Vector2i( (int)(_index.x/ m_Size.x) , (int)(_index.y / m_Size.y));

	return SetTile(tileIndex, _spriteIndex);
}

TileMapRenderer::TileData * TileMapRenderer::FindTile(Vector2i _index)
{
	std::map<__int64, TileData*>::iterator FindIter = m_TileDataMap.find(_index);

	if (FindIter != m_TileDataMap.end())
	{
		return FindIter->second;
	}
	return nullptr;
}

void TileMapRenderer::Render()
{
	std::map<__int64, TileData*>::iterator StartIter = m_TileDataMap.begin();
	std::map<__int64, TileData*>::iterator EndIter = m_TileDataMap.end();

	Vector2i Pos;
	for (; StartIter != EndIter; ++StartIter)
	{
		Pos = StartIter->first;
		Pos.x = (int)(Pos.x * m_Size.x);
		Pos.y = (int)(Pos.y * m_Size.y);

		if (true == m_bCamera)
		{
			Pos -= GetActor()->GetLevel()->GetCameraPosition();
		}

		GameSprite* TileSprite = m_TileSprite->GetSprite(StartIter->second->SpriteIndex);

		if (TileSprite == nullptr)
		{
			return;
		}
		TransparentBlt(ResourceManager::Instance().GetBackBuffer(),
			Pos.x,
			Pos.y,
			(int)(m_Size.x),
			(int)(m_Size.y),
			TileSprite->GetHDC(),
			TileSprite->GetPosition().GetIntX(),
			TileSprite->GetPosition().GetIntY(),
			TileSprite->GetSize().GetIntX(),
			TileSprite->GetSize().GetIntY(),
			TileSprite->GetTransColor()
		);
	}
}
