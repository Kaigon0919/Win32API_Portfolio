#pragma once
#include "ActorRenderer.h"

class GameSprite;
class SingleRenderer : public ActorRenderer
{
public:
	SingleRenderer();
	~SingleRenderer();

private:
	GameSprite * m_Sprite;
	BYTE m_AlphaValue;
public:
	virtual void Render() override;
	virtual void SettingSprite(const wchar_t * key);
	void SettingSprite(const wchar_t* _pImageName, size_t _Count);


	inline void SetAlphaValue(BYTE alpha)
	{
		m_AlphaValue = alpha;
	}
};

