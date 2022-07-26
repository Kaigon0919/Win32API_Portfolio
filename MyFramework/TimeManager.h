#pragma once
class TimeManager
{
private:
	TimeManager();
	~TimeManager();

public:
	static TimeManager& Instance()
	{
		static TimeManager instance = TimeManager();
		return instance;
	}

private: // private innser class.
	class Timer
	{
	public:
		Timer();
		~Timer();
	private:
		LARGE_INTEGER Count;
		LARGE_INTEGER CurTime;
		LARGE_INTEGER PrevTime;
		float deltaTime;

		int fps;
		int frameCountAcc;
		float fpsTimeAcc;

	public: // Get,Set Function.
		inline float GetDeltaTime()const
		{
			return deltaTime;
		}
		inline int GetFPS()const
		{
			return fps;
		}
	public:
		void Update();
		void FpsUpdate();
	};
private:
	Timer m_Timer;

public: // Get,Set Function.
	inline float GetDeltaTime()const
	{
		return m_Timer.GetDeltaTime();
	}
	inline int GetFPS()const
	{
		return m_Timer.GetFPS();
	}
public: // public Function.
	void Update();

};

