#pragma once
class UpdateBase
{
public:
	UpdateBase();
	virtual ~UpdateBase();

private:
	bool m_bDeath;
	bool m_bUpdate;
public:
	inline void UpdateOn()
	{
		m_bUpdate = true;
	}
	inline void UpdateOff()
	{
		m_bUpdate = false;
	}
	inline void SetUpdate(bool isOn)
	{
		m_bUpdate = isOn;
	}
	inline void Death()
	{
		m_bDeath = true;
	}
	inline virtual bool IsDeath() const
	{
		return m_bDeath;
	}
	inline virtual bool IsUpdate() const
	{
		return  m_bUpdate && !m_bDeath;
	}

};

