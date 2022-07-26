#pragma once
#include "Actor.h"

class BattlePawn;
class AniRenderer;
class ActorCollision;
class Arrow : public Actor
{
public:
	Arrow();
	~Arrow();
protected:
	enum ArrowDir
	{
		LeftDown, Down, RightDown, Left, Right, LeftTop, Top, RightTop, DirMax
	};
	ArrowDir m_Dir;
	std::wstring m_DirString[ArrowDir::DirMax];
public:
	enum ArrowType
	{
		FireArrow,
		DragonArrow,
		Max
	};
public:
	// Actor을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
private:
	BattlePawn * m_Taget;
	Vector2f m_TagetCenter;
	float m_Speed;
	float m_Att;
	float m_AttRange;
	ArrowType m_Type;
private:
	AniRenderer * m_Render;
	ActorCollision * m_Col;
protected:
	Vector2f DistancePerFrame(const Vector2f& _myPosition, const Vector2f& _taget, const float _moveDistance);
	void DirUpdate();
	void ChangeDir(ArrowDir _newDir);
	ArrowDir QuadrantProsses(int num, Vector2f dir);
public:
	void Setting(BattlePawn * taget, ArrowType type, float speed, float att, float attRange);
private:
	void AnimationSetting();
};

