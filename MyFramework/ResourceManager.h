#pragma once
#include<map>
#include<set>
#include <fmod.hpp>

#ifdef _WIN64
#pragma comment(lib, "fmod64_vc.lib")
#else
#pragma comment(lib, "fmod_vc.lib")
#endif

class GameImage;
class GameSprite;
class MultiSprite;
class GameSound;
class SoundPlayer;
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
public:
	static ResourceManager& Instance()
	{
		static ResourceManager instance = ResourceManager();
		return instance;
	}

private:
	std::map<std::wstring, std::wstring> m_PathMap;
	std::wstring m_Root;
public:
	inline std::wstring RootPath() const
	{
		return m_Root;
	}
	inline const wchar_t* RootPathPtr() const
	{
		return m_Root.c_str();
	}

public:
	void Init();
	std::wstring FindPath(const wchar_t* _key);
	bool RootToCreatePath(const wchar_t* _key);
	bool RootToCreatePath(const wchar_t* _key, const wchar_t* _folder);

//////////////////////////////////////////////////
// Back Buffer									//
private:
	GameImage* m_BackBuffer;
public:
	HDC GetBackBuffer() const;

//////////////////////////////////////////////////
// Image										//

private:
	std::map<std::wstring, GameImage*> m_GameImage;

public:
	GameImage* LoadToPathBmp(const wchar_t* _FolderKey, const wchar_t* _imageName, DWORD _transColor = RGB(255,0,255));
	GameImage* FindImage(const wchar_t* _imageKey);

//////////////////////////////////////////////////
// Sprite										//

private:
	std::map<std::wstring, GameSprite*> m_GameSprite;

public:
	GameSprite * CreateSprite(const wchar_t * _imageName);
	GameSprite* CreateSprite(const wchar_t* _imageName,Vector2f _pos, Vector2f _size);
	GameSprite* CreateSprite(const wchar_t* _SpriteName, const wchar_t* _imageName, Vector2f _pos, Vector2f _size);

	GameSprite* FindSprite(const wchar_t* _SpriteName);

//////////////////////////////////////////////////
// MultiSprite									//
private:
	std::map<std::wstring, MultiSprite*> m_MultiSprite;
public:
	MultiSprite* CreateMultiSprite(const wchar_t* _imageName, Vector2f _size);
	MultiSprite* CreateMultiSprite(const wchar_t* _SpriteName, const wchar_t* _imageName, Vector2f _size);

	MultiSprite* FindMultiSprite(const wchar_t* _multiSpriteName);
	GameSprite* FindSprite(const wchar_t* _key, size_t _idx);

//////////////////////////////////////////////////
// Sound										//
public:
	friend GameSound;
	friend SoundPlayer;
private:
	FMOD::System* m_SoundSystem;
	std::map<std::wstring, GameSound*> m_SoundMap;
	std::set<SoundPlayer*> m_SoundPlayerSet;

public:
	SoundPlayer* CreateSoundPlayer();
	bool ReleaseSoundPlayer(SoundPlayer* _player);

public:
	GameSound* LoadSound(const wchar_t* _folderKey, const wchar_t* _fileName, bool isLoop = false);
	GameSound* FindSound(const wchar_t* _SoundName);

	void PlaySound(const wchar_t* _SoundName);


};