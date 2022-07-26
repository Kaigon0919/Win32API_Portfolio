#include "stdafx.h"
#include "PlayerBackGround.h"
#include"Level.h"
#include"Render.h"
#include"IFStream.h"


PlayerBackGround::PlayerBackGround()
{
}


PlayerBackGround::~PlayerBackGround()
{
}

void PlayerBackGround::Init()
{
	//Vector2i winSize = SystemClass::Instance().GetWindowsSize();
	//SetPosition(winSize.GetHalfX(), winSize.GetHalfY());

	m_IsoTileRenderer = CreateRenderer<IsoMetricTileRenderer>(-4);
	m_IsoTileRenderer->CreateMap(L"Tile01", Vector2f(64.0f, 32.0f));
	m_IsoTileRenderer->UpdateOff();

	pRenderer = CreateRenderer<SingleRenderer>(-5);
}

void PlayerBackGround::PrevUpdate()
{
#ifdef _DEBUG
	m_IsoTileRenderer->SetUpdate(GetLevel()->IsDebug());
#endif
}

void PlayerBackGround::Update()
{
}

void PlayerBackGround::LateUpdate()
{
}

void PlayerBackGround::DebugRender()
{
}

bool PlayerBackGround::IsTileEqualState(const Vector2f & ref, int _State)
{
	if (!m_IsoTileRenderer)
	{
		return false;
	}
	int tileState = m_IsoTileRenderer->WorldPosGetState(ref);

	return tileState == _State;
}
void PlayerBackGround::SetTile(const Vector2f &ref, int _State)
{
	Vector2i iVec = Vector2i(ref.x,ref.y);
	m_IsoTileRenderer->WorldPosSetTile(iVec, _State);
}

void PlayerBackGround::SetSprite(const wchar_t * _SpriteName)
{
	pRenderer->SettingSprite(_SpriteName);
}

void PlayerBackGround::SetSize(const Vector2f & ref)
{
	pRenderer->SetSize(ref);
}

bool PlayerBackGround::Load(const wchar_t * dataName)
{
	m_IsoTileRenderer->Reset();

	std::wstring path = ResourceManager::Instance().FindPath(L"MapData");
	std::wstring fileName = dataName;
	path += fileName;

	IFStream is = IFStream(path.c_str());

	if (!is.IsOpen())
	{
		// 읽어지지 않았다.
		assert(false);
		return false;
	}

	size_t count = 0;

	is.Read(&count, sizeof(size_t), sizeof(size_t));
	IsoMetricTileRenderer::OutputTileData* LoadTile = new IsoMetricTileRenderer::OutputTileData[count];

	is.Read(LoadTile, sizeof(IsoMetricTileRenderer::OutputTileData)*(int)count, sizeof(IsoMetricTileRenderer::OutputTileData)*(int)count);

	for (size_t i = 0; i < count; ++i)
	{
		IsoMetricTileRenderer::OutputTileData readData = LoadTile[i];
		m_IsoTileRenderer->SetTile(LoadTile[i]._index, LoadTile[i]._data.SpriteIndex);
	}
	delete[] LoadTile;
	return true;
}