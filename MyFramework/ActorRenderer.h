#pragma once
#include "ActorSubBase.h"
#include<set>
class ActorRenderer : public ActorSubBase
{
protected:
	ActorRenderer();
	~ActorRenderer();

public:
	friend class Actor;
	friend class RenderManager;

protected:
	bool m_bCamera;
	int m_Order;
public:
	void CameraMode(bool _isCamera)
	{
		m_bCamera = _isCamera;
	}
	Vector2f RenderPosition(); 
public:
		int Order() { return m_Order; }
		void Order(int _Order) { m_Order = _Order; }

private:
	virtual void Render() = 0;

};

