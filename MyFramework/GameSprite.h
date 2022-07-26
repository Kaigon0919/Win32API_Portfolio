#pragma once
#include"GameImage.h"

class GameSprite
{
private:
	GameSprite(GameImage* const _image, const Vector2f _pos, const Vector2f _size);
	~GameSprite();
public:
	friend class ResourceManager;
	friend class MultiSprite;

private:
	GameImage* m_Image;
	RectFloat m_Rect;

public:
	inline HDC GetHDC() const
	{
		return m_Image->GetHDC();
	}
	inline Vector2f GetPosition() const
	{
		return m_Rect.Position;
	}
	inline Vector2f GetSize() const
	{
		return m_Rect.Size;
	}
	inline UINT GetTransColor() const
	{
		return m_Image->GetTransColor();
	}
	inline bool IsAlpha()const
	{
		return m_Image->IsAlpha();
	}
};

