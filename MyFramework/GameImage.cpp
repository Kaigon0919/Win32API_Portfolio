#include "stdafx.h"
#include "GameImage.h"
#include"IFStream.h"

GameImage::GameImage() :m_ImageDC(nullptr), m_Bitmap(nullptr), m_OldBitmap(nullptr), m_BitmapInfo(), transColor(0), m_bAlpha(false)
{
}


GameImage::~GameImage()
{
	SelectObject(m_ImageDC, m_OldBitmap);
	DeleteObject(m_Bitmap);
	DeleteDC(m_ImageDC);
}

bool GameImage::Create(const Vector2f& _size)
{
	if (!SystemClass::Instance().GetHDC())
	{
		return false;
	}
	m_ImageDC = CreateCompatibleDC(SystemClass::Instance().GetHDC());
	if (!m_ImageDC)
	{
		return false;
	}

	m_Bitmap = CreateCompatibleBitmap(SystemClass::Instance().GetHDC(), _size.GetIntX(), _size.GetIntY());
	if (!m_Bitmap)
	{
		return false;
	}

	m_OldBitmap = (HBITMAP)SelectObject(m_ImageDC, m_Bitmap);
	GetObject(m_Bitmap, sizeof(BITMAP), &m_BitmapInfo);

	return true;
}

bool GameImage::Load(const wchar_t * _path)
{
	if (_path == L"")
	{
		return false;
	}

	if (!SystemClass::Instance().GetHINSTANCE())
	{
		return false;
	}
	
	m_Bitmap = (HBITMAP)LoadImageW(SystemClass::Instance().GetHINSTANCE(), _path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (!m_Bitmap)
	{
		return false;
	}


	if (!SystemClass::Instance().GetHDC())
	{
		return false;
	}
	m_ImageDC = CreateCompatibleDC(SystemClass::Instance().GetHDC());

	if (!m_ImageDC)
	{
		return false;
	}

	m_OldBitmap = (HBITMAP)SelectObject(m_ImageDC, m_Bitmap);
	GetObject(m_Bitmap, sizeof(BITMAP), &m_BitmapInfo);

	IFStream fs = IFStream(_path);

	fs.Seek(sizeof(BITMAPFILEHEADER));
	fs.Read(&m_BitInfo, sizeof(m_BitInfo), sizeof(m_BitInfo));

	if (32 <= m_BitInfo.biBitCount)
	{
		m_bAlpha = true;
	}

	return true;
}
