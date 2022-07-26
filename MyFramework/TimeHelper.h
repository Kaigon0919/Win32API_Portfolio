#pragma once
class TimeHelper
{
private:
	float m_Time;
	float m_CurTime;
	bool m_IsDead;
public:
	bool Check();
	void Reset();
	inline void SetDead(bool isdead)
	{
		m_IsDead = isdead;
	}
	inline void SetTime(float time)
	{
		m_Time = time;
	}

public:
	TimeHelper(float _Time);
	~TimeHelper();
};

