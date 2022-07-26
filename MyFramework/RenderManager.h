#pragma once
#include<map>
#include<list>
#include<set>

class ActorRenderer;
class RenderManager
{
public:
	RenderManager();
	~RenderManager();
private:
	friend class Level;
private:
	std::map<int, std::list<ActorRenderer*>>::iterator StartMapIter;
	std::map<int, std::list<ActorRenderer*>>::iterator EndMapIter;

	std::list<ActorRenderer*>::iterator StartListIter;
	std::list<ActorRenderer*>::iterator EndListIter;
	std::map<int, std::list<ActorRenderer*>> m_RenderMap;

	std::set<int>::iterator itYSort;
	std::set<int> m_YSet;

	DWORD m_BackBufferColor;
public:
	void SetBufferColor(const DWORD _color)
	{
		m_BackBufferColor = _color;
	}

private:
	void PushRenderer(int _Order, ActorRenderer* _Renderer);
	void Render();
	void Release();
	void BitmapBufferClear(HDC _buffer, Vector2f _size = Vector2f::zero);

public:
	void YSortOn(int _index);
	
};

