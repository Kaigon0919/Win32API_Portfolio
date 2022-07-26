#include "stdafx.h"
#include "IsoMetricTileRenderer.h"
#include"Actor.h"
#include"Level.h"
#include"MultiSprite.h"
#include"GameSprite.h"

IsoMetricTileRenderer::IsoMetricTileRenderer()
{
}


IsoMetricTileRenderer::~IsoMetricTileRenderer()
{
	Reset();
}

size_t IsoMetricTileRenderer::GetTileStateCount()const
{
	return m_TileSprite->SpriteCount();
}

void IsoMetricTileRenderer::Reset()
{
	std::map<__int64, TileData*>::iterator itTileMapStart = m_TileDataMap.begin();
	std::map<__int64, TileData*>::iterator itTileMapEnd = m_TileDataMap.end();

	for (; itTileMapStart != itTileMapEnd; ++itTileMapStart)
	{
		delete itTileMapStart->second;
	}

	m_TileDataMap.clear();
}

void IsoMetricTileRenderer::CreateMap(const wchar_t * _name, Vector2f _tileSize)
{
	m_TileSprite = ResourceManager::Instance().FindMultiSprite(_name);
	m_Size = _tileSize;
}

IsoMetricTileRenderer::TileData * IsoMetricTileRenderer::SetTile(Vector2i _index, int _spriteIndex)
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

IsoMetricTileRenderer::TileData * IsoMetricTileRenderer::ScreenPosSetTile(Vector2f _index, int _spriteIndex)
{
	_index += GetActor()->GetLevel()->GetCameraPosition();

	return WorldPosSetTile(_index, _spriteIndex);
}

IsoMetricTileRenderer::TileData * IsoMetricTileRenderer::WorldPosSetTile(Vector2f _index, int _spriteIndex)
{
	Vector2f tileIndex = Vector2f((_index.x / m_Size.GetHalfX() + _index.y / m_Size.GetHalfY()) / 2.0f, (_index.y / m_Size.GetHalfY() - _index.x / m_Size.GetHalfX()) / 2.0f);
	tileIndex.x -= 0.5;
	if (tileIndex.x < 0)
	{
		tileIndex.x -= 1.0;
	}
	if (tileIndex.y < 0)
	{
		tileIndex.y -= 0.5f;
	}
	else
	{
		tileIndex.y += 0.5f;
	}
	return SetTile(Vector2i(static_cast<int>(tileIndex.x), static_cast<int>(tileIndex.y)), _spriteIndex);
}

void IsoMetricTileRenderer::DeleteTile(Vector2i _index)
{
	std::map<__int64, TileData*>::iterator findIter = m_TileDataMap.find(_index);
	if (findIter != m_TileDataMap.end())
	{
		delete findIter->second;
		findIter->second = nullptr;
		m_TileDataMap.erase(findIter);
	}

}

void IsoMetricTileRenderer::ScreenPosDeleteTile(Vector2f _index)
{
	_index += GetActor()->GetLevel()->GetCameraPosition();
	WorldPosDeleteTile(_index);
}

void IsoMetricTileRenderer::WorldPosDeleteTile(Vector2f _index)
{
	Vector2f tileIndex = Vector2f((_index.x / m_Size.GetHalfX() + _index.y / m_Size.GetHalfY()) / 2.0f, (_index.y / m_Size.GetHalfY() - _index.x / m_Size.GetHalfX()) / 2.0f);

	tileIndex.x -= 0.5;
	if (tileIndex.x < 0)
	{
		tileIndex.x -= 1.0;
	}
	if (tileIndex.y < 0)
	{
		tileIndex.y -= 0.5f;
	}
	else
	{
		tileIndex.y += 0.5f;
	}

	DeleteTile(tileIndex);
}

IsoMetricTileRenderer::TileData * IsoMetricTileRenderer::FindTile(Vector2i _index)
{
	std::map<__int64, TileData*>::iterator FindIter = m_TileDataMap.find(_index);

	if (FindIter != m_TileDataMap.end())
	{
		return FindIter->second;
	}
	return nullptr;
}


void IsoMetricTileRenderer::Render()
{
	std::map<__int64, TileData*>::iterator itTileMapStart = m_TileDataMap.begin();
	std::map<__int64, TileData*>::iterator itTileMapEnd = m_TileDataMap.end();

	Vector2i Pos;
	for (; itTileMapStart != itTileMapEnd; ++itTileMapStart)
	{
		Pos = itTileMapStart->first;
		Vector2f newPos = Vector2f();
		newPos.x = static_cast<float>((Pos.x - Pos.y) * m_Size.GetHalfIntX());
		newPos.y = static_cast<float>((Pos.x + Pos.y) * m_Size.GetHalfIntY());

		if (true == m_bCamera)
		{
			newPos -= GetActor()->GetLevel()->GetCameraPosition();
		}

		GameSprite* TileSprite = m_TileSprite->GetSprite(itTileMapStart->second->SpriteIndex);

		if (TileSprite == nullptr)
		{
			return;
		}

		TransparentBlt(ResourceManager::Instance().GetBackBuffer(),
			(int)newPos.x,
			(int)newPos.y,
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

int IsoMetricTileRenderer::WorldPosGetState(Vector2f _index)
{
	Vector2f tileIndex = Vector2f((_index.x / m_Size.GetHalfX() + _index.y / m_Size.GetHalfY()) / 2.0f, (_index.y / m_Size.GetHalfY() - _index.x / m_Size.GetHalfX()) / 2.0f);
	tileIndex.x -= 0.5;
	if (tileIndex.x < 0)
	{
		tileIndex.x -= 1.0;
	}
	if (tileIndex.y < 0)
	{
		tileIndex.y -= 0.5f;
	}
	else
	{
		tileIndex.y += 0.5f;
	}
	TileData * taget = FindTile(Vector2i(tileIndex.x, tileIndex.y));
	if (!taget)
	{
		return -1;
	}
	return taget->SpriteIndex;
}

int IsoMetricTileRenderer::ScreenPosGetState(Vector2f _index)
{
	_index += GetActor()->GetLevel()->GetCameraPosition();
	Vector2f tileIndex = Vector2f((_index.x / m_Size.GetHalfX() + _index.y / m_Size.GetHalfY()) / 2.0f, (_index.y / m_Size.GetHalfY() - _index.x / m_Size.GetHalfX()) / 2.0f);
	tileIndex.x -= 0.5;
	if (tileIndex.x < 0)
	{
		tileIndex.x -= 1.0;
	}
	if (tileIndex.y < 0)
	{
		tileIndex.y -= 0.5f;
	}
	else
	{
		tileIndex.y += 0.5f;
	}
	TileData * taget = FindTile(Vector2i(tileIndex.x, tileIndex.y));
	if (!taget)
	{
		return -1;
	}
	return taget->SpriteIndex;
}

int IsoMetricTileRenderer::PosGetState(Vector2f _index)
{
	TileData * taget = FindTile(Vector2i(_index.x, _index.y));
	if (!taget)
	{
		return -1;
	}
	return taget->SpriteIndex;
}

void IsoMetricTileRenderer::GetAllTileData(OutputTileData * _buffer, int _bufferSize)
{
	std::map<__int64, TileData*>::iterator itStart = m_TileDataMap.begin();
	std::map<__int64, TileData*>::iterator itEnd = m_TileDataMap.end();

	int count = 0;

	for (; itStart != itEnd; ++itStart)
	{
		_buffer[count]._index = itStart->first;
		_buffer[count]._data = *(itStart->second);
		++count;

		if (count >= _bufferSize)
		{
			break;
		}
	}
}
