#pragma once
#include "ActorRenderer.h"
#include<map>
class MultiSprite;
class TileMapRenderer :	public ActorRenderer
{
public:
	TileMapRenderer();
	~TileMapRenderer();

public: // inner Class
	class TileData
	{
	public:
		int SpriteIndex;
	};

private:
	MultiSprite* m_TileSprite;
	std::map<__int64, TileData*> m_TileDataMap;

public:
	inline size_t GetTileCount()
	{
		return m_TileDataMap.size();
	}

public:
	void Reset();
	void CreateMap(const wchar_t* _name, Vector2f _tileSize);

	TileData* SetTile(Vector2i _index, int _spriteIndex = 0);
	TileData* ScreenPosSetTile(Vector2f _index, int _spriteIndex = 0);
	TileData* FindTile(Vector2i _index);
	
private:
	void Render() override;
};

