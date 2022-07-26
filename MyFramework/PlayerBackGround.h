#pragma once
#include "Actor.h"

class IsoMetricTileRenderer;
class SingleRenderer;
class TileMapRenderer;
class PlayerBackGround : public Actor
{
public:
	PlayerBackGround();
	~PlayerBackGround();
private:
	SingleRenderer* pRenderer;
	IsoMetricTileRenderer* m_IsoTileRenderer;
public:
	virtual void Init() override;
	virtual void PrevUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void DebugRender();
public:
	bool IsTileEqualState(const Vector2f& ref, int _State);
	void SetTile(const Vector2f &ref, int _State);
	void SetSprite(const wchar_t * _SpriteName);
	void SetSize(const Vector2f &ref);
	bool Load(const wchar_t * dataName);
};

