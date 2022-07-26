#include "stdafx.h"

#include<string>

#include "ResourceManager.h"
#include"GameImage.h"
#include"GameSprite.h"
#include"MultiSprite.h"
#include"GameSound.h"
#include"SoundPlayer.h"

ResourceManager::ResourceManager() :m_PathMap(), m_Root(), m_GameImage(), m_BackBuffer(nullptr)
{
}


ResourceManager::~ResourceManager()
{
	// 이미지 처리.
	std::map<std::wstring, GameImage*>::iterator StartIter = m_GameImage.begin();
	std::map<std::wstring, GameImage*>::iterator EndIter = m_GameImage.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
		}
	}

	// 스프라이트 처리.
	std::map<std::wstring, GameSprite*>::iterator StartSpIter = m_GameSprite.begin();
	std::map<std::wstring, GameSprite*>::iterator EndSpIter = m_GameSprite.end();

	for (; StartSpIter != EndSpIter; ++StartSpIter)
	{
		if (nullptr != StartSpIter->second)
		{
			delete StartSpIter->second;
		}
	}
	std::map<std::wstring, MultiSprite*>::iterator StartMultiSpIter = m_MultiSprite.begin();
	std::map<std::wstring, MultiSprite*>::iterator EndMultiSpIter = m_MultiSprite.end();

	for (; StartMultiSpIter != EndMultiSpIter; ++StartMultiSpIter)
	{
		if (nullptr != StartMultiSpIter->second)
		{
			delete StartMultiSpIter->second;
		}
	}

	// 백버퍼 처리.
	if (m_BackBuffer)
	{
		delete m_BackBuffer;
	}

	// 사운드 처리.
	if (m_SoundSystem)
	{
		m_SoundSystem->release();
		m_SoundSystem = nullptr;
	}
	std::set<SoundPlayer*>::iterator itSoundPlayerStart = m_SoundPlayerSet.begin();
	std::set<SoundPlayer*>::iterator itSoundPlayerEnd = m_SoundPlayerSet.end();
	for (; itSoundPlayerStart != itSoundPlayerEnd; ++itSoundPlayerStart)
	{
		if (*itSoundPlayerStart)
		{
			delete *itSoundPlayerStart;
		}
	}
	m_SoundPlayerSet.clear();


	std::map<std::wstring, GameSound*>::iterator itSoundStart = m_SoundMap.begin();
	std::map<std::wstring, GameSound*>::iterator itSoundEnd = m_SoundMap.end();
	for (; itSoundStart != itSoundEnd; ++itSoundStart)
	{
		if (itSoundStart->second)
		{
			delete itSoundStart->second;
		}
	}
	m_SoundPlayerSet.clear();
}

void ResourceManager::Init()
{
	// 실행하는 파일 위치를 Root에 넣어주는 처리를 해준다.
	wchar_t str[1024] = {};
	int len = GetCurrentDirectoryW(0, nullptr);
	GetCurrentDirectoryW(len, str);
	m_Root = str;

	size_t cutCount = m_Root.find_last_of(L"\\", m_Root.size());
	m_Root = m_Root.replace(cutCount, m_Root.size(), L"\\Bin\\");

	m_BackBuffer = new GameImage();
	if (m_BackBuffer)
	{
		Vector2i winSize = SystemClass::Instance().GetWindowsSize();
		m_BackBuffer->Create(Vector2f(static_cast<float>(winSize.x), static_cast<float>(winSize.y)));
	}
	// Sound
	FMOD::System_Create(&m_SoundSystem);

	assert(m_SoundSystem);
	if (nullptr == m_SoundSystem)
	{
		return;
	}

	// 최대 동시에 1000개를 재생할수 있다.
	FMOD_RESULT Return = m_SoundSystem->init(32, FMOD_DEFAULT, nullptr);
}

std::wstring ResourceManager::FindPath(const wchar_t * _key)
{
	std::map<std::wstring, std::wstring>::iterator taget = m_PathMap.find(_key);
	if (taget != m_PathMap.end())
	{
		return taget->second;
	}
	return L"";
}

bool ResourceManager::RootToCreatePath(const wchar_t * _key)
{
	return RootToCreatePath(_key, _key);
}

