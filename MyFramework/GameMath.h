#pragma once

#include "MathData.h"
#include <math.h>

class GameMath
{
public:
	GameMath();
	~GameMath();

public:
	static const float PI;
	static const float DTOR;
	static const float RTOD;

public:
	// 선형보간.
	static Vector2f Lerp(Vector2f _Start, Vector2f _End, float _t, bool _Cut = true)
	{
		if (1.0f >= _t && true == _Cut)
		{
			_t = 1.0f;
		}

		return (_Start * (1.0f - _t)) + (_End *_t);
	}

	static Vector2f DgreeToDir(float _d)
	{
		float radian = _d * DTOR;
		return Vector2f(cosf(radian), -sin(radian));
	}

	// 밑변의 거리를 구하는 함수.
	static float PTOPWDIS(const Vector2f & _left, const Vector2f& _right)
	{
		float width = _left.x - _right.x;
		
		width *= (width < 0 ? -1 : 1);

		return width;
	}

	// 높이의 거리를 구하는 함수.
	static float PTOPHDIS(const Vector2f & _left, const Vector2f& _right)
	{
		float height = _left.y - _right.y;

		height *= (height < 0 ? -1 : 1);

		return height;
	}
	// 빗변의 거리를 구하는 함수.
	static float PTOPDIS(const Vector2f& _left, const Vector2f& _right)
	{
		float wDis = PTOPWDIS(_left, _right);
		float hDis = PTOPHDIS(_left, _right);

		return sqrtf(wDis*wDis + hDis*hDis);
	}
	static float PTOPRAD(const Vector2f& _Left, const Vector2f& _Right)
	{
		float RDis = PTOPDIS(_Left, _Right);

		float w = _Left.x - _Right.x;
		float h = _Left.y - _Right.y;

		float cosS = w / RDis;
		float sinS = h / RDis;
		float tanS = h / w;

		float Rad = 0.0f;
		// case1.
		//*/
		if (sinS>=0)
		{
			Rad = acosf(cosS);
		}
		else if(sinS< 0)
		{
			Rad = PI * 2 - acosf(cosS);
		}
		//*/

		// case2
		//atan2f 를 이용함.
		/*/
		float Rad = atan2f(_Left.y - _Right.y, _Left.x - _Right.x); // cos의 역함수 acosf
		if (Rad < 0)
		{
			Rad = PI*2 + Rad;
		}
		//*/
		return Rad;
	}
	static float PTOPDEG(const Vector2f& _Left, const Vector2f& _Right)
	{
		return PTOPRAD(_Left, _Right) * RTOD;
	}
	static bool RECTTORECT(const RectFloat& _Left, const RectFloat& _Right)
	{
		if (_Left.Left() > _Right.Right())
		{
			return false;
		}
		if (_Left.Right() < _Right.Left())
		{
			return false;
		}
		if (_Left.Top() > _Right.Bottom())
		{
			return false;
		}
		if (_Left.Bottom() < _Right.Top())
		{
			return false;
		}

		return true;
	}
	static bool RECTTOCIRCLE(const RectFloat& _Left, const RectFloat& _Right)
	{
		RectFloat HR = _Left;
		RectFloat WR = _Left;

		HR.Size.y += _Right.Size.x;
		WR.Size.x += _Right.Size.x;

		if (RECTTOPOINT(HR, _Right.Position) || RECTTOPOINT(HR, _Right.Position))
		{
			return true;
		}

		if (CIRCLETOPOINT(_Right, _Left.LeftTop()) ||
			CIRCLETOPOINT(_Right, _Left.RightTop()) ||
			CIRCLETOPOINT(_Right, _Left.LeftBottom()) ||
			CIRCLETOPOINT(_Right, _Left.RightBottom()))
		{
			return true;
		}
		return false;

	}
	static bool RECTTOPOINT(const RectFloat& _Left, const Vector2f& _Right)
	{
		if (_Left.Left() > _Right.x)
		{
			return false;
		}
		if (_Left.Right() < _Right.x)
		{
			return false;
		}
		if (_Left.Top() > _Right.y)
		{
			return false;
		}
		if (_Left.Bottom() < _Right.y)
		{
			return false;
		}
		return true;
	}
	static bool CIRCLETOCIRCLE(const RectFloat& _Left, const RectFloat& _Right)
	{
		float dis = PTOPDIS(_Left.Position, _Right.Position);

		if (_Left.Size.GetHalfIntX() + _Right.Size.GetHalfIntX() > dis)
		{
			return true;
		}
		return false;
	}
	static bool CIRCLETOPOINT(const RectFloat& _Left, const Vector2f& _Right)
	{
		float dis = PTOPDIS(_Left.Position, _Right);

		if (_Left.Size.GetHalfIntX() > dis)
		{
			return true;
		}
		return false;

	}
	static bool POINTTOPOINT(const RectFloat& _Left, const RectFloat& _Right)
	{
		return _Left.Position == _Right.Position;
	}
};

