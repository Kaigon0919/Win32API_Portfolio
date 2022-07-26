#pragma once
#include<vector>

class GameSprite;
class MultiSprite
{
private:
	MultiSprite(const size_t _count);
	~MultiSprite();
public:
	friend class ResourceManager;

private:
	std::vector<GameSprite*> m_Sprites;

private:
	void PushSprite(GameSprite* _taget);
public:
	inline GameSprite* GetSprite(const size_t& idx)
	{
		return m_Sprites[idx];
	}
	inline size_t SpriteCount()const
	{
		return m_Sprites.size();
	}
};

