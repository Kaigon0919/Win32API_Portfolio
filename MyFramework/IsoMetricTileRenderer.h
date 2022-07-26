#pragma once
#include "ActorRenderer.h"
class IsoMetricTileRenderer : public ActorRenderer
{
private:
	IsoMetricTileRenderer();
	~IsoMetricTileRenderer();
public:
	friend class Actor;
public: // inner Class
	class TileData
	{
	public:
		int SpriteIndex;
	};

	class OutputTileData
	{
	public:
		Vector2i _index;
		TileData _data;
	};
private:
	MultiSprite* m_TileSprite;
	std::map<__int64, TileData*> m_TileDataMap;

public:
	inline size_t GetTileCount()const
	{
		return m_TileDataMap.size();
	}
	size_t GetTileStateCount()const;
public:
	void Reset();
	void CreateMap(const wchar_t* _name, Vector2f _tileSize);

	TileData* SetTile(Vector2i _index, int _spriteIndex = 0);
	TileData* ScreenPosSetTile(Vector2f _index, int _spriteIndex = 0);
	TileData* WorldPosSetTile(Vector2f _index, int _spriteIndex = 0);

	void DeleteTile(Vector2i _index);
	void ScreenPosDeleteTile(Vector2f _index);
	void WorldPosDeleteTile(Vector2f _index);

	TileData* FindTile(Vector2i _index);

	int WorldPosGetState(Vector2f _index);
	int ScreenPosGetState(Vector2f _index);
	int PosGetState(Vector2f _index);

	void GetAllTileData(OutputTileData* _buffer, int _bufferSize);
private:
	void Render() override;
};

