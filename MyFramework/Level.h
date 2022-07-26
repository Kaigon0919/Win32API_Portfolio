#pragma once
#include<list>
#include"RenderManager.h"
#include"CollisionManager.h"

class Actor;
class SystemClass;
class Level
{
protected:
	Level();
	virtual ~Level();

public:
	friend SystemClass;
	friend Actor;

private:
	static bool IsDebugMode;
private:
	std::list<Actor*> m_ActorList;
	std::list<Actor*>::iterator m_IteratorStart;
	std::list<Actor*>::iterator m_IteratorEnd;

	RenderManager m_RenderMgr;
	bool isLoading;
	Vector2f m_Camera;
protected: // protected function.
	void PrevUpdate();
	void Update();
	void LateUpdate();
	void Render();
	void AfterRender();
	void Release();
	void Collision();

	// Level Change Update.
	virtual void Loading() = 0;
	virtual void LevelEnter() {}
	virtual void LevelExit() {}

	// Level Update.
	virtual void LevelUpdate() {}
	virtual void EndDebugUpdate() {}

public:
	static bool IsDebug() {
		return IsDebugMode;
	}
	static void SetDebugMode(bool isOn) {
		IsDebugMode = isOn;
	}
	static void SetDebugModeToggle()
	{
		IsDebugMode = IsDebugMode ? false : true;
	}
	inline size_t AllActorCount()const
	{
		return m_ActorList.size();
	}
	
	inline void SetCameraPosition(const Vector2f& _pos)
	{
		m_Camera = _pos;
	}
	inline Vector2f GetCameraPosition()const
	{
		return m_Camera;
	}
	Vector2f GetMouseConvertPosition()const;

	void SetBackBufferColor(DWORD _color)
	{
		m_RenderMgr.SetBufferColor(_color);
	}
private:
	// 스테이트를 이동할수 있는 Actor들을 모아놓는다.
	static std::list<Actor*> m_OverActorList;

public:
	static void EndDestroy();

public:
	bool IsHaveCheck(Actor* _Actor);
	Actor* FindActor(const wchar_t * ActorName);

private:
	static void PushOver(Actor* _OverActor)
	{
		m_OverActorList.push_back(_OverActor);
	}
	Actor* FindOverActor(const wchar_t * ActorName);

public: // public template function.
	template<class T>
	T* CreateActor(Vector2f _spawnPosition = Vector2f::zero)
	{
		T * newActor = new T();
		newActor->SetLevel(this);
		newActor->SetPosition(_spawnPosition);
		newActor->Init();
		m_ActorList.push_back(newActor);
		return newActor;
	}
private:
	void PushActor(Actor* _NewActor);
public:
	void PushRenderer(int _Order, ActorRenderer* _pRenderer);
	void YSortOn(int _Order);

	/////////////////////////////////////////////////////////////////////////////////////////////
	// Col
private:
	CollisionManager m_ColMgr;
private:
	void PushCol(const wchar_t* _GroupName, ActorCollision* _collision);

protected:
	void ColLink(const wchar_t* _Left, const wchar_t* _Right);
};