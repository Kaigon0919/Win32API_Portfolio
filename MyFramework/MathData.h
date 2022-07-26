#pragma once

struct Vector2i;

struct Vector2f
{
public:
	Vector2f() : x(0.0f), y(0.0f) {	}
	Vector2f(int _x, int _y) : x((float)_x), y((float)_y) {	}
	Vector2f(float _x, float _y) : x(_x), y(_y) {	}
public:
	float x;
	float y;
public:
	static const Vector2f zero;
	static const Vector2f one;
	static const Vector2f left;
	static const Vector2f right;
	static const Vector2f up;
	static const Vector2f down;

public:
	int GetIntX()const		{ return (int)x;		}
	int GetIntY()const		{ return (int)y;		}
	int GetHalfIntX()const	{ return (int)(x*0.5f); }
	int GetHalfIntY()const	{ return (int)(y*0.5f); }

	float GetHalfX()const		{ return x*0.5f;		}
	float GetHalfY()const		{ return y*0.5f;		}

	Vector2f GetHalf()const { return Vector2f(GetHalfX(), GetHalfY()); }
	
public:
	void normalize()
	{
		float len = Length();
		x /= len;
		y /= len;
	}
	Vector2f GetNormalize()
	{
		float len = sqrtf(x*x + y*y);
		return Vector2f(x/len, y/len);
	}
	void Rotate(float degree)
	{
		float radian = (float)degree / 180.0f * 3.14f;
		float newX, newY;
		newX = x*cos(radian) - y*sin(radian);
		newY = x*sin(radian) + y*cos(radian);

		x = newX;
		y = newY;
	}
	float Dot(const Vector2f& ref) const
	{
		return (x * ref.x + y * ref.y);
	}
	float Cross(const Vector2f& ref) const
	{
		return (x * ref.y - y * ref.x);
	}
	float Length()const { return sqrtf(x*x + y*y); }
	float Distance(const Vector2f& ref)const
	{
		return (ref - *this).Length();
	}
	Vector2f operator+(const Vector2f& ref)
	{
		return Vector2f(x + ref.x, y + ref.y);
	}
	Vector2f operator-(const Vector2f& ref)const
	{
		return Vector2f(x - ref.x, y - ref.y);
	}
	Vector2f& operator+=(const Vector2f& ref)
	{
		x += ref.x;
		y += ref.y;
		return *this;
	}
	Vector2f& operator-=(const Vector2f& ref)
	{
		x -= ref.x;
		y -= ref.y;
		return *this;
	}
	Vector2f operator*(const int& ref) const
	{
		return Vector2f(x*ref, y*ref);
	}
	Vector2f operator*(const float& ref) const
	{
		return Vector2f(x*ref, y*ref);
	}
	float operator*(const Vector2f& ref)  const
	{
		return Cross(ref);
	}

	bool operator==(const Vector2f& ref) const
	{
		return x == ref.x && y == ref.y;
	}

};

struct Vector2i
{
public:
	Vector2i() : x(0), y(0) {	}
	Vector2i(int _x, int _y) : x(_x), y(_y) {	}
	Vector2i(float _x, float _y) : x((int)_x), y((int)_y) {	}
	Vector2i(__int64 _value) : value64(_value) {	}
	Vector2i(const Vector2f& ref) : x((int)ref.x), y((int)ref.y) {	}
public:
	union 
	{
		__int64 value64;
		struct
		{
			int x;
			int y;
		};
	};
public:
	float GetHalfX()const { return (int)x*0.5f; }
	float GetHalfY()const { return (int)y*0.5f; }

	Vector2i& operator-=(const Vector2f& ref)
	{
		x -= (int)ref.x;
		y -= (int)ref.y;
		return *this;
	}
	
	operator Vector2f() const
	{
		return Vector2f(static_cast<float>(x), static_cast<float>(y));
	}
	operator __int64()const
	{
		return value64;
	}
};

struct RectFloat
{
public:
	Vector2f Position;
	Vector2f Size;

public:
	RectFloat() : Position(), Size() {}
	RectFloat(Vector2f _Position, Vector2f _Size) : Position(_Position), Size(_Size) {}

public:
	float Left()const				{	return Position.x - Size.GetHalfX();								}
	float Right()const				{	return Position.x + Size.GetHalfX();								}
	float Top()const				{	return Position.y - Size.GetHalfY();								}
	float Bottom()const				{	return Position.y + Size.GetHalfY();								}

	Vector2f LeftTop()const			{	return Vector2f(Left()	, Top()		);								}
	Vector2f RightTop()const			{	return Vector2f(Right()	, Top()	);								}
	Vector2f LeftBottom()const		{	return Vector2f(Left()	, Bottom()	);								}
	Vector2f RightBottom()const		{	return Vector2f(Right()	, Bottom()	);								}

	Vector2f LeftCenter()const		{	return Vector2f(Left()		, Position.y	);						}
	Vector2f RightCenter()const		{	return Vector2f(Right()		, Position.y	);						}
	Vector2f TopCenter()const		{	return Vector2f(Position.x	, Top()			);						}
	Vector2f BottomCenter()const		{	return Vector2f(Position.x	, Bottom()	);						}


	int IntLeft()const				{	return (int)Left();															}
	int IntRight()const				{	return (int)Right();														}
	int IntTop()const				{	return (int)Top();															}
	int IntBottom()const			{	return (int)Bottom();														}

	Vector2f IntLeftTop()const		{	return Vector2f((float)IntLeft()		, (float)IntTop()			);		}
	Vector2f IntRightTop()const		{	return Vector2f((float)IntRight()		, (float)IntTop()			);		}
	Vector2f IntLeftBottom()const	{	return Vector2f((float)IntLeft()		, (float)IntBottom()		);		}
	Vector2f IntRightBottom()const	{	return Vector2f((float)IntRight()		, (float)IntBottom()		);		}

	Vector2f IntLeftCenter()const	{	return Vector2f((float)IntLeft()		, (float)Position.GetIntY()	);		}
	Vector2f IntRightCenter()const	{	return Vector2f((float)IntRight()		, (float)Position.GetIntY()	);		}
	Vector2f IntTopCenter()const	{	return Vector2f((float)Position.GetIntX(), (float)IntTop()			);		}
	Vector2f IntBottomCenter()const	{	return Vector2f((float)Position.GetIntX(), (float)IntBottom()		);		}

};