bool ResourceManager::RootToCreatePath(const wchar_t * _key, const wchar_t * _folder)
{
	std::map<std::wstring, std::wstring>::iterator taget = m_PathMap.find(_key);

	if (taget != m_PathMap.end())
	{
		return false;
	}
	m_PathMap.insert(std::map<std::wstring, std::wstring>::value_type(_key, m_Root + _folder + L"\\"));
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Back Buffer																																		//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HDC ResourceManager::GetBackBuffer() const
{
	return m_BackBuffer->GetHDC();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Image																																			//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameImage * ResourceManager::LoadToPathBmp(const wchar_t * _FolderKey, const wchar_t * _imageName, DWORD _transColor)
{
	std::map<std::wstring, GameImage*>::iterator Iter = m_GameImage.find(_imageName);
	if (Iter != m_GameImage.end())
	{
		return Iter->second;
	}

	std::wstring path = FindPath(_FolderKey);
	path += _imageName;

	GameImage* newImage = new GameImage();
	newImage->SetTransColor(_transColor);
	if (newImage->Load(path.c_str()) == false)
	{
#ifdef _DEBUG
		wchar_t errorMessage[1024];
		swprintf_s(errorMessage, L"%s : %s", L"Image Load Error", _imageName);
		MessageBox(SystemClass::Instance().GetHWND(), errorMessage, L"ERROR", MB_OK);
#endif
		delete newImage;
		return nullptr;
	}
	m_GameImage.insert(std::map<std::wstring, GameImage*>::value_type(_imageName, newImage));
	return newImage;
}

GameImage * ResourceManager::FindImage(const wchar_t * _imageKey)
{
	std::map<std::wstring, GameImage*>::iterator taget = m_GameImage.find(_imageKey);
	if (taget == m_GameImage.end())
	{
		return nullptr;
	}

	return taget->second;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sprite																																			//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameSprite * ResourceManager::CreateSprite(const wchar_t * _imageName, Vector2f _pos, Vector2f _size)
{
	return CreateSprite(_imageName, _imageName, _pos, _size);
}
GameSprite * ResourceManager::CreateSprite(const wchar_t * _imageName)
{
	GameImage* imageTaget = FindImage(_imageName);
	if (imageTaget == nullptr)
	{

#ifdef _DEBUG
		wchar_t errStr[1024];
		swprintf_s(errStr, L"CreateSpriteError : %s", _imageName);
		MessageBox(SystemClass::Instance().GetHWND(), errStr, L"ERROR", MB_OK);
#endif

		return nullptr;
	}

	Vector2f imageSize = Vector2f(static_cast<float>(imageTaget->GetWidth()), static_cast<float>(imageTaget->GetHeight()));

	return CreateSprite(_imageName, Vector2f(0.0f, 0.0f), imageSize);
}
GameSprite * ResourceManager::CreateSprite(const wchar_t * _SpriteName, const wchar_t * _imageName, Vector2f _pos, Vector2f _size)
{
	// 스프라이트가 만들어져 있으면 그 스프라이트를 반환. 중복생성 방지.
	GameSprite* spriteTaget = FindSprite(_SpriteName);
	if (spriteTaget != nullptr)
	{
		return spriteTaget;
	}

	// 이미지가 없으면 생성에 실패하여 nullptr를 반환한다.
	GameImage* imageTaget = FindImage(_imageName);
	if (imageTaget == nullptr)
	{
		return nullptr;
	}

	// 스프라이트 생성.
	GameSprite* newSprite = new GameSprite(imageTaget, _pos, _size);
	m_GameSprite.insert(std::map<std::wstring, GameSprite*>::value_type(_SpriteName, newSprite));
	return newSprite;
}

GameSprite * ResourceManager::FindSprite(const wchar_t * _SpriteName)
{
	std::map<std::wstring, GameSprite*>::iterator taget = m_GameSprite.find(_SpriteName);

	if (taget == m_GameSprite.end())
	{
		return nullptr;
	}
	return taget->second;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MultiSprite																																		//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MultiSprite * ResourceManager::CreateMultiSprite(const wchar_t * _imageName, Vector2f _size)
{
	return CreateMultiSprite(_imageName, _imageName, _size);
}

// _size의 값 갯수만큼 잘라 저장하는 함수.
MultiSprite * ResourceManager::CreateMultiSprite(const wchar_t * _SpriteName, const wchar_t * _imageName, Vector2f _size)
{
	MultiSprite* pMultiTaget = FindMultiSprite(_SpriteName);

	if (pMultiTaget != nullptr)
	{
		return pMultiTaget;
	}

	GameImage* pImage = FindImage(_imageName);
	if (pImage == nullptr)
	{
#ifdef _DEBUG
		wchar_t errStr[1024];
		swprintf_s(errStr, L"CreateMultiSpriteError : %s", _imageName);
		MessageBox(SystemClass::Instance().GetHWND(), errStr, L"ERROR", MB_OK);
#endif
		return nullptr;
	}

	// 한 컷의 사이즈 계산.
	Vector2f SpriteSize = Vector2f();
	SpriteSize.x = pImage->GetWidth() / _size.x;
	SpriteSize.y = pImage->GetHeight() / _size.y;

	// 멀티스프라이트에 들어갈 갯수를 인자로 넣어 생성.
	MultiSprite* pNewMultiSprite = new MultiSprite(static_cast<int>(_size.x * _size.y));

	// 스프라이트를 하나씩 쪼개 저장.
	for (size_t y = 0; y < _size.y; ++y)
	{
		for (size_t x = 0; x < _size.x; ++x)
		{
			GameSprite* pNewSprite = new GameSprite(pImage, Vector2f(SpriteSize.x*x, SpriteSize.y*y), SpriteSize);
			pNewMultiSprite->PushSprite(pNewSprite);
		}
	}
	m_MultiSprite.insert(std::map<std::wstring, MultiSprite*>::value_type(_SpriteName, pNewMultiSprite));

	return pNewMultiSprite;
}

MultiSprite * ResourceManager::FindMultiSprite(const wchar_t * _multiSpriteName)
{
	std::map<std::wstring, MultiSprite*>::iterator taget = m_MultiSprite.find(_multiSpriteName);
	if (taget == m_MultiSprite.end())
	{
		return nullptr;
	}
	return taget->second;
}

GameSprite * ResourceManager::FindSprite(const wchar_t * _multiSpriteName, size_t _idx)
{
	std::map<std::wstring, MultiSprite*>::iterator Iter = m_MultiSprite.find(_multiSpriteName);

	if (Iter == m_MultiSprite.end())
	{
		return nullptr;
	}

	return Iter->second->GetSprite(_idx);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sound																																			//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SoundPlayer * ResourceManager::CreateSoundPlayer()
{
	SoundPlayer* newPlayer = new SoundPlayer();
	m_SoundPlayerSet.insert(newPlayer);
	return newPlayer;
}

bool ResourceManager::ReleaseSoundPlayer(SoundPlayer * _player)
{
	std::set<SoundPlayer*>::iterator itFind = m_SoundPlayerSet.find(_player);
	if (itFind == m_SoundPlayerSet.end())
	{
		return false;
	}
	delete *itFind;
	m_SoundPlayerSet.erase(itFind);
	return true;
}

GameSound * ResourceManager::LoadSound(const wchar_t * _folderKey, const wchar_t * _fileName, bool isLoop)
{
	GameSound* pSound = FindSound(_fileName);

	if (pSound)
	{
		return pSound;
	}

	pSound = new GameSound();
	std::wstring path = FindPath(_folderKey);
	path += _fileName;

	if (pSound->Load(path.c_str(),isLoop) == false)
	{
#ifdef _DEBUG
		wchar_t errString[1024];
		swprintf_s(errString, L"Fail Load Sound : %s", _fileName);
		MessageBox(SystemClass::Instance().GetHWND(), errString, L"Error SoundLoad", MB_OK);
#endif
		delete pSound;
		return nullptr;
	}

	m_SoundMap.insert(std::map<std::wstring, GameSound*>::value_type(_fileName, pSound));
	return pSound;
}

GameSound * ResourceManager::FindSound(const wchar_t * _SoundName)
{
	std::map<std::wstring, GameSound*>::iterator FindIter = m_SoundMap.find(_SoundName);

	if (FindIter == m_SoundMap.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void ResourceManager::PlaySound(const wchar_t * _SoundName)
{
	GameSound* pSound = FindSound(_SoundName);

	if (nullptr == pSound)
	{
		assert(pSound);
		return;
	}

	m_SoundSystem->playSound(pSound->GetSound(), nullptr, false, nullptr);
}
