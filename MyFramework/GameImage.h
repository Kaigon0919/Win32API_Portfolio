#pragma once
class GameImage
{
private:
	GameImage();
	~GameImage();

public:
	friend class ResourceManager;

private:
	HDC m_ImageDC;
	HBITMAP m_Bitmap;
	HBITMAP m_OldBitmap;
	BITMAP m_BitmapInfo;
	BITMAPINFOHEADER m_BitInfo;
	DWORD transColor;
	bool m_bAlpha;

private:
	inline void SetTransColor(const DWORD _transColor)
	{
		transColor = _transColor;
	}

public:
	inline bool IsAlpha()const
	{
		return m_bAlpha;
	}
	inline HDC GetHDC() const
	{
		return m_ImageDC;
	}
	inline UINT GetTransColor() const
	{
		return transColor;
	}
	inline UINT GetWidth()const
	{
		return m_BitmapInfo.bmWidth;
	}
	inline UINT GetHeight()const
	{
		return m_BitmapInfo.bmHeight;
	}
public:
	bool Create(const Vector2f& _size);
	bool Load(const wchar_t* _path);
};

