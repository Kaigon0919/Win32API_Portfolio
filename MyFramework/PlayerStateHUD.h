#pragma once
#include"HPBar.h"

class BattlePawn;
class SingleRenderer;
class PlayerStateHUD
{
public:
	PlayerStateHUD();
	~PlayerStateHUD();
private:
	BattlePawn* m_Pawn;
	HPBar m_HpBar;
	HPBar m_MpBar;
	HPBar m_SpBar;
	SingleRenderer* m_Back;
	SingleRenderer* m_Up;
	Vector2f m_Pivot;
	Vector2f m_Size;

public:
	void Init(BattlePawn * _Pawn, float * _CurHp, float _MaxHp, float * _CurMp, float _MaxMp, float * _CurSp, float _MaxSp, Vector2f _Pivot, Vector2f _Size);
	void Update();

};

