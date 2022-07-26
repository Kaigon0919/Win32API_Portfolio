#pragma once

class BattlePawn;
class SingleRenderer;
class HPBar
{
public:
	HPBar();
	~HPBar();

private:
	BattlePawn* m_Pawn;
	SingleRenderer* m_Back;
	SingleRenderer* m_Up;
	float m_MaxHp;
	float* m_CurHp;
	Vector2f m_Pivot;
	Vector2f m_Size;

public:
	void Init(BattlePawn* pawn,float * curHp, float maxHp, Vector2f pivot, Vector2f size,int orderOffset = 0 , bool back = true);
	void SetSprite(const wchar_t * _BackImage, const wchar_t * _UpImage);
	void SetUpSprite(const wchar_t * _UpImage);
	void SetBackSprite(const wchar_t * _BackImage);
	void SetActive(bool isActive);
	void Update();
};

